#pragma once
#include <combaseapi.h>

#include"ITurretComponent.h"

class BulletManager;
/// <summary>
/// ITurretPartFactory�C���^�t�F�[�X���`����
/// </summary>
interface ITurretPartFactory
{	
	/// <summary>
	///�@�^���b�g�̓y��𐶐�����
	/// </summary>
	/// <param name="parent">���̊Ǘ��҂̃|�C���^</param>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�^���b�g�̓y��̃A�h���X</returns>
	virtual std::unique_ptr<ITurretComponent> CreateTurretBase(
		const BulletManager* bulletManager,
		const ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;
	/// <summary>
	///�@�^���b�g�̐^�񒆂̑�C�𐶐�����
	/// </summary>
	/// <param name="parent">���̊Ǘ��҂̃|�C���^</param>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�^���b�g�̐^�񒆂̑�C�̃A�h���X</returns>
	virtual std::unique_ptr<ITurretComponent> CreateTurretCancer_Middle(
		const BulletManager* bulletManager,
		const ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@�^���b�g�̍��̑�C�𐶐�����
	/// </summary>
	/// <param name="parent">���̊Ǘ��҂̃|�C���^</param>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�^���b�g�̍��̑�C�̃A�h���X</returns>
	virtual std::unique_ptr<ITurretComponent> CreateTurretCancer_Left(
		const BulletManager* bulletManager,
		const ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@�^���b�g�̉E�̑�C�𐶐�����
	/// </summary>
	/// <param name="parent">���̊Ǘ��҂̃|�C���^</param>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�^���b�g�̉E�̑�C�̃A�h���X</returns>
	virtual std::unique_ptr<ITurretComponent> CreateTurretCancer_Right(
		const BulletManager* bulletManager,
		const ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@�^���b�g�̓��𐶐�����
	/// </summary>
	/// <param name="parent">���̊Ǘ��҂̃|�C���^</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�^���b�g�̓��̃A�h���X</returns>
	virtual std::unique_ptr<ITurretComponent> CreateTurretHead(
		const BulletManager* bulletManager,
		const ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;
};
