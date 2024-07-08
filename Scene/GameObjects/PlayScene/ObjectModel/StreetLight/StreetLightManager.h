#pragma once
#include"StreetLight.h"

class Enemy; 
class Airship;
class BulletManager;
class SandstormEffect;

/// <summary>
/// オブジェクトの管理者のクラスを定義する
/// </summary>
class StreetLightManager
{
public:
	//オブジェクトの種類
	const enum ObjectParent
	{
		None = 0,
		HOUSE = 1
	};

	//キルカウント
	int GetStreetLightKillCount() { return m_streetLightKillCount; }
	void SetStreetLightKillCount(int streetLightKillCount) { m_streetLightKillCount = streetLightKillCount; }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="mapLoader">マップのアドレス</param>
	StreetLightManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StreetLightManager();

	/// <summary>
	/// 初期化する
	/// </summary>
	void Intialize(BulletManager* bulletManager);

	/// <summary>
	/// 更新する
	/// </summary>
	void Update(const float& elapsedTime);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

	/// <summary>
	/// シャドウマップ用の画像を作る
	/// </summary>
	virtual void RenderShadowTex(const bool flag);


	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();

	/// <summary>
	/// プレイヤーと球の当たり判定
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	void CheckHitCharacter(Player* player);

	/// <summary>
	/// プレイヤーと球の当たり判定
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	void CheckHitEnemy(Enemy* enemy);	
	
	/// <summary>
	/// 飛行船と球の当たり判定
	/// </summary>
	/// <param name="character">敵のアドレス</param>
	void CheckHitAirship(Airship* airship);

	/// <summary>
/// 飛行船と球の当たり判定
/// </summary>
/// <param name="character">敵のアドレス</param>
	void CheckHitSandstorm(SandstormEffect* sandstormEffect);



private:
	//オブジェクトのポインタ
	std::vector<std::unique_ptr<StreetLight>> m_objectsList;
	BulletManager* m_bulletManager;
	//キルカウント
	int m_streetLightKillCount;

};