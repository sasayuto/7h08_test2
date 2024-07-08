#pragma once
#include"Objects.h"

class Enemy; 
class Airship;

/// <summary>
/// オブジェクトの管理者のクラスを定義する
/// </summary>
class ObjectsManager
{
public:
	//オブジェクトの種類
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
	ObjectsManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ObjectsManager();

	/// <summary>
	/// 初期化する
	/// </summary>
	void Intialize();  
		void CollJson(const Json::Value& ary,Objects* obj); 

	/// <summary>
	/// 更新する
	/// </summary>
	void Update();

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

	/// <summary>
	/// 描画する
	/// </summary>
	void RenderShadowTex();

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



private:
	//オブジェクトの種類
	ObjectParent m_objectParent;

	//オブジェクトのポインタ
	std::vector<std::unique_ptr<Objects>> m_objectsList;
};