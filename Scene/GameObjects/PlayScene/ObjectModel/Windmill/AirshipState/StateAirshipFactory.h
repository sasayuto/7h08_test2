#pragma once
#include "IStateAirshipFactory.h"

class Player;
class Airship;
class IStateAirship;

/// <summary>
/// StateEnemyFactoryのクラスを定義する
/// </summary>
class StateAirshipFactory : public IStateAirshipFactory
{
public:
	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="parent">親のアイテムのアドレス</param>
	/// <param name="coinManager">コインのアドレス</param>
	/// <returns>通常の状態のポインタ</returns>
	static std::unique_ptr<IStateAirship> CreateAirshipMotion(
		Airship* enemy,
		Player* player
	);

	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="parent">親のアイテムのアドレス</param>
	/// <param name="coinManager">コインのアドレス</param>
	/// <returns>通常の状態のポインタ</returns>
	static std::unique_ptr<IStateAirship> CreateAirshipMotion_01(
		Airship* enemy,
		Player* player
	);

	///// <summary>
	///// 通常の状態を生成
	///// </summary>
	///// <param name="parent">親のアイテムのアドレス</param>
	///// <param name="respawnManager">リスポーン地点のアドレス</param>
	///// <param name="supplyPointManager">アイテムのアドレス</param>
	///// <param name="enemyManager">敵のアドレス</param>
	///// <param name="coinManager">コインのアドレス</param>
	///// <returns>通常の状態のポインタ</returns>
	//static std::unique_ptr<IState> CreateEnemyMotion_01(
	//	Enemy* enemy,
	//	EnemyManager* enemyManager,
	//	Player* player
	//);

	///// <summary>
	///// 死亡の状態を生成
	///// </summary>
	///// <param name="player">プレイヤーのアドレス</param>
	///// <returns>死亡の状態のポインタ</returns>
	//static std::unique_ptr<IState> CreateEnemyKillMotion(
	//	Enemy* enemy);
};

