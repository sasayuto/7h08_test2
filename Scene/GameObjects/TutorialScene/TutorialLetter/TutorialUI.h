#pragma once
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"

#include"StateTutorialUI/IStateTutorialUI.h"
#include"../OperationTaskUI.h"

enum TUTORIAl_UIS
{
	NONE,
	WELCOME_TO_TOWN,
	WASDQE_MOVE,
	SHIFT_STOP,
	BENCH_STREET_LIGHT_GET,
	NICE_LETTER,
	SCORE_UP_LETTER,
	COIN_GET,
	CHALLENGE_LIMITS_LETTER,
	ENEMY_AND_DES_SCORE_LETTER,
	TIME_3MINUTES_LETTER,
	RECOVERY_ITEMS_GET,
	LET_IS_RECOVER_LETTER,
	TUTORIAl_UIS_COUNT,
};

/// <summary>
/// アイテムの基底クラスを定義する
/// </summary>
class TutorialUI
{
public:
	//コインフラグのセッター
	void SetCoinGetFlag(const bool& coinGetFlag) { m_coinGetFlag = coinGetFlag; }
	bool GetCoinGetFlag() { return m_coinGetFlag; };

	//コインフラグのセッター
	void SetObjectsKillFlag(const bool& objectsKillFlag) { m_objectsKillFlag = objectsKillFlag; }
	bool GetObjectsKillFlag() { return m_objectsKillFlag; }

	//コインフラグのセッター
	void SetItemsFlag(const bool& itemsFlag) { m_itemsFlag = itemsFlag; }
	bool GetItemsFlag() { return m_itemsFlag; }

	// コインフラグのセッター
	void SetCoinMissionAccomplishedFlag(const bool& coinMissionAccomplishedFlag) { m_coinMissionAccomplishedFlag = coinMissionAccomplishedFlag; }
	bool GetCoinMissionAccomplishedFlag() const { return m_coinMissionAccomplishedFlag; }

	// アイテムフラグのセッター
	void SetItemsMissionAccomplishedFlag(const bool& itemsMissionAccomplishedFlag) { m_itemsMissionAccomplishedFlag = itemsMissionAccomplishedFlag; }
	bool GetItemsMissionAccomplishedFlag() const { return m_itemsMissionAccomplishedFlag; }

	// オブジェクトキルフラグのセッター
	void SetObjectKillMissionAccomplishedFlag(const bool& objectKillMissionAccomplishedFlag) { m_ObjectKillMissionAccomplishedFlag = objectKillMissionAccomplishedFlag; }
	bool GetObjectKillMissionAccomplishedFlag() const { return m_ObjectKillMissionAccomplishedFlag; }

	// シフトフラグのセッター
	void SetShiftMissionAccomplishedFlag(const bool& shiftMissionAccomplishedFlag) { m_shiftMissionAccomplishedFlag = shiftMissionAccomplishedFlag; }
	bool GetShiftMissionAccomplishedFlag() const { return m_shiftMissionAccomplishedFlag; }

	// WASDフラグのセッター
	void SetWASDMissionAccomplishedFlag(const bool& WASDMissionAccomplishedFlag) { m_WASDMissionAccomplishedFlag = WASDMissionAccomplishedFlag; }
	bool GetWASDMissionAccomplishedFlag() const { return m_WASDMissionAccomplishedFlag; }

	// コインフラグのセッター
	void SetCoinDrawFlag(const bool& coinDrawFlag) { m_coinDrawFlag = coinDrawFlag; }
	bool GetCoinDrawFlag() const { return m_coinDrawFlag; }

	// アイテムフラグのセッター
	void SetItemsDrawFlag(const bool& itemsDrawFlag) { m_itemsDrawFlag = itemsDrawFlag; }
	bool GetItemsDrawFlag() const { return m_itemsDrawFlag; }

	// オブジェクトキルフラグのセッター
	void SetObjectKillDrawFlag(const bool& objectKillDrawFlag) { m_ObjectKillDrawFlag = objectKillDrawFlag; }
	bool GetObjectKillDrawFlag() const { return m_ObjectKillDrawFlag; }

	// シフトフラグのセッター
	void SetShiftDrawFlag(const bool& shiftDrawFlag) { m_shiftDrawFlag = shiftDrawFlag; }
	bool GetShiftDrawFlag() const { return m_shiftDrawFlag; }

	// WASDフラグのセッター
	void SetWASDDrawFlag(const bool& WASDDrawFlag) { m_WASDDrawFlag = WASDDrawFlag; }
	bool GetWASDDrawFlag() const { return m_WASDDrawFlag; }

	// タスク描画フラグのセッター
	void SetTaskDrawFlag(const bool& taskDrawFlag) { m_taskDrawFlag = taskDrawFlag; }
	bool GetTaskDrawFlag() const { return m_taskDrawFlag; }	

	//ステージ遷移フラグのセッター
	void SetSceneTransitionFlag(const bool& sceneTransitionFlag) { m_sceneTransitionFlag = sceneTransitionFlag; }
	//ステージ遷移フラグのセッター
	bool GetSceneTransitionFlag() {return m_sceneTransitionFlag; }

	std::unique_ptr<IStateTutorialUI>* GetTutorialUI() { return m_tutorialUI; }

	void SetCurrentState(IStateTutorialUI* iStateTutorialUI) 
	{ 
		m_pCurrentState = iStateTutorialUI;
		m_pCurrentState->Reset();
	}

	void SetPraiseUis(const TUTORIAl_UIS& tutorialUis) { m_praiseUis = tutorialUis; }
	TUTORIAl_UIS GetPraiseUis() { return m_praiseUis; }

	void SetNiceUis(const TUTORIAl_UIS& tutorialUis) { m_niceUis = tutorialUis; }
	TUTORIAl_UIS GetNiceUis() { return m_niceUis; }

	static const float FADE_TIME;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TutorialUI();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~TutorialUI();

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">1フレーム時間</param>
	virtual void Update(const float& elapsedTime);

	/// <summary>
	/// 描画する
	/// </summary>
	virtual void Render();

	/// <summary>
	/// 後始末
	/// </summary>
	virtual void Finalize();

private:

	std::unique_ptr<IStateTutorialUI> m_tutorialUI[TUTORIAl_UIS::TUTORIAl_UIS_COUNT];

	//タスクの順番を表す
	enum TUTORIAl_TASK_UI
	{
		WASD,
		SHIFT_STOP,
		COIN_GET,
		OBJECTS_BREAK,
		ITEMS_GET,
		TUTORIAl_TASK_COUNT,
	};
	std::unique_ptr<OperationTaskUI> m_tutorialTaskUIs[TUTORIAl_TASK_UI::TUTORIAl_TASK_COUNT];

	std::unique_ptr<TutorialLetter> m_tutorialTaskListLetter;

	IStateTutorialUI* m_pCurrentState;

	//コインをとったか
	bool m_coinGetFlag;

	//コインをとったか
	bool m_objectsKillFlag;

	//ものを破壊したか
	bool m_itemsFlag;

	//シーン遷移フラグ
	bool m_sceneTransitionFlag;

	bool m_taskDrawFlag;
	bool m_WASDMissionAccomplishedFlag;
	bool m_coinMissionAccomplishedFlag;
	bool m_shiftMissionAccomplishedFlag;
	bool m_itemsMissionAccomplishedFlag;
	bool m_ObjectKillMissionAccomplishedFlag;
	bool m_WASDDrawFlag;
	bool m_coinDrawFlag;
	bool m_shiftDrawFlag;
	bool m_itemsDrawFlag;
	bool m_ObjectKillDrawFlag;
	//次に行きたいシーンの間に複数回使用する文字があった時に使う
	TUTORIAl_UIS m_niceUis;

	//次の次に行きたいシーンの間に複数回使用する文字があった時に使う
	TUTORIAl_UIS m_praiseUis;
};
