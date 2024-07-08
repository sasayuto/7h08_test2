#pragma once
#include <combaseapi.h>
#include <pch.h>

// ITurretComponent�C���^�t�F�[�X���`����
interface  IPlayerComponent
{
	// �e���擾����
	virtual IPlayerComponent* GetParent() = 0;

	// �f�X�g���N�^
	virtual ~IPlayerComponent() = default;

	// ����������
	virtual void Initialize() = 0;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	virtual void Update(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle) = 0;

	// �`�悷��
	virtual void Render() = 0;

	// ��������
	virtual void Explosion(float gravity) = 0;

	// �`�悷��
	virtual void Speed() = 0;

	// �㏈���������Ȃ�
	virtual void Finalize() = 0;
};
