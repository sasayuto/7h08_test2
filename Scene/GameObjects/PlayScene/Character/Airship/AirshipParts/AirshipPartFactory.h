#pragma once
#include "IAirshipComponent.h"
#include "IAirshipPartFactory.h"

/// <summary>
/// PlayerPartFactory�̃N���X���`����
/// </summary>
class AirshipPartFactory : public IAirshipPartFactory
{
public:
	/// <summary>
	///�@��s�D�̃{�f�B�[�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>��s�D�̃{�f�B�[�̃|�C���^</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipBody(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);	
	
	/// <summary>
	///�@��s�D��ElevatorLeft�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>��s�D��ElevatorLeft�̃A�h���X</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipElevatorLeft(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
	/// <summary>
	///�@��s�D��ElevatorRight�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>��s�D��ElevatorRight�̃A�h���X</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipElevatorRight(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@��s�D�̕����Q�O�P�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>��s�D�̕����Q�O�P�̃A�h���X</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipRoom_01(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@��s�D�̕����Q�O�Q�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>��s�D�̕����Q�O�Q�̃A�h���X</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipRoom_02(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�v���y���T�|�[�g�E�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���T�|�[�g�E�̃A�h���X</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipPropellerSupportRight(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�v���y���T�|�[�g���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���T�|�[�g���̃A�h���X</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipPropellerSupportLeft(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�ǂ𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�ǂ̃A�h���X</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipRudder(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
		/// <summary>
	///�@�v���y���̉E�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̉E�̃A�h���X</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipPropellerLeft(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�v���y���̍��𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̍��̃A�h���X</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipPropellerRight(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�v���y���̐^�񒆂𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̐^�񒆂̃A�h���X</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipPropellerMiddle(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

};

