#include "pch.h"

#include"AirshipPartFactory.h"
#include"AirshipBody.h"
#include"AirshipElevator_Left.h"
#include"AirshipElevatorRight.h"
#include"AirshipRoom_1.h"
#include"AirshipRoom_2.h"
#include"AirshipPropellerSupportLeft.h"
#include"AirshipPropellerSupportRight.h"
#include"AirshipPropellerRight.h"
#include"AirshipPropellerMiddle.h"
#include"AirshipPropellerLeft.h"
#include"AirshipRudder.h"

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipBody(
	IAirshipComponent* parent,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& angle
)
{
	//��s�D�̃{�f�B�[�̃C���X�^���X�𐶐�����
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipBody>(parent, position, angle);
	// ����������
	airshipBody->Initialize();
	//��s�D�̃{�f�B�[�̃C���X�^���X��Ԃ�
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipElevatorLeft(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//��s�D��ElevatorLeft�̃C���X�^���X�𐶐�����
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipElevatorLeft>(parent, position, angle);
	// ����������
	airshipBody->Initialize();
	//��s�D��ElevatorLeft�̃C���X�^���X��Ԃ�
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipElevatorRight(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//��s�D��ElevatorRight�̃C���X�^���X�𐶐�����
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipElevatorRight>(parent, position, angle);
	// ����������
	airshipBody->Initialize();
	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipRoom_01(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//��s�D�̕����Q�O�P�̃C���X�^���X�𐶐�����
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipRoom_01>(parent, position, angle);
	// ����������
	airshipBody->Initialize();
	//��s�D�̕����Q�O�P�̃C���X�^���X��Ԃ�
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipRoom_02(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//��s�D�̕����Q�O�Q�̃C���X�^���X�𐶐�����
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipRoom_02>(parent, position, angle);
	// ����������
	airshipBody->Initialize();
	//��s�D�̕����Q�O�Q�̃C���X�^���X��Ԃ�
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipPropellerSupportRight(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���T�|�[�g�E�̃C���X�^���X�𐶐�����
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipPropellerSupportRight>(parent, position, angle);
	// ����������
	airshipBody->Initialize();
	//�v���y���T�|�[�g�E�̃C���X�^���X��Ԃ�
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipPropellerSupportLeft(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���T�|�[�g���̃C���X�^���X�𐶐�����
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipPropellerSupportLeft>(parent, position, angle);
	// ����������
	airshipBody->Initialize();
	//�v���y���T�|�[�g���̃C���X�^���X��Ԃ�
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipRudder(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�ǂ̃C���X�^���X�𐶐�����
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipRudder>(parent, position, angle);
	// ����������
	airshipBody->Initialize();
	//�ǂ̃C���X�^���X��Ԃ�
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipPropellerLeft(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���̉E�̃C���X�^���X�𐶐�����
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipPropellerLeft>(parent, position, angle);
	// ����������
	airshipBody->Initialize();
	//�v���y���̉E�̃C���X�^���X��Ԃ�
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipPropellerRight(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���̍��̃C���X�^���X�𐶐�����
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipPropellerRight>(parent, position, angle);
	// ����������
	airshipBody->Initialize();
	//�v���y���̍��̃C���X�^���X��Ԃ�
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipPropellerMiddle(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���̐^�񒆂̃C���X�^���X�𐶐�����
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipPropellerMiddle>(parent, position, angle);
	// ����������
	airshipBody->Initialize();
	//�v���y���̐^�񒆂̃C���X�^���X��Ԃ�
	return move(airshipBody);
}
