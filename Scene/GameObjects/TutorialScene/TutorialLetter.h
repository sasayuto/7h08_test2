#pragma once

#include "ImaseLib/MoveUserInterface.h"

/// <summary>
/// ステージ選択UIのクラスを定義する
/// </summary>
class TutorialLetter
{
public:

	static const float TRANSPARENT_END_TIME;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TutorialLetter();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TutorialLetter();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const wchar_t* path,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const tito::ANCHOR& anchor,
		const tito::POSITION_ANCHOR& positionAnchor);

	/// <summary>
	/// 更新する
	/// </summary>
	void Update(const float& elapsedTime);

	/// <summary>
	/// 更新する
	/// </summary>
	void ReduceTransparency(const float& elapsedTime);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

private:
	//ゲージとベースのポインタ
	std::unique_ptr<tito::MoveUserInterface> m_titleName;
	//描画スタート時間
	float m_timer;

	//透明度
	float m_transparency;
};
