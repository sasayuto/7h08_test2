#pragma once
class PlayScene;
class StatePauseScene;
#include"Scene/GameObjects/UI/Letter/StageSelectLetter.h"
#include"Scene/GameObjects/UI/UnderBar/UnderBar.h"

/// <summary>
/// StageSelectのクラスを定義する
/// </summary>
class PauseSelect
{
public:
	/// <summary>
/// メニュー画面の種類（順番になる）
/// </summary>
	const enum Pause
	{
		STAGE_SELECT,
		TITLE,
		PAUSE_COUNT
	};

		//UIの縦幅
		static const int WIDTH = 90;


	//選択している番号のゲッター、セッター
	int GetSelectNum() const{ return m_selectNum; }
	void SetSelectNum(const int& selectNum) { m_selectNum = selectNum; }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PauseSelect();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PauseSelect();
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="titleScene"></param>
	void Initialize(PlayScene* playScene);

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="selectFlag"></param>
	void Update(const bool& selectFlag, const bool& animationFlag);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();

	/// <summary>
	/// デバイスに依存するリソースを作成する関数
	/// </summary>
	void CreateDeviceDependentResources();

	bool GetGameStop()const { return m_gameStop; }

	void SetGameStop(const bool& gameStop) { m_gameStop = gameStop; }
private:
	//状態のポインタ
	std::unique_ptr<StatePauseScene> m_select[Pause::PAUSE_COUNT];
	// 現在の状態のポインタ
	StatePauseScene* m_pCurrentState;

	//タイトルシーンのポインタ
	PlayScene* m_titleScene;

	//選択している番号
	int m_selectNum;

	bool m_gameStop;
private:
	//背景の惑星
	std::unique_ptr <StageSelectLetter> m_object[Pause::PAUSE_COUNT];

	//回る惑星
	std::unique_ptr <UnderBar> m_underBar;

};

