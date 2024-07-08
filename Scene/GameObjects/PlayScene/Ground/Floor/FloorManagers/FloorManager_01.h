#pragma once
#include"../Floor.h"

class Enemy; 
class Airship;

/// <summary>
/// 床の管理者のクラスを定義する
/// </summary>
class FloorManager_01
{
public:
	//床の種類
	const enum ObjectParent
	{
		None = 0,
		HOUSE = 1
	};

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="mapLoader">マップのアドレス</param>
	FloorManager_01();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~FloorManager_01();

	/// <summary>
	/// 初期化する
	/// </summary>
	void Intialize();

	/// <summary>
	/// 更新する
	/// </summary>
	void Update();

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

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

private:
	//床の種類
	ObjectParent m_objectParent;

	//床のポインタ
	std::vector<std::unique_ptr<Floor>> m_floorsList;
};