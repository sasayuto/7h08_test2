#pragma once
#include <combaseapi.h>
class EnemyManager;
class Player;
class Enemy;
class IState;

/// <summary>
/// IStateEnemyFactoryインターフェイスのクラスを定義する
/// </summary>
interface  IStateEnemyFactory
{
	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="parent">敵のアドレス</param>
	/// <param name="supplyPointManager">敵の管理者のアドレス</param>
	/// <param name="player">プレイヤーのアドレス</param>
	/// <returns>通常の状態のポインタ</returns>
	virtual std::unique_ptr<IState> CreateEnemyMotion(
		Enemy* parent,
		EnemyManager* supplyPointManager,
		Player* respawnManager
	) = 0;

	/// <summary>
	///  通常の状態１を生成
	/// </summary>
	/// <param name="parent">敵のアドレス</param>
	/// <param name="supplyPointManager">敵の管理者のアドレス</param>
	/// <param name="player">プレイヤーのアドレス</param>
	/// <returns>通常の状態１のポインタ</returns>
	virtual std::unique_ptr<IState> CreateEnemyMotion_01(
		Enemy* parent,
		EnemyManager* supplyPointManager,
		Player* player
	) = 0;

	/// <summary>
	/// 通常の状態２を生成
	/// </summary>
	/// <param name="parent">敵のアドレス</param>
	/// <param name="supplyPointManager">敵の管理者のアドレス</param>
	/// <param name="player">プレイヤーのアドレス</param>
	/// <returns>通常の状態２のポインタ</returns>
	virtual std::unique_ptr<IState> CreateEnemyMotion_02(
		Enemy* parent,
		EnemyManager* supplyPointManager,
		Player* respawnManager
	) = 0;

	/// <summary>
	/// 死亡の状態を生成
	/// </summary>
	/// <param name="parent">敵のアドレス</param>
	/// <returns>死亡の状態のポインタ</returns>
	virtual std::unique_ptr<IState> CreateEnemyKillMotion(
		Enemy* parent
	) = 0;
};

