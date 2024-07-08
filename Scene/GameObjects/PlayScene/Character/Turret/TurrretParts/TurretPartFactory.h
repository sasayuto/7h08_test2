#pragma once
#include "ITurretComponent.h"
#include "ITurretPartFactory.h"

class BulletManager;
/// <summary>
/// PlayerPartFactory�̃N���X���`����
/// </summary>
class TurretPartFactory : public ITurretPartFactory
{
public:
	/// <summary>
	///�@�^���b�g�̓y��𐶐�����
	/// </summary>
	/// <param name="parent">���̊Ǘ��҂̃|�C���^</param>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�^���b�g�̓y��̃A�h���X</returns>
	static std::unique_ptr<ITurretComponent> CreateTurretBase(
		BulletManager* bulletManager,
		ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�^���b�g�̐^�񒆂̑�C�𐶐�����
	/// </summary>
	/// <param name="parent">���̊Ǘ��҂̃|�C���^</param>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�^���b�g�̐^�񒆂̑�C�̃A�h���X</returns>
	static std::unique_ptr<ITurretComponent> CreateTurretCancer_Middle(
		BulletManager* bulletManager,
		ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�^���b�g�̍��̑�C�𐶐�����
	/// </summary>
	/// <param name="parent">���̊Ǘ��҂̃|�C���^</param>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�^���b�g�̍��̑�C�̃A�h���X</returns>
	static std::unique_ptr<ITurretComponent> CreateTurretCancer_Left(
		BulletManager* bulletManager,
		ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�^���b�g�̉E�̑�C�𐶐�����
	/// </summary>
	/// <param name="parent">���̊Ǘ��҂̃|�C���^</param>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�^���b�g�̉E�̑�C�̃A�h���X</returns>
	static std::unique_ptr<ITurretComponent> CreateTurretCancer_Right(
		BulletManager* bulletManager,
		ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�^���b�g�̓��𐶐�����
	/// </summary>
	/// <param name="parent">���̊Ǘ��҂̃|�C���^</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�^���b�g�̓��̃A�h���X</returns>
	static std::unique_ptr<ITurretComponent> CreateTurretHead(
		BulletManager* bulletManager,
		ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

};

