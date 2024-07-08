#pragma once

#include "ImaseLib/NumberManager.h"


/// <summary>
/// ゲージのクラスを定義する
/// </summary>
class ScoreTex
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="m_player">プレイヤーのポインタ</param>
	ScoreTex();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ScoreTex();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const int& timer,
		const tito::ANCHOR& anchor
	);

	/// <summary>
	/// 更新する
	/// </summary>
	void Update(const int& timer);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

	/// <summary>
private:
	//ゲージとベースのポインタ
	std::vector<std::unique_ptr<tito::NumberManager>> m_ScoreTex;

	DirectX::SimpleMath::Vector2 m_position;
	DirectX::SimpleMath::Vector2 m_scale;
	float m_timer;
	tito::ANCHOR m_anchor;
};
