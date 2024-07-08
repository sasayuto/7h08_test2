//--------------------------------------------------------------------------------------
// File: UserInterface.h
//
// ���[�U�[�C���^�[�t�F�[�X�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "NumberManager.h"
#include"Scene/GameObjects/Models/Textures.h"

#include "ImaseLib/BinaryFile.h"


using namespace DirectX;

/// <summary>
/// �C���v�b�g���C�A�E�g
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> tito::NumberManager::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(SimpleMath::Vector3)+ sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
tito::NumberManager::NumberManager()
	:m_windowHeight(0)
	,m_windowWidth(0)
	,m_texture(nullptr)
	,m_res(nullptr)
	,m_position(SimpleMath::Vector2::Zero)
	,m_anchor(ANCHOR::TOP_LEFT),
	m_transparency(1),
	m_number()
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
tito::NumberManager::~NumberManager()
{
}

/// <summary>
/// �����֐�
/// </summary>
/// <param name="pDR">���[�U�[���\�[�X�����玝���Ă���</param>
void tito::NumberManager::Create(
	DirectX::SimpleMath::Vector2 position
	,DirectX::SimpleMath::Vector2 scale
	, const int& number
	, ANCHOR anchor
)
{
	auto device = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	m_scale = scale;
	m_number = number;
	m_position = position;
	m_anchor = anchor;

	//�V�F�[�_�[�̍쐬
	CreateShader();

	//�摜�̓ǂݍ���
	DirectX::CreateWICTextureFromFile(device, L"Resources/Textures/Number_01.png", m_res.ReleaseAndGetAddressOf(), m_texture.ReleaseAndGetAddressOf());

	// �v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);

	m_states = std::make_unique<CommonStates>(device);

	//�E�B���h�E�T�C�Y���擾�i�V�F�[�_�[�͔䗦�Ȃ̂Ńt���X�N���[���̑Ή��E�B���h�E�T�C�Y�j
	m_windowHeight = Textures::GetInstance()->GetFullScreenNoneWindowHeight();
	m_windowWidth = Textures::GetInstance()->GetFullScreenNoneWindowWidth();
}

/// <summary>
/// Shader�쐬�����������������֐�
/// </summary>
void tito::NumberManager::CreateShader()
{
	auto device = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/NumberVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/NumberGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/NumberPS.cso");

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
void tito::NumberManager::Render()
{
	auto context = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

		// ���_���
		// Position.xy	:�g�k�p�X�P�[��
		// Position.z	:�A���J�[�^�C�v(0�`8)�̐����Ŏw��
		// Color.xy�@	:�A���J�[���W(�s�N�Z���w��:1280 �~720)
		// Color.zw		:�摜�T�C�Y
		// Tex.xy		:�E�B���h�E�T�C�Y�i�o�b�t�@�������B������͖��g�p�j
	VertexPositionColorTexture vertex[1] = {
		VertexPositionColorTexture(SimpleMath::Vector3(m_scale.x,m_scale.y, static_cast<float>(m_anchor))
		, SimpleMath::Vector4(m_position.x, m_position.y,0,0)
		, SimpleMath::Vector2(static_cast<float>(m_number),m_transparency))
	};

	//�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.windowSize = SimpleMath::Vector4(static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight), 0, 0);
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

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// �J�����O�͍�����
	context->RSSetState(m_states->CullNone());

	//�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	//�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	// �|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch->End();

	//�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}
