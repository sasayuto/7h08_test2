//--------------------------------------------------------------------------------------
// File: ParticleSandstorm.cpp
//
// パーティクルクラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "ParticleSandstorm.h"
#include"Scene/GameObjects/Models/Textures.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/PlayScene/Sun/Sun.h"
#include "BinaryFile.h"

using namespace DirectX;

/// <summary>
/// インプットレイアウト
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> ParticleSandstorm::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0,							 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// コンストラクタ
/// </summary>
ParticleSandstorm::ParticleSandstorm():
	m_brightness(),
	m_emissiveColor(DirectX::SimpleMath::Vector3::Zero)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ParticleSandstorm::~ParticleSandstorm()
{
}

/// <summary>
/// テクスチャリソース読み込み関数
/// </summary>
/// <param name="path">相対パス(Resources/Textures/・・・.pngなど）</param>
void ParticleSandstorm::LoadTexture(const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	DirectX::CreateWICTextureFromFile(SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice(), path, nullptr, texture.ReleaseAndGetAddressOf());
	
	m_texture.push_back(texture);
}

/// <summary>
/// 生成関数
/// </summary>
/// <param name="pDR">ユーザーリソース等から持ってくる</param>
void ParticleSandstorm::Create(wchar_t const* fileName)
{	
	auto device = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//シェーダーの作成
	CreateShader();

	//画像の読み込み（２枚ともデフォルトは読み込み失敗でnullptr)
	LoadTexture(fileName);

	// プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());

	m_states = std::make_unique<CommonStates>(device);

}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">Game等からStepTimerを受け取る</param>
void ParticleSandstorm::Update(float elapsedTime)
{
	//timerを渡してm_effectの更新処理を行う
	for (std::list<ParticleUtility>::iterator ite = m_ParticleSandstormUtility.begin(); ite != m_ParticleSandstormUtility.end(); ite++)
	{
		// 子クラスからfalseで消す
		if (!(ite)->Update(elapsedTime))
		{
			ite = m_ParticleSandstormUtility.erase(ite);
			if (ite == m_ParticleSandstormUtility.end()) break;
		}
	}
	m_brightness = Textures::GetInstance()->GetSun()->GetObjectsRight();
	m_emissiveColor;
}

void ParticleSandstorm::RotateUpdate()
{
	//timerを渡してm_effectの更新処理を行う
	for (std::list<ParticleUtility>::iterator ite = m_ParticleSandstormUtility.begin(); ite != m_ParticleSandstormUtility.end(); ite++)
	{
		ite->RotateUpdate();
	}
}

void ParticleSandstorm::Add(ParticleUtility* ParticleUtility)
{
	m_ParticleSandstormUtility.push_back(*ParticleUtility);
}


/// <summary>
/// Shader作成部分だけ分離した関数
/// </summary>
void ParticleSandstorm::CreateShader()
{
	auto device = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");
	
	//インプットレイアウトの作成
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	// 頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	// ジオメトリシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	// ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	//シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);
}

/// <summary>
/// 描画関数
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void ParticleSandstorm::Render()
{
	auto context = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	// 頂点情報(板ポリゴンの４頂点の座標情報）

	m_ParticleSandstormUtility.sort(
		[&](ParticleUtility lhs, ParticleUtility  rhs)
			{
				//カメラ正面の距離でソート
			return Draw::GetInstance()->CameraDistanceSort(lhs.GetPosition(), rhs.GetPosition());
		});
	//登録されている頂点をリセット
	m_vertices.clear();

	for (auto& li : m_ParticleSandstormUtility)
	{
		if(Draw::GetInstance()->DistanceRange(li.GetPosition())) continue;

		VertexPositionColorTexture vPCT{};
		vPCT.position = XMFLOAT3(li.GetPosition());
		vPCT.color = XMFLOAT4(li.GetNowColor());
		vPCT.textureCoordinate = XMFLOAT2(li.GetNowScale().x, Draw::GetInstance()->GetFogNear());
			
		m_vertices.push_back(vPCT);
	}
		
	//表示する点がない場合は描画を終わる
	if (m_vertices.empty())
	{
		return;
	}
	DirectX::SimpleMath::Vector3 eyePos = Draw::GetInstance()->GetEyePosition();

	//シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	DirectX::SimpleMath::Matrix proj = *SingletonDeviceResources::GetInstance()->GetProj();
	cbuff.matView = Draw::GetInstance()->GetView().Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = m_billboard.Transpose();
	cbuff.Brightness = SimpleMath::Vector4(m_brightness, m_emissiveColor.x, m_emissiveColor.y, m_emissiveColor.z);
	cbuff.EyePosition = DirectX::SimpleMath::Vector4(eyePos.x, eyePos.y, eyePos.z, Draw::GetInstance()->GetFogFar());
	//受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//半透明描画指定
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	// 透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// 深度バッファに書き込み参照する
	context->OMSetDepthStencilState(m_states->DepthRead(), 0);

	// カリングは左周り
	context->RSSetState(m_states->CullNone());

	//シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//ピクセルシェーダにテクスチャを登録する。
	for (int i = 0; i < m_texture.size(); i++)
	{
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	//インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	// 板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());
	m_batch->End();

	//シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}
