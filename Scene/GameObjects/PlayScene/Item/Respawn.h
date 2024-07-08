#pragma once
#include"Item.h"

/// <summary>
/// リスポーン地点のクラスを定義する
/// </summary>
class Respawn : public Item
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Respawn();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Respawn()override;

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">1フレーム時間</param>
	void Update(const float& elapsedTime)override;

	/// <summary>
	/// 描画する
	/// </summary>
	void Render()override;

	/// <summary>
	/// 回復をさせる
	/// </summary>
	/// <param name="player">プレイヤーのアドレス/param>
	void Recovery(Player* player) override;
};
