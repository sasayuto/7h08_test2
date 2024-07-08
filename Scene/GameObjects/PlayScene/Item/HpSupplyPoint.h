#pragma once
#include"Item.h"

/// <summary>
/// HP補給のクラスを定義する
/// </summary>
class HpSupplyPoint : public Item
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	HpSupplyPoint();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~HpSupplyPoint()override;

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime"></param>
	void Update(const float& elapsedTime)override;

	/// <summary>
	/// 回復をさせる
	/// </summary>
	/// <param name="player">プレイヤーのポインタ</param>
	void Recovery(Player* player) override;
private:
	static const int REPLENISHMENT_HP;
};
