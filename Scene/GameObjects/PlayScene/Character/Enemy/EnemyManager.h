#pragma once
#include"Enemy.h"

class BulletManager;
class Player;
class ObjectsManager;
class AirshipManager;
class WindmillManager;
class Floor;
class SandstormManager;
class FloorManager_01;
class BigBrickWallManager;

/// <summary>
/// 敵の管理者のクラスを定義する
/// </summary>
class EnemyManager
{
public:
	//キル数のゲッター、セッター
	unsigned int GetKillCount() const { return m_killCount; }
	void SetKillCount(const unsigned int& killCount) { m_killCount = killCount; }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyManager();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="bulletManager">球の管理者アドレス</param>
	/// <param name="objectsManager">オブジェクトの管理者のアドレス</param>
	/// <param name="player">プレイヤーのアドレス</param>
	/// <param name="airshipManager">飛行船の管理者のアドレス</param>
	/// <param name="windmillManager">風車の管理者のアドレス</param>
	/// <param name="floor">床のアドレス</param>
	/// <param name="sandstormManager">砂嵐の管理者のアドレス</param>
	/// <param name="floorManager_01">床の管理者のアドレス</param>
	void Intialize(
		BulletManager* bulletManager,
		Player* player,
		ObjectsManager* objectsManager = nullptr,
		AirshipManager* airhhipManager = nullptr,
		WindmillManager* windmillManager = nullptr,
		Floor* floor = nullptr,
		SandstormManager* sandstormManager = nullptr,
		FloorManager_01* floorManager_01 = nullptr,
		BigBrickWallManager* bigBrickWallManager = nullptr
	);

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">フレーム時間</param>
	void Update(const float& elapsedTime);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

		/// <summary>
	/// シャドウマップ用の画像を作る
	/// </summary>
	void RenderShadowTex();

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();

	/// <summary>
	/// プレイヤーと当たり判定
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	void CheckHitCharacter(Player* player);

	/// <summary>
	/// 自動生成
	/// </summary>
	void AutoGenerated();

private:
	//敵の配列のポインタ
	std::vector<std::unique_ptr<Enemy>> m_enemyList;

	//キル数
	unsigned int m_killCount;

	//生成時間
	float m_generationTime;

	//球のポインタ
	BulletManager* m_pBulletManager;

	//プレイヤーのポインタ
	Player* m_pPlayer;

	//オブジェクトの管理者のポインタ
	ObjectsManager* m_pObjectsManager;

	//飛行船の管理者のポインタ
	AirshipManager* m_pAirshipManager;

	//風車の管理者のポインタ
	WindmillManager* m_pWindmillManager;

	//床のポインタ
	Floor* m_pFloor;

	//砂嵐の管理者のポインタ
	SandstormManager* m_pSandstormManager;


};