#pragma once
#include"Scene/GameObjects/UI/Letter/StageSelectLetter.h"
#include"Scene/GameObjects/UI/UnderBar/UnderBar.h"

class MenuSelect;
class TitleScene;

/// <summary>
/// ISelectPlaySceneインターフェイスを定義する
/// </summary>
class StateMenuScene
{
public:
	TitleScene* GetTitleScene() { return m_pTitleScene; }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StateMenuScene();

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize(MenuSelect* menuSelect, TitleScene* titleScene);

	/// <summary>
	/// 処理を実行する
	/// </summary>
	/// <param name="elapsedTime">選択時間</param>
	virtual void Update(const bool& selectFlag) = 0;

	/// <summary>
	/// 描画する
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// 後始末をする
	/// </summary>
	virtual void Finalize() = 0;

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~StateMenuScene() = default;

private:
	MenuSelect* m_pMenuSelect;
	TitleScene* m_pTitleScene;
};
