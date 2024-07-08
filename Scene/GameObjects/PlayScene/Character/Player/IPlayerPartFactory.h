#pragma once
#include <combaseapi.h>
#ifndef ITURRET_FACTORY_DEFINED
#define ITURRET_FACTORY_DEFINED
#include"IPlayerComponent.h"

/// <summary>
/// IPlayerPartFactory�C���^�t�F�[�X���`����
/// </summary>
interface  IPlayerPartFactory
{	
	/// <summary>
	///�@�v���y���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃A�h���X</returns>
	virtual std::unique_ptr<IPlayerComponent> CreatePlayerPro(
		const IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@�H�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�H�̃|�C���^</returns>
	virtual std::unique_ptr<IPlayerComponent> CreatePlayerWing(
		const IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@�{�f�B�[�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�{�f�B�[�̃|�C���^</returns>
	virtual std::unique_ptr<IPlayerComponent> CreatePlayerBody(
		const IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@�K���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�K���̃|�C���^</returns>
	virtual std::unique_ptr<IPlayerComponent> CreatePlayerTail(
		const IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@���������𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�����K���̃|�C���^</returns>
	virtual std::unique_ptr<IPlayerComponent> CreatePlayerHorizontalStabilizer(
		const IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@�E�^�C���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�^�C���̃|�C���^</returns>
	virtual std::unique_ptr<IPlayerComponent> CreatePlayerLeftTire(
		const IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@���^�C���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�^�C���̃|�C���^</returns>
	virtual std::unique_ptr<IPlayerComponent> CreatePlayerRightTire(
		const IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@�z�C�[���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�z�C�[���̃|�C���^</returns>
	virtual std::unique_ptr<IPlayerComponent> CreatePlayerWheelSupport(
		const IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;
};

#endif	// ITURRET_FACTORY_DEFINED