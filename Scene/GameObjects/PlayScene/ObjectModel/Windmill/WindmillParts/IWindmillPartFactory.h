#pragma once
#include <combaseapi.h>

#include"IWindmillComponent.h"

/// <summary>
/// IPlayerPartFactory�C���^�t�F�[�X���`����
/// </summary>
interface IWindmillPartFactory
{	
	/// <summary>
	///�@�v���y���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃A�h���X</returns>
	virtual std::unique_ptr<IWindmillComponent> CreateWindmillBlade_01(
		const IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@�v���y���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃A�h���X</returns>
	virtual std::unique_ptr<IWindmillComponent> CreateWindmillBlade_02(
		const IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@�v���y���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃A�h���X</returns>
	virtual std::unique_ptr<IWindmillComponent> CreateWindmillFoundation(
		const IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@�v���y���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃A�h���X</returns>
	virtual std::unique_ptr<IWindmillComponent> CreateWindmillRoom(
		const IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@�v���y���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃A�h���X</returns>
	virtual std::unique_ptr<IWindmillComponent> CreateWindmillTower(
		const IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@�v���y���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃A�h���X</returns>
	virtual std::unique_ptr<IWindmillComponent> CreateWindmillStairs(
		const IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;
};
