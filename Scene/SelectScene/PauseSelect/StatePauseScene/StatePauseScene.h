#pragma once
#include"Scene/GameObjects/UI/Letter/StageSelectLetter.h"
#include"Scene/GameObjects/UI/UnderBar/UnderBar.h"

class PauseSelect;
class PlayScene;

/// <summary>
/// ISelectPlaySceneインターフェイスを定義する
/// </summary>
class StatePauseScene
{
public:
	PlayScene* GetPlayScene() { return m_pPlayScene; }

	PauseSelect* GetPauseSelect() { return m_pPauseSelect; }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StatePauseScene();

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize(PauseSelect* pauseSelect, PlayScene* playScene);

	/// <summary>
	/// 処理を実行する
	/// </summary>
	/// <param name="elapsedTime">選択時間</param>
	virtual void Update(const bool& selectFlag, const bool& animationFlag) = 0;

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
	virtual ~StatePauseScene() = default;

private:
	PauseSelect* m_pPauseSelect;
	PlayScene* m_pPlayScene;
};
