#include "pch.h"
#include "Draw.h"
#include"Resources.h"
#include"Scene/GameObjects/PlayScene/Sun/Sun.h"
#include"ImaseLib/BinaryFile.h"
#include"ImaseLib/ReadData.h"

using namespace DirectX;
const int Draw::CASCADE_LIGHT_MAX_NUM(4);
std::unique_ptr<Draw> Draw::m_draw = nullptr;
const float Draw::FOG_LENGTH(300);
const float Draw::SHADOW_UPDATE_SECONDS(0.7f);		//影の更新秒数(静的オブジェクトの太陽の更新間隔)

//#include <DirectXTex.h>
//
//void SaveRenderTargetToDDS(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, ID3D11RenderTargetView* pRTV, ID3D11DepthStencilView* pDSV, const wchar_t* filename)
//{
//
//	// ビューからテクスチャリソース取得
//	ID3D11Resource* cubeMapResource = nullptr;
//	pRTV->GetResource(&cubeMapResource);
//	cubeMapResource->Release();
//
//	// テクスチャ―リソースから、イメージデータを作成
//	DirectX::ScratchImage image;
//	DirectX::CaptureTexture(
//		pDevice,
//		pContext,
//		cubeMapResource,
//		image
//	);
//
//	// イメージデータをファイルへ保存
//	DirectX::SaveToDDSFile(image.GetImages(),
//		image.GetImageCount(),
//		image.GetMetadata(), DirectX::DDS_FLAGS_NONE,
//		filename);
//}
Draw::Draw() :
	m_pContext(nullptr),
	m_pDevice(nullptr),
	m_view(SimpleMath::Matrix::Identity),
	m_proj(nullptr),
	m_commonStates(nullptr),
	m_height(),
	m_width(),
	m_cameraPosition(DirectX::SimpleMath::Vector3::Zero),
	m_cameraTarget(DirectX::SimpleMath::Vector3::Zero),
	m_cameraUp(DirectX::SimpleMath::Vector3::Zero),
	m_sun(nullptr),
	m_drawDistance(),
	m_FogFar(),
	m_FogNear(),
	m_timer(0),
	m_cascadeTatgetPos(),
	m_cameraDir(),
	m_staticCascadeUpdateDistance(0),
	m_keepStaticCascadeUpdateDistance(0)
{
}

void Draw::Initialize()
{
	m_deviceResources = SingletonDeviceResources::GetInstance()->GetDeviceResources();
	m_pContext = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	m_pDevice = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	m_proj = SingletonDeviceResources::GetInstance()->GetProj();
	m_commonStates = SingletonDeviceResources::GetInstance()->GetCommonStates();

	std::ifstream obj("Resources/json/Json_DrawOptionDate.Json");
	Json::CharReaderBuilder reader;
	Json::Value root;

	// ファイルが開かれているかを確認します。
	if (obj.is_open()) {
		std::string errors;

		// ファイルからJSONをパースします。
		if (Json::parseFromStream(reader, obj, &root, &errors))
		{
			// JSONに "house" が存在し、配列であるかどうかを確認します。
			if (root.isMember("DrawOption") && root["DrawOption"].isArray())
			{
				m_drawDistance = root["DrawOption"][0]["DRAW_DISTANCE"][0].asFloat();		//球クールタイム	(s)

				//霧の距離の設定
				m_FogFar = m_drawDistance;
				m_FogNear = m_drawDistance - FOG_LENGTH;

				//2乗で比較することが多いので事前計算
				m_drawDistance *= m_drawDistance;
}
		}
		else {
			std::cerr << "JSONのパースエラー: " << errors << std::endl;
		}
		obj.close();
	}
	else {
		std::cerr << "JSONファイルを開く際にエラーが発生しました。" << std::endl;
	}

	m_cascadeShadowMapManager = std::make_unique<CascadeShadowMapManager>();
	m_cascadeShadowMapManager->Initialize(m_deviceResources, m_cascadeTatgetPos, CASCADE_LIGHT_MAX_NUM, m_FogFar);

	m_att[0] = 0.0f;
	m_att[1] = 0.0f;
	m_att[2] = 1.0f;

	// ピクセルシェーダーの作成（トーラス用）
	std::vector<uint8_t> ps_torus = DX::ReadData(L"Resources/Shaders/LightEffectsPS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreatePixelShader(ps_torus.data(), ps_torus.size(), nullptr, m_PS_Torus.ReleaseAndGetAddressOf())
	);

	// ピクセルシェーダーの作成（トーラス用）
	std::vector<uint8_t> ps_shadow = DX::ReadData(L"Resources/Shaders/ShadowPS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreatePixelShader(ps_shadow.data(), ps_shadow.size(), nullptr, m_PS_Shadow.ReleaseAndGetAddressOf())
	);

	// 頂点シェーダーの作成（シャドウマップ用）
	std::vector<uint8_t> vs_depth = DX::ReadData(L"Resources/Shaders/SM_VS_Depth.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreateVertexShader(vs_depth.data(), vs_depth.size(), nullptr, m_VS_Depth.ReleaseAndGetAddressOf())
	);

	// ピクセルシェーダーの作成（シャドウマップ用）
	std::vector<uint8_t> ps_depth = DX::ReadData(L"Resources/Shaders/SM_PS_Depth.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreatePixelShader(ps_depth.data(), ps_depth.size(), nullptr, m_PS_Depth.ReleaseAndGetAddressOf())
	);


	// 頂点シェーダーの作成（シャドウマップ用）
	std::vector<uint8_t> vs = DX::ReadData(L"Resources/Shaders/SM_VS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreateVertexShader(vs.data(), vs.size(), nullptr, m_VS.ReleaseAndGetAddressOf())
	);
	// 頂点シェーダーの作成（シャドウマップ用）
	vs = DX::ReadData(L"Resources/Shaders/SM_NormalVS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreateVertexShader(vs.data(), vs.size(), nullptr, m_NoormalVS.ReleaseAndGetAddressOf())
	);

	// 頂点シェーダーの作成（シャドウマップ用）
	std::vector<uint8_t> gs = DX::ReadData(L"Resources/Shaders/SM_GS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreateGeometryShader(gs.data(), gs.size(), nullptr, m_GS.ReleaseAndGetAddressOf())
	);

	// ピクセルシェーダーの作成（シャドウマップ用）
	std::vector<uint8_t> ps = DX::ReadData(L"Resources/Shaders/SM_PS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreatePixelShader(ps.data(), ps.size(), nullptr, m_PS.ReleaseAndGetAddressOf())
	);
	// ピクセルシェーダーの作成（シャドウマップ用）
	 ps = DX::ReadData(L"Resources/Shaders/SM_NormalPS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreatePixelShader(ps.data(), ps.size(), nullptr, m_NoormalPS.ReleaseAndGetAddressOf())
	);
	// 頂点シェーダーの作成（シャドウマップ用）
	std::vector<uint8_t> no_picture_vs_depth = DX::ReadData(L"Resources/Shaders/SM_No_Picture_VS_Depth.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreateVertexShader(no_picture_vs_depth.data(), no_picture_vs_depth.size(), nullptr, m_NoPicture_VS_Depth.ReleaseAndGetAddressOf())
	);

	// ピクセルシェーダーの作成（シャドウマップ用）
	std::vector<uint8_t> no_picture_ps_depth = DX::ReadData(L"Resources/Shaders/SM_No_Picture_PS_Depth.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreatePixelShader(no_picture_ps_depth.data(), no_picture_ps_depth.size(), nullptr, m_NoPicture_PS_Depth.ReleaseAndGetAddressOf())
	);


	// 頂点シェーダーの作成（シャドウマップ用）
	std::vector<uint8_t> no_picture_vs = DX::ReadData(L"Resources/Shaders/SM_No_Picture_VS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreateVertexShader(no_picture_vs.data(), no_picture_vs.size(), nullptr, m_NoPictureVS.ReleaseAndGetAddressOf())
	);

	// ピクセルシェーダーの作成（シャドウマップ用）
	std::vector<uint8_t> no_picture_ps = DX::ReadData(L"Resources/Shaders/SM_No_Picture_PS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreatePixelShader(no_picture_ps.data(), no_picture_ps.size(), nullptr, m_NoPicturePS.ReleaseAndGetAddressOf())
	);

	// サンプラーの作成（シャドウマップ用）
	D3D11_SAMPLER_DESC sampler_desc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
	sampler_desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_LESS;
	m_pDevice->CreateSamplerState(&sampler_desc, m_shadowMapSampler.ReleaseAndGetAddressOf());

	sampler_desc = {};
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampler_desc.MinLOD = 0;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
	// デバイスに法線マップのサンプラーステートを作成
	m_pDevice->CreateSamplerState(&sampler_desc, m_NormalMapSampler.ReleaseAndGetAddressOf());
	//--------------------------------------------------------------------
	//	シャドウマップ用
	//--------------------------------------------------------------------


	// 定数バッファの作成
	D3D11_BUFFER_DESC bufferDesc2 = {};
	bufferDesc2.ByteWidth = static_cast<UINT>(sizeof(ConstantBuffer));	// 確保するサイズ（16の倍数で設定する）
	// GPU (読み取り専用) と CPU (書き込み専用) の両方からアクセスできるリソース
	bufferDesc2.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// 定数バッファとして扱う
	bufferDesc2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPUが内容を変更できるようにする
	DX::ThrowIfFailed(m_pDevice->CreateBuffer(&bufferDesc2, nullptr, m_constantBuffer2.ReleaseAndGetAddressOf()));

	// 定数バッファの作成
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(ConstantBuffer2));	// 確保するサイズ（16の倍数で設定する）
	// GPU (読み取り専用) と CPU (書き込み専用) の両方からアクセスできるリソース
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// 定数バッファとして扱う
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPUが内容を変更できるようにする
	DX::ThrowIfFailed(m_pDevice->CreateBuffer(&bufferDesc, nullptr, m_constantBuffer.ReleaseAndGetAddressOf()));

	ID3D11ShaderResourceView* srv = Textures::GetInstance()->GetHouse_01NormalMap();
	m_pContext->PSSetShaderResources(1, 1, &srv);

}

void Draw::Update(float elapsedTime)
{
	m_timer += elapsedTime;
}

Draw* Draw::GetInstance()
{
	//すでに生成されてるかチェック
	if (m_draw == nullptr)
	{
		//描画のインスタンスを生成する
		m_draw = std::make_unique<Draw>();
	}
	//描画のインスタンスを返す
	return m_draw.get();
}

void Draw::StaticShadowMapTexCreateStart(int index,float timer)
{
	timer;
	m_cascadeIndex = index;
	m_cascadeTatgetPos = GetEyePosition();
	// ビューポートを設定
	D3D11_VIEWPORT vp = { 0.0f, 0.0f, static_cast<float>(CascadeShadowMapManager::SHADOWMAP_SIZE), static_cast<float>(CascadeShadowMapManager::SHADOWMAP_SIZE), 0.0f, 1.0f };
	m_pContext->RSSetViewports(1, &vp); 

	auto rtv = m_cascadeShadowMapManager->GetRenderTexture(index)->GetRenderTargetView();
	auto dsv = m_cascadeShadowMapManager->GetDepthStencil(index)->GetDepthStencilView();

	// レンダーターゲットを変更（shadowMapRT）
	m_pContext->ClearRenderTargetView(rtv, SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f));
	m_pContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_pContext->OMSetRenderTargets(1, &rtv, dsv);
}
void Draw::DynamicShadowMapTexCreateStart(int index, float timer)
{
	m_cascadeIndex = index;
	if (timer >= SHADOW_UPDATE_SECONDS)
		m_cascadeTatgetPos = GetEyePosition();

		m_cascadeShadowMapManager->Update(0.01666f,timer, GetEyePosition());

	// ビューポートを設定
	D3D11_VIEWPORT vp = { 0.0f, 0.0f, static_cast<float>(CascadeShadowMapManager::SHADOWMAP_SIZE), static_cast<float>(CascadeShadowMapManager::SHADOWMAP_SIZE), 0.0f, 1.0f };
	m_pContext->RSSetViewports(1, &vp);

	auto rtv = m_cascadeShadowMapManager->GetMoveRenderTexture(index)->GetRenderTargetView();
	auto dsv = m_cascadeShadowMapManager->GetMoveDepthStencil(index)->GetDepthStencilView();

	// レンダーターゲットを変更（shadowMapRT）
	m_pContext->ClearRenderTargetView(rtv, SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f));
	m_pContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_pContext->OMSetRenderTargets(1, &rtv, dsv);
}


void Draw::ShadowMapTexCreate(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world)
{
	// トーラスの描画
	model->Draw(m_pContext, *m_commonStates, world, m_cascadeShadowMapManager->GetMoveLightView(), m_cascadeShadowMapManager->GetLightProj(m_cascadeIndex), false, [&]()
		{
			m_pContext->VSSetShader(m_VS_Depth.Get(), nullptr, 0);
			m_pContext->PSSetShader(m_PS_Depth.Get(), nullptr, 0);
		}
	);

}

void Draw::ShadowMapTexCreateNoPicture(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world)
{	
	// トーラスの描画
	model->Draw(m_pContext, *m_commonStates, world, m_cascadeShadowMapManager->GetMoveLightView(), m_cascadeShadowMapManager->GetLightProj(m_cascadeIndex), false, [&]()
		{
			m_pContext->VSSetShader(m_NoPicture_VS_Depth.Get(), nullptr, 0);
			m_pContext->PSSetShader(m_NoPicture_PS_Depth.Get(), nullptr, 0);
		}
	);

}

void Draw::ShadowMapTexCreateNoPictureLight(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	// GPUが定数バッファに対してアクセスを行わないようにする
	m_pContext->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// 定数バッファを更新
	ConstantBuffer2 cb = {};
	for (int i = 0; i < CASCADE_LIGHT_MAX_NUM; i++)
	{
		cb.lightViewProj[i] = XMMatrixTranspose(m_cascadeShadowMapManager->GetLightView() * m_cascadeShadowMapManager->GetLightProj(i));
		cb.MovelightViewProj[i] = XMMatrixTranspose(m_cascadeShadowMapManager->GetMoveLightView() * m_cascadeShadowMapManager->GetLightProj(i));
		cb.lightDistance[i] = DirectX::SimpleMath::Vector4(0, 0, 0, m_cascadeShadowMapManager->GetLightDistance(i));
	}
	cb.lightDir = -m_cascadeShadowMapManager->GetLightDir();
	cb.StaticTargetPosition = m_cascadeTatgetPos;
	cb.DynamicTargetPosition = GetEyePosition();
	cb.lightAmbient = DirectX::SimpleMath::Vector3(0.3f, 0.3f, 0.3f);
	cb.FogFar = m_FogFar;
	cb.FogNear = m_FogNear;


	*static_cast<ConstantBuffer2*>(mappedResource.pData) = cb;

	// GPUが定数バッファに対してのアクセスを許可する
	m_pContext->Unmap(m_constantBuffer.Get(), 0);

	model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj, false, [&]()
		{
			// 定数バッファの設定
			ID3D11Buffer* cbuf[] = { m_constantBuffer.Get() };
			m_pContext->VSSetConstantBuffers(1, 1, cbuf);
			m_pContext->PSSetConstantBuffers(1, 1, cbuf);

			// テクスチャサンプラーの設定
			ID3D11SamplerState* samplers[] = { m_commonStates->PointWrap(), m_shadowMapSampler.Get() };
			m_pContext->PSSetSamplers(0, 2, samplers);

			// シェーダーの設定
			m_pContext->VSSetShader(m_NoPictureVS.Get(), nullptr, 0);
			m_pContext->PSSetShader(m_NoPicturePS.Get(), nullptr, 0);
		}
	);

}

void Draw::ShadowMapTexCreateEnd()
{
	// -------------------------------------------------------------------------- //
	auto renderTarget = m_deviceResources->GetRenderTargetView();
	auto depthStencil = m_deviceResources->GetDepthStencilView();
	m_pContext->ClearRenderTargetView(renderTarget, Colors::AliceBlue);
	m_pContext->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pContext->OMSetRenderTargets(1, &renderTarget, depthStencil);
	auto const viewport = m_deviceResources->GetScreenViewport();
	m_pContext->RSSetViewports(1, &viewport);


	//ID3D11ShaderResourceView* s = Textures::GetInstance()->GetStaticShadowMapTex1();
	//m_pContext->PSSetShaderResources(0 + 1, 1, &s);
	//s = Textures::GetInstance()->GetStaticShadowMapTex2();
	//m_pContext->PSSetShaderResources(1 + 1, 1, &s);
	//s = Textures::GetInstance()->GetStaticShadowMapTex3();
	//m_pContext->PSSetShaderResources(2 + 1, 1, &s);
	//s = Textures::GetInstance()->GetStaticShadowMapTex4();
	//m_pContext->PSSetShaderResources(3 + 1, 1, &s);
	for (int index = 0; index < CASCADE_LIGHT_MAX_NUM; index++)
	{
		//ID3D11ShaderResourceView* s=  Textures::GetInstance()->GetCoinlight();
		auto srv = m_cascadeShadowMapManager->GetRenderTexture(index)->GetShaderResourceView();
		m_pContext->PSSetShaderResources(index + 3, 1, &srv);
		//auto renderTargetTex =m_cascadeShadowMapManager->GetRenderTexture(index)->GetRenderTargetView();
		//auto depthStencilTex =m_cascadeShadowMapManager->GetDepthStencil(index)->GetDepthStencilView();
		//std::wstringstream ss;
		//ss << L"test" << index << L".dds";
		//std::wstring filename = ss.str();
		//// const wchar_t* に変換PSSetShaderResources
		//const wchar_t* filenameCStr = filename.c_str();
		//SaveRenderTargetToDDS(m_pDevice, m_pContext, renderTargetTex, depthStencilTex, filenameCStr);
		srv = m_cascadeShadowMapManager->GetMoveRenderTexture(index)->GetShaderResourceView();
		m_pContext->PSSetShaderResources(index + 3 + CASCADE_LIGHT_MAX_NUM, 1, &srv);

	}
}

void Draw::ShadowMapTexCreateEndCon()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	// GPUが定数バッファに対してアクセスを行わないようにする
	m_pContext->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// 定数バッファを更新
	ConstantBuffer2 cb = {};
	for (int i = 0; i < CASCADE_LIGHT_MAX_NUM; i++)
	{
		cb.lightViewProj[i] = XMMatrixTranspose(m_cascadeShadowMapManager->GetLightView() * m_cascadeShadowMapManager->GetLightProj(i));
		cb.MovelightViewProj[i] = XMMatrixTranspose(m_cascadeShadowMapManager->GetMoveLightView() * m_cascadeShadowMapManager->GetLightProj(i));
		cb.lightDistance[i] = DirectX::SimpleMath::Vector4(0, 0, 0, m_cascadeShadowMapManager->GetLightDistance(i));
	}
	cb.lightDir = m_cascadeShadowMapManager->GetLightDir();
	cb.StaticTargetPosition = m_cascadeTatgetPos;
	cb.DynamicTargetPosition = GetEyePosition();
	cb.lightAmbient = DirectX::SimpleMath::Vector3(0.3f, 0.3f, 0.3f);
	cb.FogFar = m_FogFar;
	cb.FogNear = m_FogNear;


	*static_cast<ConstantBuffer2*>(mappedResource.pData) = cb;

	// GPUが定数バッファに対してのアクセスを許可する
	m_pContext->Unmap(m_constantBuffer.Get(), 0);

	// 定数バッファの設定
	ID3D11Buffer* cbuf[] = { m_constantBuffer.Get() };
	m_pContext->VSSetConstantBuffers(1, 1, cbuf);
	m_pContext->PSSetConstantBuffers(1, 1, cbuf);

}

void Draw::DrawEndUpdate()
{
	// リソースの割り当てを解除する（shadowMapRT）
	//ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	//m_pContext->PSSetShaderResources(1, 1, nullsrv);

	auto renderTarget = m_deviceResources->GetRenderTargetView();
	auto depthStencil = m_deviceResources->GetDepthStencilView();

	//SaveRenderTargetToDDS(m_pDevice, m_pContext, renderTarget, depthStencil, L"test.dds");
}

void Draw::ShadowMapRender(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, std::function<void()> additionalProcessing)
{
	model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj, false, [&]()
		{
			if (additionalProcessing)
				additionalProcessing();

			// テクスチャサンプラーの設定
			ID3D11SamplerState* samplers[] = { m_commonStates->PointWrap(), m_shadowMapSampler.Get() ,m_NormalMapSampler.Get() };
			m_pContext->PSSetSamplers(0, 3, samplers);

			// シェーダーの設定
			m_pContext->VSSetShader(m_VS.Get(), nullptr, 0);
			m_pContext->PSSetShader(m_PS.Get(), nullptr, 0);
			//m_pContext->GSSetShader(m_GS.Get(), nullptr, 0);
		}
	);
}

void Draw::ShadowMapRender(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world,ID3D11ShaderResourceView* normalMapTex,std::function<void()> additionalProcessing)
{
	if(normalMapTex)
		m_pContext->PSSetShaderResources(1, 1, &normalMapTex);
	ID3D11ShaderResourceView* stv = Textures::GetInstance()->GetPillarTexture_01NormalMap();

	m_pContext->PSSetShaderResources(2, 1, &stv);

	model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj, false, [&]()
		{
			if (additionalProcessing)
				additionalProcessing();

			// テクスチャサンプラーの設定
			ID3D11SamplerState* samplers[] = { m_commonStates->PointWrap(), m_shadowMapSampler.Get() ,m_NormalMapSampler.Get()};
			m_pContext->PSSetSamplers(0, 3, samplers);

			// シェーダーの設定
			m_pContext->VSSetShader(m_NoormalVS.Get(), nullptr, 0);
			m_pContext->PSSetShader(m_NoormalPS.Get(), nullptr, 0);
			//m_pContext->GSSetShader(m_GS.Get(), nullptr, 0);
		}
	);
}

void Draw::ShadowMapRenderNoPicture(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world,std::function<void()> additionalProcessing)
{
	model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj, false, [&]()
		{
			if (additionalProcessing)
				additionalProcessing();

			// テクスチャサンプラーの設定
			ID3D11SamplerState* samplers[] = { m_commonStates->PointWrap(), m_shadowMapSampler.Get() };
			m_pContext->PSSetSamplers(0, 2, samplers);

			// シェーダーの設定
			m_pContext->VSSetShader(m_NoPictureVS.Get(), nullptr, 0);
			m_pContext->PSSetShader(m_NoPicturePS.Get(), nullptr, 0);
		}
	);
}

void Draw::Render(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world)
{
	//// トーラスモデルのエフェクトを設定する
	//model->UpdateEffects([&](IEffect* effect)
	//	{
	//		auto basicEffect = dynamic_cast<BasicEffect*>(effect);
	//		if (basicEffect)
	//		{
	//			basicEffect->SetPerPixelLighting(true);
	//		}
	//	}
	//);

	////モデルを描画
	//model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj, false, [&]()
	//	{
	//		// オリジナルピクセルシェーダーの設定
	//		D3D11_MAPPED_SUBRESOURCE mappedResource;
	//		// GPUが定数バッファに対してアクセスを行わないようにする
	//		m_pContext->Map(m_CBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	//		// 定数バッファを更新
	//		ConstantBuffer cb = { m_lightPosition };
	//		*static_cast<ConstantBuffer*>(mappedResource.pData) = cb;
	//		// GPUが定数バッファに対してのアクセスを許可する
	//		m_pContext->Unmap(m_CBuffer.Get(), 0);
	//		// ピクセルシェーダ使用する定数バッファを設定
	//		ID3D11Buffer* cbuf_ps[] = { m_CBuffer.Get() };

	//		// オリジナルピクセルシェーダーの設定
	//		m_pContext->PSSetShader(m_pixelShader.Get(), nullptr, 0);
	//	}
	//);
	// 
	//モデルの設定
	model->UpdateEffects([&](IEffect* effect)
		{
			auto basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				//光の方向と色
				basicEffect->SetLightDirection(true, SimpleMath::Vector3(-m_cascadeShadowMapManager->GetLightDir()));
				basicEffect->SetLightDiffuseColor(false, SimpleMath::Color(0.4f, 0.4f, 0.4f, 0.5f));

				//明度
				basicEffect->SetAlpha(m_sun->GetObjectsRight());
			}
		}
	);

	//モデルを描画
	model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj);
}


void Draw::Rendersss(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world)
{
	//// 射影行列の作成
//*m_proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
//	XMConvertToRadians(45.0f), static_cast<float>(m_width) / static_cast<float>(m_height), 0.1f, drawingDistance);

//// トーラスモデルのエフェクトを設定する
//model->UpdateEffects([&](IEffect* effect)
//	{
//		auto basicEffect = dynamic_cast<BasicEffect*>(effect);
//		if (basicEffect)
//		{
//			basicEffect->SetPerPixelLighting(true);
//		}
//	}
//);

////モデルを描画
//model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj, false, [&]()
//	{
//		// オリジナルピクセルシェーダーの設定
//		D3D11_MAPPED_SUBRESOURCE mappedResource;
//		// GPUが定数バッファに対してアクセスを行わないようにする
//		m_pContext->Map(m_CBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
//		// 定数バッファを更新
//		ConstantBuffer cb = { m_lightPosition };
//		*static_cast<ConstantBuffer*>(mappedResource.pData) = cb;
//		// GPUが定数バッファに対してのアクセスを許可する
//		m_pContext->Unmap(m_CBuffer.Get(), 0);
//		// ピクセルシェーダ使用する定数バッファを設定
//		ID3D11Buffer* cbuf_ps[] = { m_CBuffer.Get() };

//		// オリジナルピクセルシェーダーの設定
//		m_pContext->PSSetShader(m_pixelShader.Get(), nullptr, 0);
//	}
//);

// トーラスモデルのエフェクトを設定する
	model->UpdateEffects([&](IEffect* effect)
		{
			auto basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				basicEffect->SetLightingEnabled(true);
				basicEffect->SetPerPixelLighting(true);
				basicEffect->SetTextureEnabled(true);
				basicEffect->SetVertexColorEnabled(false);
				basicEffect->SetFogEnabled(false);
			}
		}
	);


	model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj, false, [&]()
		{
			// 定数バッファを更新
			D3D11_MAPPED_SUBRESOURCE mappedResource;

			// GPUが定数バッファに対してアクセスを行わないようにする
			m_pContext->Map(m_constantBuffer2.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

			// 定数バッファを更新
			ConstantBuffer cb = {};
			cb.att0 = 200.0f;
			cb.att1 = 0;
			cb.att2 = m_att[2];
			cb.SpotLight = DirectX::SimpleMath::Vector3(0, 100, 0),
			cb.lightPosition = m_cascadeShadowMapManager->GetLightDir();
			cb.LightAmbient = DirectX::SimpleMath::Vector3(0.3f, 0.3f, 0.3f);
			cb.EyePosition = m_cameraPosition;
			cb.FogFar = m_FogFar;
			cb.FogNear = m_FogNear;

			*static_cast<ConstantBuffer*>(mappedResource.pData) = cb;

			// GPUが定数バッファに対してのアクセスを許可する
			m_pContext->Unmap(m_constantBuffer2.Get(), 0);

			// ピクセルシェーダ使用する定数バッファを設定
			ID3D11Buffer* cbuf_ps[] = { m_constantBuffer2.Get() };
			m_pContext->PSSetConstantBuffers(1, 1, cbuf_ps);	// スロット０はDirectXTKが使用しているのでスロット１を使用する

			// オリジナルピクセルシェーダーの設定
			m_pContext->PSSetShader(m_PS_Torus.Get(), nullptr, 0);
		}
	);

}

void Draw::kari(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world)
{
	//モデルの設定
	model->UpdateEffects([&](IEffect* effect)
		{
			auto basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				//光の方向と色
				basicEffect->SetLightDirection(true, SimpleMath::Vector3(m_cascadeShadowMapManager->GetLightDir()));
				basicEffect->SetLightDiffuseColor(false, SimpleMath::Color(0.4f, 0.4f, 0.4f, 0.5f));

				//明度
				basicEffect->SetAlpha(m_sun->GetObjectsRight());
			}
		}
	);

	//モデルを描画
	model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj);

}

void Draw::LightRender(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world)
{	
	//モデルの設定
	model->UpdateEffects([&](IEffect* effect)
		{
			auto basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				//明度をなくす
				basicEffect->SetAlpha(true);

				//光の強さ
				basicEffect->SetEmissiveColor(DirectX::SimpleMath::Color(1, 1, 1, 1));
			}
		}
	);

	//モデルを描画
	model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj);

}


void Draw::MeshRender(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world)
{
	//モデルを描画
	model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj,true);
}

void Draw::ShadowMapDraw(DirectX::Model* model, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate)
{
}

void Draw::TestSphereModel(
	const float& radian,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotate
)
{
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

	//大きさ
	world = SimpleMath::Matrix::CreateScale(radian);

	//回転
	world *= SimpleMath::Matrix::CreateFromQuaternion(rotate);

	//位置
	world *= SimpleMath::Matrix::CreateTranslation(position);

	//描画
	Draw::GetInstance()->MeshRender(Resources::GetInstance()->GetSphere(), world);
}

//falseで描画する（変えたほうが良いよ）
bool Draw::VisibilityRange(const DirectX::SimpleMath::Vector3& position)
{
	//描画距離か
	//描画範囲外だったらtrue
	if ((m_cameraTarget - position).LengthSquared() >= m_drawDistance)
		return true;

	DirectX::SimpleMath::Vector3 cameraDir = position - m_cameraPosition;
	cameraDir.Normalize();

	//カメラ内か判定するか
	//内積が0.7以かの場合はカメラの後ろなので表示する必要なし
	if (m_cameraDir.Dot(cameraDir) < 0.698f) 
		return true;

	return false;
}

bool Draw::VisibilityRange(const DirectX::SimpleMath::Vector3& position, const float& ModelExtents)
{
	//描画距離か
	//描画範囲外だったらtrue
	
	DirectX::SimpleMath::Vector3 modelCameratyo = m_cameraDir * ModelExtents;
	if ((m_cameraTarget - position).LengthSquared() >= m_drawDistance)
		return true;

	DirectX::SimpleMath::Vector3 cameraDir = (position+ modelCameratyo) - m_cameraPosition;
	cameraDir.Normalize();

	//カメラ内か判定するか
	//内積が0.7以かの場合はカメラの後ろなので表示する必要なし
	if (m_cameraDir.Dot(cameraDir) < 0.3f)
		return true;

	return false;
}

bool Draw::DistanceRange(const DirectX::SimpleMath::Vector3& position)
{
	//距離を計算
	DirectX::SimpleMath::Vector3 cameraDistance = m_cameraTarget - position;

	//描画範囲外だったらtrue
	if ((m_cameraTarget - position).LengthSquared() >= m_drawDistance)
		return true;

	//描画範囲だったらfalse
	return false;
}

bool Draw::UpdateDistance(const DirectX::SimpleMath::Vector3& position, const float& updateDistance)
{
	//距離を計算
	DirectX::SimpleMath::Vector3 cameraDistance = m_cameraTarget - position;

	//描画範囲外だったらtrue
	if (cameraDistance.LengthSquared() >= updateDistance * updateDistance)
		return true;

	//描画範囲だったらfalse
	return false;
}

bool Draw::DespawnDistance(const DirectX::SimpleMath::Vector3& position, const float& despawnDistance)
{
	//距離を計算
	DirectX::SimpleMath::Vector3 cameraDistance = m_cameraTarget - position;

	//デスポーン範囲外だったらtrue
	if (cameraDistance.LengthSquared() >= despawnDistance * despawnDistance)
		return true;

	//デスポーン範囲だったらfalse
	return false;
}


bool Draw::CameraDistanceSort(const DirectX::SimpleMath::Vector3& position_1, const DirectX::SimpleMath::Vector3& position_2)
{
	//カメラとどっちが近いか
	return m_cameraDir.Dot(position_1 - m_cameraPosition) > m_cameraDir.Dot(position_2 - m_cameraPosition);
}

void Draw::CreateBillboard(DirectX::SimpleMath::Matrix& billboard)
{
	//ビルボード行列計算
	billboard = SimpleMath::Matrix::CreateBillboard(
		SimpleMath::Vector3::Zero,
		m_cameraPosition - m_cameraTarget, m_cameraUp
	);

	//ビルボードの回転
	SimpleMath::Matrix rotate = SimpleMath::Matrix::Identity;
	rotate._11 = -1;
	rotate._33 = -1;

	//最終結果
	billboard = rotate * billboard;

}

void Draw::TestCubeModel(
	const DirectX::SimpleMath::Vector3& size,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotate
)
{
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

	//大きさを計算
	world = SimpleMath::Matrix::CreateScale(size);

	//回転を計算
	world *= SimpleMath::Matrix::CreateFromQuaternion(rotate);

	//位置を調整
	world *= SimpleMath::Matrix::CreateTranslation(position);

	//描画
	Draw::GetInstance()->MeshRender(Resources::GetInstance()->GetCube(), world);
}

