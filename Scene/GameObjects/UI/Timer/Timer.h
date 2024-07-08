#pragma once

#include "ImaseLib/NumberManager.h"


/// <summary>
/// ゲージのクラスを定義する
/// </summary>
class TimerTex
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="m_player">プレイヤーのポインタ</param>
	TimerTex();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TimerTex();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const float& timer,
		const tito::ANCHOR& anchor
	);

	/// <summary>
	/// 更新する
	/// </summary>
	void Update(const float& timer);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

	/// <summary>
	/// 描画する
	/// </summary>
	void Finalize();

	/// <summary>
private:
	//ゲージとベースのポインタ
	std::vector<std::unique_ptr<tito::NumberManager>> m_timerTex;
};
