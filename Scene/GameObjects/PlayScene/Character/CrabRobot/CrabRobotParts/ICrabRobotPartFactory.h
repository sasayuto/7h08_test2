#pragma once
#include <combaseapi.h>

#include"ICrabRobotComponent.h"

/// <summary>
/// IPlayerPartFactoryインタフェースを定義する
/// </summary>
interface ICrabRobotPartFactory
{	
	/// <summary>
	///　タレットの土台を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのアドレス</returns>
	virtual std::unique_ptr<ICrabRobotComponent> CreateCrabRobotHead(
		const ICrabRobotComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;
};
