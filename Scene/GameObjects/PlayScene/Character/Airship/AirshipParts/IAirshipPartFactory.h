#pragma once
#include <combaseapi.h>

#include"IAirshipComponent.h"

/// <summary>
/// IPlayerPartFactory�C���^�t�F�[�X���`����
/// </summary>
interface IAirshipPartFactory
{	
	/// <summary>
	///�@�v���y���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃A�h���X</returns>
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipBody(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipElevatorLeft(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipElevatorRight(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipRoom_01(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipRoom_02(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipPropellerSupportRight(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipPropellerSupportLeft(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipRudder(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipPropellerLeft(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipPropellerRight(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipPropellerMiddle(
		const IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;
};
