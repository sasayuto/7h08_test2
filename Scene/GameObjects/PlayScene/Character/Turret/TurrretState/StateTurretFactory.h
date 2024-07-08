#pragma once
#include "IStateTurretFactory.h"

class ITurretState;
class Turret;
class TurretManager;

/// <summary>
/// StateTurretFactoryのクラスを定義する
/// </summary>
class StateTurretFactory : public IStateTurretFactory
{
public:
	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="parent">タレットのアドレス</param>
	/// <param name="coinManager">タレットの管理者のアドレス</param>
	/// <returns>通常の状態のポインタ</returns>
	static std::unique_ptr<ITurretState> CreateTurretMotion(
		Turret* parent,
		TurretManager* TurretManager
	);

	/// <summary>
	/// 死亡状態を生成
	/// </summary>
	/// <param name="parent">タレットのアドレス</param>
	/// <returns>死亡状態のポインタ</returns>
	static std::unique_ptr<ITurretState> CreateTurretKillMotion(
		Turret* parent
	);
};

