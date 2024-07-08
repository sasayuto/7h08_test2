#pragma once

#include"StatePauseScene.h"
class TitleScene;

/// <summary>
/// SelectGrandCanyonのクラスを定義する
/// </summary>
class PauseStageSelectScen :public StatePauseScene
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="titleScene">タイトルシーンのアドレス</param>
	PauseStageSelectScen();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PauseStageSelectScen()override;

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="selectFlag">シーン遷移のフラグ</param>
	void Update(const bool& selectFlag,  const bool& animationFlag)override;

	/// <summary>
	/// 描画する
	/// </summary>
	void Render()override;

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize()override;
};

