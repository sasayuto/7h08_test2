#pragma 
#include <combaseapi.h>
#include"IState.h"
// ITurretFactoryインタフェースを定義する
class RespawnManager;
class SupplyPointManager;
class EnemyManager;
class CoinManager;
class Player;
class BulletManager;
/// <summary>
/// IStatePlayerFactoryインターフェイスのクラスを定義する
/// </summary>
interface IStatePlayerFactory
{
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
	virtual std::unique_ptr<IState> CreateMotion(
		Player* parent,
		BulletManager* bulletManager,
		RespawnManager* respawnManager,
		SupplyPointManager* supplyPointManager,
		EnemyManager* enemyManager,
		CoinManager* coinManager
	) = 0;

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
	virtual std::unique_ptr<IState> CreateTurbMode(
		Player* parent,
		BulletManager* bulletManager,
		RespawnManager* respawnManager,
		SupplyPointManager* supplyPointManager,
		EnemyManager* enemyManager,
		CoinManager* coinManager
	) = 0;

	/// <summary>
	/// 回避の状態を生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="respawnManager">リスポーン地点の管理者もアドレス</param>
	/// <param name="supplyPointManager">アイテムの管理者のアドレス</param>
	/// <param name="coinManager">コインの管理者のアドレス</param>
	/// <returns>回避の状態のポインタ</returns>
	virtual std::unique_ptr<IState> CreateAvoidanceMotion(
		Player* parent,
		RespawnManager* respawnManager,
		SupplyPointManager* supplyPointManager,
		CoinManager* coinManager
	) = 0;

	/// <summary>
	/// 停止の状態を生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="respawnManager">球の管理者のアドレス</param>
	/// <param name="respawnManager">リスポーン地点の管理者もアドレス</param>
	/// <param name="supplyPointManager">アイテムの管理者のアドレス</param>
	/// <param name="enemyManager">敵の管理者のアドレス</param>
	/// <param name="coinManager">コインの管理者のアドレス</param>
	/// <returns>通常の状態のポインタ</returns>
	virtual std::unique_ptr<IState> CreateStopMotion(
		Player* parent,
		BulletManager* bulletManager,
		RespawnManager* respawnManager,
		SupplyPointManager* supplyPointManager,
		EnemyManager* enemyManager,
		CoinManager* coinManager
	) = 0;

	/// <summary>
	/// 死亡の状態を生成
	/// </summary>
	/// <param name="player">親のアドレス</param>
	/// <returns>死亡の状態のポインタ</returns>
	virtual std::unique_ptr<IState> CreateKillMotion(
		Player* player
	) = 0;
};

