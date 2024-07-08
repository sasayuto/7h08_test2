#pragma once

#include"StateMenuScene.h"
class TitleScene;

/// <summary>
/// SelectGrandCanyonのクラスを定義する
/// </summary>
class OptionSelectScene :public StateMenuScene
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="titleScene">タイトルシーンのアドレス</param>
	OptionSelectScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OptionSelectScene()override;

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="selectFlag">シーン遷移のフラグ</param>
	void Update(const bool& selectFlag)override;

	/// <summary>
	/// 描画する
	/// </summary>
	void Render()override;


	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize()override;
};

