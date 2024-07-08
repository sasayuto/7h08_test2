#include "pch.h"
#include "SingletonDeviceResources.h"

using namespace DirectX;
std::unique_ptr<SingletonDeviceResources> SingletonDeviceResources::m_SingletonDeviceResources = nullptr;

SingletonDeviceResources::SingletonDeviceResources()
{
}

void SingletonDeviceResources::Initialize()
{
	RECT WindouSize = m_DeviceResources->GetOutputSize();
	// �ˉe�s��̍쐬
	m_proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f), static_cast<float>(WindouSize.right) / static_cast<float>(WindouSize.bottom), 0.1f, 10000);

}

SingletonDeviceResources* SingletonDeviceResources::GetInstance()
{
	//���łɐ�������Ă邩�`�F�b�N
	if (m_SingletonDeviceResources == nullptr)
	{
		//�摜�̃C���X�^���X�𐶐�����
		m_SingletonDeviceResources = std::make_unique<SingletonDeviceResources>();
	}
	//�摜�̃C���X�^���X��Ԃ�
	return m_SingletonDeviceResources.get();
}

