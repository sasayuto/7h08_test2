#pragma once
#include "DeviceResources.h"

/// <summary>
/// Textures�N���X���`����
/// </summary>
class SingletonDeviceResources
{
public:
	/// <summary>
	/// �`��N���X�̃C���X�^���X���擾����
	/// </summary>
	/// <returns>�`��N���X�̃C���X�^���X</returns>
	static SingletonDeviceResources* GetInstance();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SingletonDeviceResources();

	DX::DeviceResources* GetDeviceResources() { return m_DeviceResources; };
	void SetDeviceResources(DX::DeviceResources* deviceResources) { m_DeviceResources = deviceResources; };

	// ���ʃX�e�[�g�I�u�W�F�N�g�̃|�C���^
	DirectX::CommonStates* GetCommonStates() { return m_commonStates; };
	void SetCommonStates(DirectX::CommonStates* commonStates) { m_commonStates = commonStates; };

	DirectX::SimpleMath::Matrix* GetProj() { return &m_proj; };

	void Initialize();

private:
	// �`��̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<SingletonDeviceResources> m_SingletonDeviceResources;

	DX::DeviceResources* m_DeviceResources;

	// ���ʃX�e�[�g�I�u�W�F�N�g�̃|�C���^
	DirectX::CommonStates* m_commonStates;

	DirectX::SimpleMath::Matrix m_proj;
};


