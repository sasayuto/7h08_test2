#pragma once
#include"MoveObjects.h"

class Enemy;
class Player;
class Airship;
class BulletManager;
class SandstormEffect;
/// <summary>
/// オブジェクトの管理者のクラスを定義する
/// </summary>
class MoveObjectsManager
{
public:
	//キルカウント
	int GetBenchKillCount() { return m_benchKillCount; }
	void SetBenchKillCount(int benchKillCount) { m_benchKillCount = benchKillCount; }

	//子のパーツを生成
	void AddMoveObjects(std::unique_ptr<MoveObjects> moveObjects)  { m_MoveObjectsManager.push_back(std::move(moveObjects)); }

	//オブジェクトのポインタ
	std::vector<std::unique_ptr<MoveObjects>>& GetMoveObjectsManager() { return m_MoveObjectsManager; };

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="mapLoader">マップのアドレス</param>
	MoveObjectsManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~MoveObjectsManager();

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Intialize(BulletManager* bulletManager);

	/// <summary>
	/// 更新する
	/// </summary>
	virtual void Update(const float& elapsedTime);

	/// <summary>
	/// 描画する
	/// </summary>
	virtual void Render();

	/// <summary>
	/// シャドウマップ用の画像を作る
	/// </summary>
	virtual void RenderShadowTex(const bool flag);


	/// <summary>
	/// 後始末
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// プレイヤーと球の当たり判定
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	virtual void CheckHitCharacter(Player* player);

	/// <summary>
	/// プレイヤーと球の当たり判定
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	virtual void CheckHitEnemy(Enemy* enemy);
	
	/// <summary>
	/// 飛行船と球の当たり判定
	/// </summary>
	/// <param name="character">敵のアドレス</param>
	virtual void CheckHitAirship(Airship* airship);

	/// <summary>
	/// 飛行船と球の当たり判定
	/// </summary>
	/// <param name="character">敵のアドレス</param>
	virtual void CheckHitSandstorm(SandstormEffect* sandstormEffect);

private:
	//オブジェクトのポインタ
	std::vector<std::unique_ptr<MoveObjects>> m_breakObjectsManager;

	//オブジェクトのポインタ
	std::vector<std::unique_ptr<MoveObjects>> m_MoveObjectsManager;

	BulletManager* m_pBulletManager;

	//キルカウント
	int m_benchKillCount;
};