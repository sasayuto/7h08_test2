#pragma once

#include "ImaseLib/MoveUserInterface.h"

class Player;

/// <summary>
/// タイトル名のクラスを定義する
/// </summary>
class SpaseLetter
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="m_player">プレイヤーのポインタ</param>
	SpaseLetter();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SpaseLetter();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新する
	/// </summary>
	void Update(const float& nowTime);

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
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const tito::ANCHOR& anchor,
		const tito::POSITION_ANCHOR& positionAnchor
	);

private:
	//ゲージとベースのポインタ
	std::unique_ptr<tito::MoveUserInterface> m_SpaseLetter;

	//描画スタート時間
	float m_timer;

	//透明度
	float m_transparency;

	//透明度
	bool m_transparencyFlag;
};
