#pragma once
#include "IPlayerComponent.h"
#include "IPlayerPartFactory.h"

/// <summary>
/// PlayerPartFactory�̃N���X���`����
/// </summary>
class PlayerPartFactory : public IPlayerPartFactory
{
public:
	/// <summary>
	///�@�v���y���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃|�C���^</returns>
	static std::unique_ptr<IPlayerComponent> CreatePlayerPro(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�H�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�H�̃|�C���^</returns>
	static std::unique_ptr<IPlayerComponent> CreatePlayerWing(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�{�f�B�[�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃|�C���^</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�{�f�B�[�̃|�C���^</returns>
	static std::unique_ptr<IPlayerComponent> CreatePlayerBody(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�K���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�K���̃|�C���^</returns>
	static std::unique_ptr<IPlayerComponent> CreatePlayerTail(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@���������𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�����K���̃|�C���^</returns>
	static std::unique_ptr<IPlayerComponent> CreatePlayerHorizontalStabilizer(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�^�C���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�^�C���|�C���^</returns>
	static std::unique_ptr<IPlayerComponent> CreatePlayerLeftTire(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�^�C���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�^�C���|�C���^</returns>
	static std::unique_ptr<IPlayerComponent> CreatePlayerRightTire(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�z�C�[���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�z�C�[���̃|�C���^</returns>
	static std::unique_ptr<IPlayerComponent> CreatePlayerWheelSupport(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

};

