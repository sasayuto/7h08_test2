#pragma once

#include "ImaseLib/GaugeManager.h"

class Player;

/// <summary>
/// ゲージのクラスを定義する
/// </summary>
class Gaueg
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="m_player">プレイヤーのポインタ</param>
	Gaueg(Player* m_player);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Gaueg();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();


	/// <summary>
	/// 更新する
	/// </summary>
	void Update();

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

	/// <summary>
	/// ゲージを作る
	/// </summary>
	/// <param name="path">ゲージの画像</param>
	/// <param name="basePath">背景の画像</param>
	/// <param name="position">描画位置</param>
	/// <param name="scale">大きさ</param>
	/// <param name="anchor">描画開始位置</param>
	void Add(
		const wchar_t* path,
		const wchar_t* basePath,
		const wchar_t* framePath,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const tito::ANCHOR& anchor,
		const tito::POSITION_ANCHOR& posotionAnchor
	);

private:
	//ゲージとベースのポインタ
	std::vector<std::unique_ptr<tito::GaugeManager>> m_gaueg, m_baes, m_frame;

	//プレイヤーのポインタ
	Player* m_player;
};
