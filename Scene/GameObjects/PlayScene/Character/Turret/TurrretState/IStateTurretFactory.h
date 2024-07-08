#pragma once
#include <combaseapi.h>
class ITurretState;
class Turret;
class TurretManager;

/// <summary>
/// IStateTurretFactoryインターフェイスのクラスを定義する
/// </summary>
interface  IStateTurretFactory
{
	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="parent">タレットのアドレス</param>
	/// <param name="coinManager">タレットの管理者のアドレス</param>
	/// <returns>通常の状態のポインタ</returns>
	virtual std::unique_ptr<ITurretState> CreateTurretMotion(
		const Turret* parent,
		const TurretManager* TurretManager
	) = 0;

	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <returns>死亡状態のポインタ</returns>
	virtual std::unique_ptr<ITurretState> CreateTurretKillMotion(
		const Turret* parent
	) = 0;

};

