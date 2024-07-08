#include "pch.h"

#include"PlayerPartFactory.h"

#include"Scene/GameObjects/PlayScene/Character/Wing.h"
#include"Scene/GameObjects/PlayScene/Character/Propeller.h"
#include"Scene/GameObjects/PlayScene/Character/Tail.h"
#include"Scene/GameObjects/PlayScene/Character/HorizontalStabilizer.h"
#include"Scene/GameObjects/PlayScene/Character/Body.h"
#include"Scene/GameObjects/PlayScene/Character/LeftTire.h"
#include"Scene/GameObjects/PlayScene/Character/RightTire.h"
#include"Scene/GameObjects/PlayScene/Character/WheelSupport.h"


std::unique_ptr<IPlayerComponent> PlayerPartFactory::CreatePlayerPro(
	IPlayerComponent* parent,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& angle
)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<IPlayerComponent> propeller = std::make_unique<Propeller>(parent, position, angle);

	//プロペラののインスタンスを返す
	return move(propeller);
}

std::unique_ptr<IPlayerComponent> PlayerPartFactory::CreatePlayerWing(
	IPlayerComponent* parent,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& angle
)
{
	//羽のインスタンスを生成する
	std::unique_ptr<IPlayerComponent> wing = std::make_unique<Wing>(parent, position, angle);

	//羽のインスタンスを返す
	return move(wing);
}

std::unique_ptr<IPlayerComponent> PlayerPartFactory::CreatePlayerBody(
	IPlayerComponent* parent,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& angle
)
{
	//羽のインスタンスを生成する
	std::unique_ptr<IPlayerComponent> body = std::make_unique<Body>(parent, position, angle);

	//羽のインスタンスを返す
	return move(body);
}

std::unique_ptr<IPlayerComponent> PlayerPartFactory::CreatePlayerTail(IPlayerComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//羽のインスタンスを生成する
	std::unique_ptr<IPlayerComponent> tail = std::make_unique<Tail>(parent, position, angle);

	//羽のインスタンスを返す
	return move(tail);
}

std::unique_ptr<IPlayerComponent> PlayerPartFactory::CreatePlayerHorizontalStabilizer(IPlayerComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//羽のインスタンスを生成する
	std::unique_ptr<IPlayerComponent> horizontalStabilizer = std::make_unique<HorizontalStabilizer>(parent, position, angle);

	//羽のインスタンスを返す
	return move(horizontalStabilizer);
}

std::unique_ptr<IPlayerComponent> PlayerPartFactory::CreatePlayerLeftTire(IPlayerComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//羽のインスタンスを生成する
	std::unique_ptr<IPlayerComponent> leftTire = std::make_unique<LeftTire>(parent, position, angle);

	//羽のインスタンスを返す
	return move(leftTire);
}

std::unique_ptr<IPlayerComponent> PlayerPartFactory::CreatePlayerRightTire(IPlayerComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//羽のインスタンスを生成する
	std::unique_ptr<IPlayerComponent> rightTire = std::make_unique<RightTire>(parent, position, angle);

	//羽のインスタンスを返す
	return move(rightTire);
}



std::unique_ptr<IPlayerComponent> PlayerPartFactory::CreatePlayerWheelSupport(
	IPlayerComponent* parent, 
	const DirectX::SimpleMath::Vector3& position, 
	const DirectX::SimpleMath::Quaternion& angle
)
{
	//羽のインスタンスを生成する
	std::unique_ptr<IPlayerComponent> wheelSupport = std::make_unique<WheelSupport>(parent, position, angle);

	//羽のインスタンスを返す
	return move(wheelSupport);
}
