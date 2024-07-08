#pragma once

#include "ImaseLib/UserInterface.h"

/// <summary>
/// ステージ選択UIのクラスを定義する
/// </summary>
class StageSelectLetter
{
public:
	void SetPath(const wchar_t* path) { m_path = path; }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StageSelectLetter();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StageSelectLetter();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const tito::ANCHOR& anchor,
		const tito::POSITION_ANCHOR& positionAnchor);

	/// <summary>
	/// 更新する
	/// </summary>
	void Update();

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

private:
	/// <summary>
	/// UIを作る
	/// </summary>
	/// <param name="path">ゲージの画像</param>
	/// <param name="basePath">背景の画像</param>
	/// <param name="position">描画位置</param>
	/// <param name="scale">大きさ</param>
	/// <param name="anchor">画像の描画開始位置</param>
	/// <param name="anchor">画面の描画開始位置</param>
	void Add(
		const wchar_t* path,
		const wchar_t* pathBase,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const tito::ANCHOR& anchor,
		const tito::POSITION_ANCHOR& positionAnchor
	);

	const wchar_t* m_path;
	//ゲージとベースのポインタ
	std::unique_ptr<tito::UserInterface> m_titleName, m_titleNameBase;
};
