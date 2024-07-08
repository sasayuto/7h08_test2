//--------------------------------------------------------------------------------------
// File: ParticleSandstorm.cpp
//
// �p�[�e�B�N���N���X
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
/// �C���v�b�g���C�A�E�g
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> ParticleSandstorm::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0,							 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
ParticleSandstorm::ParticleSandstorm():
	m_brightness(),
	m_emissiveColor(DirectX::SimpleMath::Vector3::Zero)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ParticleSandstorm::~ParticleSandstorm()
{
}

/// <summary>
/// �e�N�X�`�����\�[�X�ǂݍ��݊֐�
/// </summary>
/// <param name="path">���΃p�X(Resources/Textures/�E�E�E.png�Ȃǁj</param>
void ParticleSandstorm::LoadTexture(const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	DirectX::CreateWICTextureFromFile(SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice(), path, nullptr, texture.ReleaseAndGetAddressOf());
	
	m_texture.push_back(texture);
}

/// <summary>
/// �����֐�
/// </summary>
/// <param name="pDR">���[�U�[���\�[�X�����玝���Ă���</param>
void ParticleSandstorm::Create(wchar_t const* fileName)
{	
	auto device = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//�V�F�[�_�[�̍쐬
	CreateShader();

	//�摜�̓ǂݍ��݁i�Q���Ƃ��f�t�H���g�͓ǂݍ��ݎ��s��nullptr)
	LoadTexture(fileName);

	// �v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());

	m_states = std::make_unique<CommonStates>(device);

}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">Game������StepTimer���󂯎��</param>
void ParticleSandstorm::Update(float elapsedTime)
{
	//timer��n����m_effect�̍X�V�������s��
	for (std::list<ParticleUtility>::iterator ite = m_ParticleSandstormUtility.begin(); ite != m_ParticleSandstormUtility.end(); ite++)
	{
		// �q�N���X����false�ŏ���
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
	//timer��n����m_effect�̍X�V�������s��
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
/// Shader�쐬�����������������֐�
/// </summary>
void ParticleSandstorm::CreateShader()
{
	auto device = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");
	
	//�C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	// ���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	// �W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	// �s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	//�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);
}

/// <summary>
/// �`��֐�
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void ParticleSandstorm::Render()
{
	auto context = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	// ���_���(�|���S���̂S���_�̍��W���j

	m_ParticleSandstormUtility.sort(
		[&](ParticleUtility lhs, ParticleUtility  rhs)
			{
				//�J�������ʂ̋����Ń\�[�g
			return Draw::GetInstance()->CameraDistanceSort(lhs.GetPosition(), rhs.GetPosition());
		});
	//�o�^����Ă��钸�_�����Z�b�g
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
		
	//�\������_���Ȃ��ꍇ�͕`����I���
	if (m_vertices.empty())
	{
		return;
	}
	DirectX::SimpleMath::Vector3 eyePos = Draw::GetInstance()->GetEyePosition();

	//�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	DirectX::SimpleMath::Matrix proj = *SingletonDeviceResources::GetInstance()->GetProj();
	cbuff.matView = Draw::GetInstance()->GetView().Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = m_billboard.Transpose();
	cbuff.Brightness = SimpleMath::Vector4(m_brightness, m_emissiveColor.x, m_emissiveColor.y, m_emissiveColor.z);
	cbuff.EyePosition = DirectX::SimpleMath::Vector4(eyePos.x, eyePos.y, eyePos.z, Draw::GetInstance()->GetFogFar());
	//�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//�������`��w��
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthRead(), 0);

	// �J�����O�͍�����
	context->RSSetState(m_states->CullNone());

	//�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	for (int i = 0; i < m_texture.size(); i++)
	{
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	//�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	// �|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());
	m_batch->End();

	//�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}
