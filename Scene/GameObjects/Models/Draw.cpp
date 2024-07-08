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
const float Draw::SHADOW_UPDATE_SECONDS(0.7f);		//�e�̍X�V�b��(�ÓI�I�u�W�F�N�g�̑��z�̍X�V�Ԋu)

//#include <DirectXTex.h>
//
//void SaveRenderTargetToDDS(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, ID3D11RenderTargetView* pRTV, ID3D11DepthStencilView* pDSV, const wchar_t* filename)
//{
//
//	// �r���[����e�N�X�`�����\�[�X�擾
//	ID3D11Resource* cubeMapResource = nullptr;
//	pRTV->GetResource(&cubeMapResource);
//	cubeMapResource->Release();
//
//	// �e�N�X�`���\���\�[�X����A�C���[�W�f�[�^���쐬
//	DirectX::ScratchImage image;
//	DirectX::CaptureTexture(
//		pDevice,
//		pContext,
//		cubeMapResource,
//		image
//	);
//
//	// �C���[�W�f�[�^���t�@�C���֕ۑ�
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

	// �t�@�C�����J����Ă��邩���m�F���܂��B
	if (obj.is_open()) {
		std::string errors;

		// �t�@�C������JSON���p�[�X���܂��B
		if (Json::parseFromStream(reader, obj, &root, &errors))
		{
			// JSON�� "house" �����݂��A�z��ł��邩�ǂ������m�F���܂��B
			if (root.isMember("DrawOption") && root["DrawOption"].isArray())
			{
				m_drawDistance = root["DrawOption"][0]["DRAW_DISTANCE"][0].asFloat();		//���N�[���^�C��	(s)

				//���̋����̐ݒ�
				m_FogFar = m_drawDistance;
				m_FogNear = m_drawDistance - FOG_LENGTH;

				//2��Ŕ�r���邱�Ƃ������̂Ŏ��O�v�Z
				m_drawDistance *= m_drawDistance;
}
		}
		else {
			std::cerr << "JSON�̃p�[�X�G���[: " << errors << std::endl;
		}
		obj.close();
	}
	else {
		std::cerr << "JSON�t�@�C�����J���ۂɃG���[���������܂����B" << std::endl;
	}

	m_cascadeShadowMapManager = std::make_unique<CascadeShadowMapManager>();
	m_cascadeShadowMapManager->Initialize(m_deviceResources, m_cascadeTatgetPos, CASCADE_LIGHT_MAX_NUM, m_FogFar);

	m_att[0] = 0.0f;
	m_att[1] = 0.0f;
	m_att[2] = 1.0f;

	// �s�N�Z���V�F�[�_�[�̍쐬�i�g�[���X�p�j
	std::vector<uint8_t> ps_torus = DX::ReadData(L"Resources/Shaders/LightEffectsPS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreatePixelShader(ps_torus.data(), ps_torus.size(), nullptr, m_PS_Torus.ReleaseAndGetAddressOf())
	);

	// �s�N�Z���V�F�[�_�[�̍쐬�i�g�[���X�p�j
	std::vector<uint8_t> ps_shadow = DX::ReadData(L"Resources/Shaders/ShadowPS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreatePixelShader(ps_shadow.data(), ps_shadow.size(), nullptr, m_PS_Shadow.ReleaseAndGetAddressOf())
	);

	// ���_�V�F�[�_�[�̍쐬�i�V���h�E�}�b�v�p�j
	std::vector<uint8_t> vs_depth = DX::ReadData(L"Resources/Shaders/SM_VS_Depth.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreateVertexShader(vs_depth.data(), vs_depth.size(), nullptr, m_VS_Depth.ReleaseAndGetAddressOf())
	);

	// �s�N�Z���V�F�[�_�[�̍쐬�i�V���h�E�}�b�v�p�j
	std::vector<uint8_t> ps_depth = DX::ReadData(L"Resources/Shaders/SM_PS_Depth.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreatePixelShader(ps_depth.data(), ps_depth.size(), nullptr, m_PS_Depth.ReleaseAndGetAddressOf())
	);


	// ���_�V�F�[�_�[�̍쐬�i�V���h�E�}�b�v�p�j
	std::vector<uint8_t> vs = DX::ReadData(L"Resources/Shaders/SM_VS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreateVertexShader(vs.data(), vs.size(), nullptr, m_VS.ReleaseAndGetAddressOf())
	);
	// ���_�V�F�[�_�[�̍쐬�i�V���h�E�}�b�v�p�j
	vs = DX::ReadData(L"Resources/Shaders/SM_NormalVS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreateVertexShader(vs.data(), vs.size(), nullptr, m_NoormalVS.ReleaseAndGetAddressOf())
	);

	// ���_�V�F�[�_�[�̍쐬�i�V���h�E�}�b�v�p�j
	std::vector<uint8_t> gs = DX::ReadData(L"Resources/Shaders/SM_GS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreateGeometryShader(gs.data(), gs.size(), nullptr, m_GS.ReleaseAndGetAddressOf())
	);

	// �s�N�Z���V�F�[�_�[�̍쐬�i�V���h�E�}�b�v�p�j
	std::vector<uint8_t> ps = DX::ReadData(L"Resources/Shaders/SM_PS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreatePixelShader(ps.data(), ps.size(), nullptr, m_PS.ReleaseAndGetAddressOf())
	);
	// �s�N�Z���V�F�[�_�[�̍쐬�i�V���h�E�}�b�v�p�j
	 ps = DX::ReadData(L"Resources/Shaders/SM_NormalPS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreatePixelShader(ps.data(), ps.size(), nullptr, m_NoormalPS.ReleaseAndGetAddressOf())
	);
	// ���_�V�F�[�_�[�̍쐬�i�V���h�E�}�b�v�p�j
	std::vector<uint8_t> no_picture_vs_depth = DX::ReadData(L"Resources/Shaders/SM_No_Picture_VS_Depth.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreateVertexShader(no_picture_vs_depth.data(), no_picture_vs_depth.size(), nullptr, m_NoPicture_VS_Depth.ReleaseAndGetAddressOf())
	);

	// �s�N�Z���V�F�[�_�[�̍쐬�i�V���h�E�}�b�v�p�j
	std::vector<uint8_t> no_picture_ps_depth = DX::ReadData(L"Resources/Shaders/SM_No_Picture_PS_Depth.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreatePixelShader(no_picture_ps_depth.data(), no_picture_ps_depth.size(), nullptr, m_NoPicture_PS_Depth.ReleaseAndGetAddressOf())
	);


	// ���_�V�F�[�_�[�̍쐬�i�V���h�E�}�b�v�p�j
	std::vector<uint8_t> no_picture_vs = DX::ReadData(L"Resources/Shaders/SM_No_Picture_VS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreateVertexShader(no_picture_vs.data(), no_picture_vs.size(), nullptr, m_NoPictureVS.ReleaseAndGetAddressOf())
	);

	// �s�N�Z���V�F�[�_�[�̍쐬�i�V���h�E�}�b�v�p�j
	std::vector<uint8_t> no_picture_ps = DX::ReadData(L"Resources/Shaders/SM_No_Picture_PS.cso");
	DX::ThrowIfFailed(
		m_pDevice->CreatePixelShader(no_picture_ps.data(), no_picture_ps.size(), nullptr, m_NoPicturePS.ReleaseAndGetAddressOf())
	);

	// �T���v���[�̍쐬�i�V���h�E�}�b�v�p�j
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
	// �f�o�C�X�ɖ@���}�b�v�̃T���v���[�X�e�[�g���쐬
	m_pDevice->CreateSamplerState(&sampler_desc, m_NormalMapSampler.ReleaseAndGetAddressOf());
	//--------------------------------------------------------------------
	//	�V���h�E�}�b�v�p
	//--------------------------------------------------------------------


	// �萔�o�b�t�@�̍쐬
	D3D11_BUFFER_DESC bufferDesc2 = {};
	bufferDesc2.ByteWidth = static_cast<UINT>(sizeof(ConstantBuffer));	// �m�ۂ���T�C�Y�i16�̔{���Őݒ肷��j
	// GPU (�ǂݎ���p) �� CPU (�������ݐ�p) �̗�������A�N�Z�X�ł��郊�\�[�X
	bufferDesc2.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// �萔�o�b�t�@�Ƃ��Ĉ���
	bufferDesc2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPU�����e��ύX�ł���悤�ɂ���
	DX::ThrowIfFailed(m_pDevice->CreateBuffer(&bufferDesc2, nullptr, m_constantBuffer2.ReleaseAndGetAddressOf()));

	// �萔�o�b�t�@�̍쐬
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(ConstantBuffer2));	// �m�ۂ���T�C�Y�i16�̔{���Őݒ肷��j
	// GPU (�ǂݎ���p) �� CPU (�������ݐ�p) �̗�������A�N�Z�X�ł��郊�\�[�X
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// �萔�o�b�t�@�Ƃ��Ĉ���
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPU�����e��ύX�ł���悤�ɂ���
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
	//���łɐ�������Ă邩�`�F�b�N
	if (m_draw == nullptr)
	{
		//�`��̃C���X�^���X�𐶐�����
		m_draw = std::make_unique<Draw>();
	}
	//�`��̃C���X�^���X��Ԃ�
	return m_draw.get();
}

void Draw::StaticShadowMapTexCreateStart(int index,float timer)
{
	timer;
	m_cascadeIndex = index;
	m_cascadeTatgetPos = GetEyePosition();
	// �r���[�|�[�g��ݒ�
	D3D11_VIEWPORT vp = { 0.0f, 0.0f, static_cast<float>(CascadeShadowMapManager::SHADOWMAP_SIZE), static_cast<float>(CascadeShadowMapManager::SHADOWMAP_SIZE), 0.0f, 1.0f };
	m_pContext->RSSetViewports(1, &vp); 

	auto rtv = m_cascadeShadowMapManager->GetRenderTexture(index)->GetRenderTargetView();
	auto dsv = m_cascadeShadowMapManager->GetDepthStencil(index)->GetDepthStencilView();

	// �����_�[�^�[�Q�b�g��ύX�ishadowMapRT�j
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

	// �r���[�|�[�g��ݒ�
	D3D11_VIEWPORT vp = { 0.0f, 0.0f, static_cast<float>(CascadeShadowMapManager::SHADOWMAP_SIZE), static_cast<float>(CascadeShadowMapManager::SHADOWMAP_SIZE), 0.0f, 1.0f };
	m_pContext->RSSetViewports(1, &vp);

	auto rtv = m_cascadeShadowMapManager->GetMoveRenderTexture(index)->GetRenderTargetView();
	auto dsv = m_cascadeShadowMapManager->GetMoveDepthStencil(index)->GetDepthStencilView();

	// �����_�[�^�[�Q�b�g��ύX�ishadowMapRT�j
	m_pContext->ClearRenderTargetView(rtv, SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f));
	m_pContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_pContext->OMSetRenderTargets(1, &rtv, dsv);
}


void Draw::ShadowMapTexCreate(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world)
{
	// �g�[���X�̕`��
	model->Draw(m_pContext, *m_commonStates, world, m_cascadeShadowMapManager->GetMoveLightView(), m_cascadeShadowMapManager->GetLightProj(m_cascadeIndex), false, [&]()
		{
			m_pContext->VSSetShader(m_VS_Depth.Get(), nullptr, 0);
			m_pContext->PSSetShader(m_PS_Depth.Get(), nullptr, 0);
		}
	);

}

void Draw::ShadowMapTexCreateNoPicture(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world)
{	
	// �g�[���X�̕`��
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

	// GPU���萔�o�b�t�@�ɑ΂��ăA�N�Z�X���s��Ȃ��悤�ɂ���
	m_pContext->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// �萔�o�b�t�@���X�V
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

	// GPU���萔�o�b�t�@�ɑ΂��ẴA�N�Z�X��������
	m_pContext->Unmap(m_constantBuffer.Get(), 0);

	model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj, false, [&]()
		{
			// �萔�o�b�t�@�̐ݒ�
			ID3D11Buffer* cbuf[] = { m_constantBuffer.Get() };
			m_pContext->VSSetConstantBuffers(1, 1, cbuf);
			m_pContext->PSSetConstantBuffers(1, 1, cbuf);

			// �e�N�X�`���T���v���[�̐ݒ�
			ID3D11SamplerState* samplers[] = { m_commonStates->PointWrap(), m_shadowMapSampler.Get() };
			m_pContext->PSSetSamplers(0, 2, samplers);

			// �V�F�[�_�[�̐ݒ�
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
		//// const wchar_t* �ɕϊ�PSSetShaderResources
		//const wchar_t* filenameCStr = filename.c_str();
		//SaveRenderTargetToDDS(m_pDevice, m_pContext, renderTargetTex, depthStencilTex, filenameCStr);
		srv = m_cascadeShadowMapManager->GetMoveRenderTexture(index)->GetShaderResourceView();
		m_pContext->PSSetShaderResources(index + 3 + CASCADE_LIGHT_MAX_NUM, 1, &srv);

	}
}

void Draw::ShadowMapTexCreateEndCon()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	// GPU���萔�o�b�t�@�ɑ΂��ăA�N�Z�X���s��Ȃ��悤�ɂ���
	m_pContext->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// �萔�o�b�t�@���X�V
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

	// GPU���萔�o�b�t�@�ɑ΂��ẴA�N�Z�X��������
	m_pContext->Unmap(m_constantBuffer.Get(), 0);

	// �萔�o�b�t�@�̐ݒ�
	ID3D11Buffer* cbuf[] = { m_constantBuffer.Get() };
	m_pContext->VSSetConstantBuffers(1, 1, cbuf);
	m_pContext->PSSetConstantBuffers(1, 1, cbuf);

}

void Draw::DrawEndUpdate()
{
	// ���\�[�X�̊��蓖�Ă���������ishadowMapRT�j
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

			// �e�N�X�`���T���v���[�̐ݒ�
			ID3D11SamplerState* samplers[] = { m_commonStates->PointWrap(), m_shadowMapSampler.Get() ,m_NormalMapSampler.Get() };
			m_pContext->PSSetSamplers(0, 3, samplers);

			// �V�F�[�_�[�̐ݒ�
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

			// �e�N�X�`���T���v���[�̐ݒ�
			ID3D11SamplerState* samplers[] = { m_commonStates->PointWrap(), m_shadowMapSampler.Get() ,m_NormalMapSampler.Get()};
			m_pContext->PSSetSamplers(0, 3, samplers);

			// �V�F�[�_�[�̐ݒ�
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

			// �e�N�X�`���T���v���[�̐ݒ�
			ID3D11SamplerState* samplers[] = { m_commonStates->PointWrap(), m_shadowMapSampler.Get() };
			m_pContext->PSSetSamplers(0, 2, samplers);

			// �V�F�[�_�[�̐ݒ�
			m_pContext->VSSetShader(m_NoPictureVS.Get(), nullptr, 0);
			m_pContext->PSSetShader(m_NoPicturePS.Get(), nullptr, 0);
		}
	);
}

void Draw::Render(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world)
{
	//// �g�[���X���f���̃G�t�F�N�g��ݒ肷��
	//model->UpdateEffects([&](IEffect* effect)
	//	{
	//		auto basicEffect = dynamic_cast<BasicEffect*>(effect);
	//		if (basicEffect)
	//		{
	//			basicEffect->SetPerPixelLighting(true);
	//		}
	//	}
	//);

	////���f����`��
	//model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj, false, [&]()
	//	{
	//		// �I���W�i���s�N�Z���V�F�[�_�[�̐ݒ�
	//		D3D11_MAPPED_SUBRESOURCE mappedResource;
	//		// GPU���萔�o�b�t�@�ɑ΂��ăA�N�Z�X���s��Ȃ��悤�ɂ���
	//		m_pContext->Map(m_CBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	//		// �萔�o�b�t�@���X�V
	//		ConstantBuffer cb = { m_lightPosition };
	//		*static_cast<ConstantBuffer*>(mappedResource.pData) = cb;
	//		// GPU���萔�o�b�t�@�ɑ΂��ẴA�N�Z�X��������
	//		m_pContext->Unmap(m_CBuffer.Get(), 0);
	//		// �s�N�Z���V�F�[�_�g�p����萔�o�b�t�@��ݒ�
	//		ID3D11Buffer* cbuf_ps[] = { m_CBuffer.Get() };

	//		// �I���W�i���s�N�Z���V�F�[�_�[�̐ݒ�
	//		m_pContext->PSSetShader(m_pixelShader.Get(), nullptr, 0);
	//	}
	//);
	// 
	//���f���̐ݒ�
	model->UpdateEffects([&](IEffect* effect)
		{
			auto basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				//���̕����ƐF
				basicEffect->SetLightDirection(true, SimpleMath::Vector3(-m_cascadeShadowMapManager->GetLightDir()));
				basicEffect->SetLightDiffuseColor(false, SimpleMath::Color(0.4f, 0.4f, 0.4f, 0.5f));

				//���x
				basicEffect->SetAlpha(m_sun->GetObjectsRight());
			}
		}
	);

	//���f����`��
	model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj);
}


void Draw::Rendersss(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world)
{
	//// �ˉe�s��̍쐬
//*m_proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
//	XMConvertToRadians(45.0f), static_cast<float>(m_width) / static_cast<float>(m_height), 0.1f, drawingDistance);

//// �g�[���X���f���̃G�t�F�N�g��ݒ肷��
//model->UpdateEffects([&](IEffect* effect)
//	{
//		auto basicEffect = dynamic_cast<BasicEffect*>(effect);
//		if (basicEffect)
//		{
//			basicEffect->SetPerPixelLighting(true);
//		}
//	}
//);

////���f����`��
//model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj, false, [&]()
//	{
//		// �I���W�i���s�N�Z���V�F�[�_�[�̐ݒ�
//		D3D11_MAPPED_SUBRESOURCE mappedResource;
//		// GPU���萔�o�b�t�@�ɑ΂��ăA�N�Z�X���s��Ȃ��悤�ɂ���
//		m_pContext->Map(m_CBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
//		// �萔�o�b�t�@���X�V
//		ConstantBuffer cb = { m_lightPosition };
//		*static_cast<ConstantBuffer*>(mappedResource.pData) = cb;
//		// GPU���萔�o�b�t�@�ɑ΂��ẴA�N�Z�X��������
//		m_pContext->Unmap(m_CBuffer.Get(), 0);
//		// �s�N�Z���V�F�[�_�g�p����萔�o�b�t�@��ݒ�
//		ID3D11Buffer* cbuf_ps[] = { m_CBuffer.Get() };

//		// �I���W�i���s�N�Z���V�F�[�_�[�̐ݒ�
//		m_pContext->PSSetShader(m_pixelShader.Get(), nullptr, 0);
//	}
//);

// �g�[���X���f���̃G�t�F�N�g��ݒ肷��
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
			// �萔�o�b�t�@���X�V
			D3D11_MAPPED_SUBRESOURCE mappedResource;

			// GPU���萔�o�b�t�@�ɑ΂��ăA�N�Z�X���s��Ȃ��悤�ɂ���
			m_pContext->Map(m_constantBuffer2.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

			// �萔�o�b�t�@���X�V
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

			// GPU���萔�o�b�t�@�ɑ΂��ẴA�N�Z�X��������
			m_pContext->Unmap(m_constantBuffer2.Get(), 0);

			// �s�N�Z���V�F�[�_�g�p����萔�o�b�t�@��ݒ�
			ID3D11Buffer* cbuf_ps[] = { m_constantBuffer2.Get() };
			m_pContext->PSSetConstantBuffers(1, 1, cbuf_ps);	// �X���b�g�O��DirectXTK���g�p���Ă���̂ŃX���b�g�P���g�p����

			// �I���W�i���s�N�Z���V�F�[�_�[�̐ݒ�
			m_pContext->PSSetShader(m_PS_Torus.Get(), nullptr, 0);
		}
	);

}

void Draw::kari(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world)
{
	//���f���̐ݒ�
	model->UpdateEffects([&](IEffect* effect)
		{
			auto basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				//���̕����ƐF
				basicEffect->SetLightDirection(true, SimpleMath::Vector3(m_cascadeShadowMapManager->GetLightDir()));
				basicEffect->SetLightDiffuseColor(false, SimpleMath::Color(0.4f, 0.4f, 0.4f, 0.5f));

				//���x
				basicEffect->SetAlpha(m_sun->GetObjectsRight());
			}
		}
	);

	//���f����`��
	model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj);

}

void Draw::LightRender(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world)
{	
	//���f���̐ݒ�
	model->UpdateEffects([&](IEffect* effect)
		{
			auto basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				//���x���Ȃ���
				basicEffect->SetAlpha(true);

				//���̋���
				basicEffect->SetEmissiveColor(DirectX::SimpleMath::Color(1, 1, 1, 1));
			}
		}
	);

	//���f����`��
	model->Draw(m_pContext, *m_commonStates, world, m_view, *m_proj);

}


void Draw::MeshRender(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world)
{
	//���f����`��
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

	//�傫��
	world = SimpleMath::Matrix::CreateScale(radian);

	//��]
	world *= SimpleMath::Matrix::CreateFromQuaternion(rotate);

	//�ʒu
	world *= SimpleMath::Matrix::CreateTranslation(position);

	//�`��
	Draw::GetInstance()->MeshRender(Resources::GetInstance()->GetSphere(), world);
}

//false�ŕ`�悷��i�ς����ق����ǂ���j
bool Draw::VisibilityRange(const DirectX::SimpleMath::Vector3& position)
{
	//�`�拗����
	//�`��͈͊O��������true
	if ((m_cameraTarget - position).LengthSquared() >= m_drawDistance)
		return true;

	DirectX::SimpleMath::Vector3 cameraDir = position - m_cameraPosition;
	cameraDir.Normalize();

	//�J�����������肷�邩
	//���ς�0.7�Ȃ��̏ꍇ�̓J�����̌��Ȃ̂ŕ\������K�v�Ȃ�
	if (m_cameraDir.Dot(cameraDir) < 0.698f) 
		return true;

	return false;
}

bool Draw::VisibilityRange(const DirectX::SimpleMath::Vector3& position, const float& ModelExtents)
{
	//�`�拗����
	//�`��͈͊O��������true
	
	DirectX::SimpleMath::Vector3 modelCameratyo = m_cameraDir * ModelExtents;
	if ((m_cameraTarget - position).LengthSquared() >= m_drawDistance)
		return true;

	DirectX::SimpleMath::Vector3 cameraDir = (position+ modelCameratyo) - m_cameraPosition;
	cameraDir.Normalize();

	//�J�����������肷�邩
	//���ς�0.7�Ȃ��̏ꍇ�̓J�����̌��Ȃ̂ŕ\������K�v�Ȃ�
	if (m_cameraDir.Dot(cameraDir) < 0.3f)
		return true;

	return false;
}

bool Draw::DistanceRange(const DirectX::SimpleMath::Vector3& position)
{
	//�������v�Z
	DirectX::SimpleMath::Vector3 cameraDistance = m_cameraTarget - position;

	//�`��͈͊O��������true
	if ((m_cameraTarget - position).LengthSquared() >= m_drawDistance)
		return true;

	//�`��͈͂�������false
	return false;
}

bool Draw::UpdateDistance(const DirectX::SimpleMath::Vector3& position, const float& updateDistance)
{
	//�������v�Z
	DirectX::SimpleMath::Vector3 cameraDistance = m_cameraTarget - position;

	//�`��͈͊O��������true
	if (cameraDistance.LengthSquared() >= updateDistance * updateDistance)
		return true;

	//�`��͈͂�������false
	return false;
}

bool Draw::DespawnDistance(const DirectX::SimpleMath::Vector3& position, const float& despawnDistance)
{
	//�������v�Z
	DirectX::SimpleMath::Vector3 cameraDistance = m_cameraTarget - position;

	//�f�X�|�[���͈͊O��������true
	if (cameraDistance.LengthSquared() >= despawnDistance * despawnDistance)
		return true;

	//�f�X�|�[���͈͂�������false
	return false;
}


bool Draw::CameraDistanceSort(const DirectX::SimpleMath::Vector3& position_1, const DirectX::SimpleMath::Vector3& position_2)
{
	//�J�����Ƃǂ������߂���
	return m_cameraDir.Dot(position_1 - m_cameraPosition) > m_cameraDir.Dot(position_2 - m_cameraPosition);
}

void Draw::CreateBillboard(DirectX::SimpleMath::Matrix& billboard)
{
	//�r���{�[�h�s��v�Z
	billboard = SimpleMath::Matrix::CreateBillboard(
		SimpleMath::Vector3::Zero,
		m_cameraPosition - m_cameraTarget, m_cameraUp
	);

	//�r���{�[�h�̉�]
	SimpleMath::Matrix rotate = SimpleMath::Matrix::Identity;
	rotate._11 = -1;
	rotate._33 = -1;

	//�ŏI����
	billboard = rotate * billboard;

}

void Draw::TestCubeModel(
	const DirectX::SimpleMath::Vector3& size,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotate
)
{
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

	//�傫�����v�Z
	world = SimpleMath::Matrix::CreateScale(size);

	//��]���v�Z
	world *= SimpleMath::Matrix::CreateFromQuaternion(rotate);

	//�ʒu�𒲐�
	world *= SimpleMath::Matrix::CreateTranslation(position);

	//�`��
	Draw::GetInstance()->MeshRender(Resources::GetInstance()->GetCube(), world);
}

