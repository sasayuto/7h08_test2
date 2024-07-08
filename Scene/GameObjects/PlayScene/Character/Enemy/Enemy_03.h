#pragma once
#include"Enemy.h"


/// <summary>
/// 敵3のクラスを定義する
/// </summary>
class Enemy_03 :public Enemy
{
public:
	//敵のHP
	static const unsigned ENEMY_MAX_HP = 10;

	//敵の燃料
	static const unsigned ENEMY_MAX_FUEL = 1000000;

	//敵のパワー
	static const int ENEMY_OFFENSIVE_POWER = 1;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy_03();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy_03();

	/// <summary>
	/// 初期化する
	/// </summary>
	/// <param name="bulletManager">球の管理者アドレス</param>
	/// <param name="enemyManager">敵の管理者のアドレス</param>
	/// <param name="objectsManager">オブジェクトの管理者のアドレス</param>
	/// <param name="treeManager">木の管理者のアドレス</param>
	/// <param name="player">プレイヤーのアドレス</param>
	/// <param name="airshipManager">飛行船の管理者のアドレス</param>
	/// <param name="windmillManager">風車の管理者のアドレス</param>
	/// <param name="floor">床のアドレス</param>
	/// <param name="sandstormManager">砂嵐の管理者のアドレス</param>
	/// <param name="floorManager_01">床の管理者のアドレス</param>
	void Initialize(
		BulletManager* bulletManager,
		EnemyManager* enemyManager,
		ObjectsManager* objectsManager,
		Player* player,
		AirshipManager* airshipManager,
		WindmillManager* windmillManager,
		Floor* floor,
		SandstormManager* sandstormManager,
		FloorManager_01* floorManager_01,
		BigBrickWallManager* bigBrickWallManager
	)override;

	/// <summary>
/// 動きをリセット
/// </summary>
	void Reset()override;


};
