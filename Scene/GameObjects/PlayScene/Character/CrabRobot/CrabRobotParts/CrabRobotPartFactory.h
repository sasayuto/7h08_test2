#pragma once
#include "ICrabRobotComponent.h"
#include "ICrabRobotPartFactory.h"

/// <summary>
/// PlayerPartFactoryのクラスを定義する
/// </summary>
class CrabRobotPartFactory : public ICrabRobotPartFactory
{
public:
	/// <summary>
	///　タレットの土台を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのアドレス</returns>
	static std::unique_ptr<ICrabRobotComponent> CreateCrabRobotHead(
		ICrabRobotComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
};

