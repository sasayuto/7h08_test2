#pragma once
#include"Item.h"

/// <summary>
/// 燃料補給のクラスを定義する
/// </summary>
class FuelSupplyPoint : public Item
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	FuelSupplyPoint();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~FuelSupplyPoint()override;

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
};
