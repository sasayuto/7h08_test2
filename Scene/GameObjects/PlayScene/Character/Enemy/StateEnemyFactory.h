#pragma once
#include "IStateEnemyFactory.h"

class EnemyManager;
class Player;
class Enemy;
class IState;

/// <summary>
/// StateEnemyFactoryのクラスを定義する
/// </summary>
class StateEnemyFactory : public IStateEnemyFactory
{
public:
	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="parent">敵のアドレス</param>
	/// <param name="supplyPointManager">敵の管理者のアドレス</param>
	/// <param name="player">プレイヤーのアドレス</param>
	/// <returns>通常の状態のポインタ</returns>
	static std::unique_ptr<IState> CreateEnemyMotion(
		Enemy* enemy,
		EnemyManager* enemyManager,
		Player* player
	);

	/// <summary>
	/// 通常の状態１を生成
	/// </summary>
	/// <param name="parent">敵のアドレス</param>
	/// <param name="supplyPointManager">敵の管理者のアドレス</param>
	/// <param name="player">プレイヤーのアドレス</param>
	/// <returns>通常の状態１のポインタ</returns>
	static std::unique_ptr<IState> CreateEnemyMotion_01(
		Enemy* enemy,
		EnemyManager* enemyManager,
		Player* player
	);

	/// <summary>
	/// 通常の状態２を生成
	/// </summary>
	/// <param name="parent">敵のアドレス</param>
	/// <param name="supplyPointManager">敵の管理者のアドレス</param>
	/// <param name="player">プレイヤーのアドレス</param>
	/// <returns>通常の状態２のポインタ</returns>
	static std::unique_ptr<IState> CreateEnemyMotion_02(
		Enemy* enemy,
		EnemyManager* enemyManager,
		Player* player
	);

	/// <summary>
	/// 死亡の状態を生成
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	/// <returns>死亡の状態のポインタ</returns>
	static std::unique_ptr<IState> CreateEnemyKillMotion(
		Enemy* enemy);
};

