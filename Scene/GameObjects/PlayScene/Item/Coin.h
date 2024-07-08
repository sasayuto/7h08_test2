#pragma once
#include"Item.h"
#include"Scene/GameObjects/PlayScene/Effect/LightEffect.h"

/// <summary>
/// コインのクラスを定義する
/// </summary>
class Coin : public Item
{
private:
	//光のエフェクトのポインタ
	std::unique_ptr<LightEffect> m_lightEffect;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Coin();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Coin()override;

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
	/// 描画する
	/// </summary>
	void Render()override;

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize()override;

};
