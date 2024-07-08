#include "pch.h"
#include "Textures.h"

using namespace DirectX;
std::unique_ptr<Textures> Textures::m_textures = nullptr;

Textures::Textures() :
	m_proj(SimpleMath::Matrix::Identity),
	m_pContext(),
	m_pDevice(),
	m_windowHeight(),
	m_windowWidth(),
	m_fullScreenNoneWindowHeight(),
	m_fullScreenNoneWindowWidth()
{
}

Textures* Textures::GetInstance()
{
	//���łɐ�������Ă邩�`�F�b�N
	if (m_textures == nullptr)
	{
		//�摜�̃C���X�^���X�𐶐�����
		m_textures = std::make_unique<Textures>();
	}
	//�摜�̃C���X�^���X��Ԃ�
	return m_textures.get();
}

void Textures::LoadResource()
{
	m_pDevice = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	DirectX::CreateWICTextureFromFile(m_pDevice, L"Resources/Textures/light.png", nullptr, m_Coinlight.ReleaseAndGetAddressOf());
	DX::ThrowIfFailed(CreateDDSTextureFromFile(m_pDevice, L"Resources/Textures/NoNormalMap.dds", nullptr, m_NoNormalMap.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(CreateDDSTextureFromFile(m_pDevice, L"Resources/Textures/House_01NormalMap.dds", nullptr, m_House_01NormalMap.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(CreateDDSTextureFromFile(m_pDevice, L"Resources/Textures/House_01SpecularMap.dds", nullptr, m_PillarTexture_01NormalMap.ReleaseAndGetAddressOf()));
	DirectX::CreateWICTextureFromFile(m_pDevice, L"Resources/Textures/Smoke_02.png", nullptr, m_smoke.ReleaseAndGetAddressOf());

}

