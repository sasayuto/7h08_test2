#include "pch.h"

#include "CrabRobotPartFactory.h"

#include"CrabRobotHead.h"

std::unique_ptr<ICrabRobotComponent> CrabRobotPartFactory::CreateCrabRobotHead(ICrabRobotComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<ICrabRobotComponent> crabRobotHead = std::make_unique<CrabRobotHead>( parent, position, angle);
	// 初期化する
	crabRobotHead->Initialize();
	//プロペラののインスタンスを返す
	return move(crabRobotHead);
}
