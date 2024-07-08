#pragma once
#include"FuelSupplyPoint.h"
#include"HpSupplyPoint.h"
struct IPlayerComponent;

//アイテムの管理者のクラスを定義する
class SupplyPointManager
{
public:
	int GetItemGetCount()const { return m_itemGetCount; }
	void SetItemGetCount(const int& itemGetCount) { m_itemGetCount = itemGetCount; }
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SupplyPointManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SupplyPointManager();

	//初期化する
	void Intialize(std::string failName = "");

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">1フレーム時間</param>
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
	/// プレイヤーと球の当たり判定
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	void CheckHitCharacter(Player* player);

private:
	//アイテムのポインタ
	std::vector<std::unique_ptr<Item>> m_supplyPointList;

	int m_itemGetCount;
};