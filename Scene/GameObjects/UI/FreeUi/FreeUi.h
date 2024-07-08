#pragma once

#include "ImaseLib/UserInterface.h"

/// <summary>
/// ステージ選択UIのクラスを定義する
/// </summary>
class FreeUi
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	FreeUi();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~FreeUi();

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
	void Update();

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

private:
	//ゲージとベースのポインタ
	std::unique_ptr<tito::UserInterface> m_titleName;
};
