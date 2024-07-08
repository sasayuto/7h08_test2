#include "pch.h"

#include "WindmillPartFactory.h"

#include"WindmillFoundation.h"
#include"WindmillBlade_01.h"
#include"WindmillBlade_02.h"
#include"WindmillTower.h"
#include"WindmillRoom.h"
#include"WindmillStairs.h"

std::unique_ptr<IWindmillComponent> WindmillPartFactory::CreateWindmillFoundation(IWindmillComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<IWindmillComponent> airshipBody = std::make_unique<WindmillFoundation>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//プロペラののインスタンスを返す
	return move(airshipBody);
}

std::unique_ptr<IWindmillComponent> WindmillPartFactory::CreateWindmillTower(IWindmillComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<IWindmillComponent> airshipBody = std::make_unique<WindmillTower>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//プロペラののインスタンスを返す
	return move(airshipBody);
}

std::unique_ptr<IWindmillComponent> WindmillPartFactory::CreateWindmillRoom(IWindmillComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<IWindmillComponent> airshipBody = std::make_unique<WindmillRoom>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//プロペラののインスタンスを返す
	return move(airshipBody);
}

std::unique_ptr<IWindmillComponent> WindmillPartFactory::CreateWindmillBlade_01(IWindmillComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<IWindmillComponent> airshipBody = std::make_unique<WindmillBlade_01>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//プロペラののインスタンスを返す
	return move(airshipBody);
}
std::unique_ptr<IWindmillComponent> WindmillPartFactory::CreateWindmillBlade_02(IWindmillComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<IWindmillComponent> airshipBody = std::make_unique<WindmillBlade_02>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//プロペラののインスタンスを返す
	return move(airshipBody);
}

std::unique_ptr<IWindmillComponent> WindmillPartFactory::CreateWindmillStairs(IWindmillComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<IWindmillComponent> airshipBody = std::make_unique<WindmillStairs>(parent, position, angle);
	// 初期化する
	airshipBody->Initialize();
	//プロペラののインスタンスを返す
	return move(airshipBody);
}
