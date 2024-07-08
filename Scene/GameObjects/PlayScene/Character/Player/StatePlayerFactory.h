#pragma once
#include "IState.h"
#include "IStatePlayerFactory.h"

class RespawnManager;
class SupplyPointManager;
class EnemyManager;
class CoinManager;
class Player;

/// <summary>
/// StatePlayerFactoryのクラスを定義する
/// </summary>
class StatePlayerFactory : public IStatePlayerFactory
{
public:
	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="respawnManager">球の管理者のアドレス</param>
	/// <param name="respawnManager">リスポーン地点の管理者のアドレス</param>
	/// <param name="supplyPointManager">アイテムの管理者のアドレス</param>
	/// <param name="enemyManager">敵の管理者のアドレス</param>
	/// <param name="coinManager">コインの管理者のアドレス</param>
	/// <returns>通常の状態のポインタ</returns>
	static std::unique_ptr<IState> CreateMotion(
		Player* player,
		BulletManager* bulletManager,
		RespawnManager* respawnManager,
		SupplyPointManager* supplyPointManager,
		EnemyManager* enemyManager,
		CoinManager* coinManager
	);

	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="respawnManager">球の管理者のアドレス</param>
	/// <param name="respawnManager">リスポーン地点の管理者もアドレス</param>
	/// <param name="supplyPointManager">アイテムの管理者のアドレス</param>
	/// <param name="enemyManager">敵の管理者のアドレス</param>
	/// <param name="coinManager">コインの管理者のアドレス</param>
	/// <returns>通常の状態のポインタ</returns>
	static std::unique_ptr<IState> CreateTurbMode(
		Player* parent,
		BulletManager* bulletManager,
		RespawnManager* respawnManager,
		SupplyPointManager* supplyPointManager,
		EnemyManager* enemyManager,
		CoinManager* coinManager
	);

	/// <summary>
	/// 回避の状態を生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="respawnManager">リスポーン地点の管理者もアドレス</param>
	/// <param name="supplyPointManager">アイテムの管理者のアドレス</param>
	/// <param name="coinManager">コインの管理者のアドレス</param>
	/// <returns>回避の状態のポインタ</returns>
	static std::unique_ptr<IState> CreateAvoidanceMotion(
		Player* parent,
		RespawnManager* respawnManager,
		SupplyPointManager* supplyPointManager,
		CoinManager* coinManager
	);

	/// <summary>
	/// ストップの状態を生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="respawnManager">球の管理者のアドレス</param>
	/// <param name="respawnManager">リスポーン地点の管理者のアドレス</param>
	/// <param name="supplyPointManager">アイテムの管理者のアドレス</param>
	/// <param name="enemyManager">敵の管理者のアドレス</param>
	/// <param name="coinManager">コインの管理者のアドレス</param>
	/// <returns>スットプの状態のポインタ</returns>
	static std::unique_ptr<IState> CreateStopMotion(
		Player* player,
		BulletManager* bulletManager,
		RespawnManager* respawnManager,
		SupplyPointManager* supplyPointManager,
		EnemyManager* enemyManager,
		CoinManager* coinManager
	);

	///// <summary>
	///// 回避の状態を生成
	///// </summary>
	///// <param name="parent">親のアドレス</param>
	///// <param name="respawnManager">リスポーン地点のアドレス</param>
	///// <param name="supplyPointManager">アイテムのアドレス</param>
	///// <param name="enemyManager">敵のアドレス</param>
	///// <param name="coinManager">コインのアドレス</param>
	///// <returns>回避の状態のポインタ</returns>
	//static std::unique_ptr<IState> CreateStopMotion(
	//	Player* player,
	//	RespawnManager* respawnManager,
	//	SupplyPointManager* supplyPointManager,
	//	EnemyManager* enemyManager,
	//	CoinManager* coinManager
	//);

	/// <summary>
	/// 死亡の状態を生成
	/// </summary>
	/// <param name="player">親のアドレス</param>
	/// <returns>死亡の状態のポインタ</returns>
	static std::unique_ptr<IState> CreateKillMotion(
		Player* parent);
};

