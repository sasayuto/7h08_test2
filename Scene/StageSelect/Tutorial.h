#pragma once

#include"ISelectPlayScene.h"

class StageSelectScene;
#include"Scene/GameObjects/UI/FreeUi/FreeUi.h"
/// <summary>
/// SelectTownのクラスを定義する
/// </summary>
class Tutorial :public ISelectPlayScene
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="titleScene">タイトルシーンのアドレス</param>
	Tutorial();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Tutorial()override;

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="selectFlag">シーン遷移のフラグ</param>
	void Update(const bool& selectFlag, const bool& selectStartFlag)override;

	/// <summary>
	/// 描画する
	/// </summary>
	void Render()override;

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize()override;
private:
	//背景の惑星
	std::unique_ptr <FreeUi> m_StageUI;

};

