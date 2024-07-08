#include "pch.h"

#include "StreetLightPartFactory.h"

#include"StreetLightFoundation.h"
#include"StreetLightLight.h"
#include"StreetLightConnection.h"

std::unique_ptr<IStreetLightComponent> StreetLightPartFactory::CreateStreetLightConnection(IStreetLightComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<IStreetLightComponent> streetLightConnection = std::make_unique<StreetLightConnection>(parent, position, angle);
	// 初期化する
	streetLightConnection->Initialize();
	//プロペラののインスタンスを返す
	return move(streetLightConnection);
}

std::unique_ptr<IStreetLightComponent> StreetLightPartFactory::CreateStreetLightLight(IStreetLightComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<IStreetLightComponent> streetLightLight = std::make_unique<StreetLightLight>(parent, position, angle);
	// 初期化する
	streetLightLight->Initialize();
	//プロペラののインスタンスを返す
	return move(streetLightLight);
}

std::unique_ptr<IStreetLightComponent> StreetLightPartFactory::CreateStreetLightFoundation(IStreetLightComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<IStreetLightComponent> streetLightFoundation = std::make_unique<StreetLightFoundation>(parent, position, angle);
	// 初期化する
	streetLightFoundation->Initialize();
	//プロペラののインスタンスを返す
	return move(streetLightFoundation);
}
