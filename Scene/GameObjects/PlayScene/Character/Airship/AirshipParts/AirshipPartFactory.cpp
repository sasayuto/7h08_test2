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
	//飛行船のボディーのインスタンスを生成する
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipBody>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//飛行船のボディーのインスタンスを返す
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipElevatorLeft(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//飛行船のElevatorLeftのインスタンスを生成する
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipElevatorLeft>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//飛行船のElevatorLeftのインスタンスを返す
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipElevatorRight(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//飛行船のElevatorRightのインスタンスを生成する
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipElevatorRight>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//プロペラののインスタンスを返す
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipRoom_01(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//飛行船の部屋＿０１のインスタンスを生成する
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipRoom_01>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//飛行船の部屋＿０１のインスタンスを返す
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipRoom_02(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//飛行船の部屋＿０２のインスタンスを生成する
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipRoom_02>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//飛行船の部屋＿０２のインスタンスを返す
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipPropellerSupportRight(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラサポート右のインスタンスを生成する
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipPropellerSupportRight>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//プロペラサポート右のインスタンスを返す
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipPropellerSupportLeft(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラサポート左のインスタンスを生成する
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipPropellerSupportLeft>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//プロペラサポート左のインスタンスを返す
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipRudder(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//舵のインスタンスを生成する
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipRudder>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//舵のインスタンスを返す
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipPropellerLeft(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラの右のインスタンスを生成する
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipPropellerLeft>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//プロペラの右のインスタンスを返す
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipPropellerRight(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラの左のインスタンスを生成する
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipPropellerRight>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//プロペラの左のインスタンスを返す
	return move(airshipBody);
}

std::unique_ptr<IAirshipComponent> AirshipPartFactory::CreateAirshipPropellerMiddle(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラの真ん中のインスタンスを生成する
	std::unique_ptr<IAirshipComponent> airshipBody = std::make_unique<AirshipPropellerMiddle>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//プロペラの真ん中のインスタンスを返す
	return move(airshipBody);
}
