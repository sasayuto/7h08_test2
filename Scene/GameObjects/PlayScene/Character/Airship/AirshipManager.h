#pragma once
#include"Airship.h"

class BulletManager;
class ObjectsManager;
class Player;
class Enemy;

//敵の管理者のクラスを定義する
class AirshipManager
{
public:
	//キル数のゲッター、セッター
	unsigned int GetKillCount() const { return m_killCount; }
	void SetKillCount(const unsigned int& killCount) { m_killCount = killCount; }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	AirshipManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~AirshipManager();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="bulletManager">球のアドレス</param>
	/// <param name="player">プレイヤーのアドレス</param>
	void Intialize(
		BulletManager* bulletManager, 
		Player* player, 
		ObjectsManager* objectsManager
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
	void CheckHitPlayer(Player* player);

	/// <summary>
	/// プレイヤーと当たり判定
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	void CheckHitEnemy(Enemy* enemy);

	/// <summary>
	/// 自動生成
	/// </summary>
	void AutoGenerated();

private:
	//敵の配列のポインタ
	std::vector<std::unique_ptr<Airship>> m_airshipList;

	//キル数
	unsigned int m_killCount;

	//生成時間
	float m_generationTime;

	//球のポインタ
	BulletManager* m_pBulletManager;

	//プレイヤーのポインタ
	Player* m_pPlayer;
	ObjectsManager* m_pObjectsManager;

};