#pragma once
#include"Enemy.h"


/// <summary>
/// 敵カスタムのクラスを定義する
/// </summary>
class EnemyCustom_00 :public Enemy
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="Hp">敵のHP</param>
	/// <param name="Fuel">敵の燃料</param>
	/// <param name="offensivePower">敵のパワー</param>
	EnemyCustom_00(const int& Hp, const int& Fuel, const int& offensivePower);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyCustom_00();

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

private:
	int m_maxHp;

	int m_maxFuel;

	int m_OffensivePower;
};
