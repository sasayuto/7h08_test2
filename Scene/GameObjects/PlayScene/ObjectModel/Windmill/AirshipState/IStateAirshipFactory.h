#pragma once
#include <combaseapi.h>
class Player;
class Airship;
class IStateAirship;

/// <summary>
/// IStateEnemyFactoryインターフェイスのクラスを定義する
/// </summary>
interface  IStateAirshipFactory
{
	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="coinManager">コインのアドレス</param>
	/// <returns>通常の状態のポインタ</returns>
	virtual std::unique_ptr<IStateAirship> CreateAirshipMotion(
		Airship* parent,
		Player* respawnManager
	) = 0;
	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="coinManager">コインのアドレス</param>
	/// <returns>通常の状態のポインタ</returns>
	virtual std::unique_ptr<IStateAirship> CreateAirshipMotion_01(
		Airship* parent,
		Player* respawnManager
	) = 0;

	///// <summary>
	///// 死亡の状態を生成
	///// </summary>
	///// <param name="parent">敵のアドレス</param>
	///// <returns>死亡の状態のポインタ</returns>
	//virtual std::unique_ptr<IState> CreateEnemyKillMotion(
	//	Enemy* parent
	//) = 0;
};

