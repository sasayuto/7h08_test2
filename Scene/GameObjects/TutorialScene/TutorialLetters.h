#pragma once
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"
/// <summary>
/// アイテムの基底クラスを定義する
/// </summary>
class TutorialLetters
{
public:
	//コインフラグのセッター
	void SetCoinGetFlag(const bool& coinGetFlag) { m_coinGetFlag = coinGetFlag; }

	//コインフラグのセッター
	void SetObjectsKillFlag(const bool& objectsKillFlag) { m_objectsKillFlag = objectsKillFlag; }

	//ステージ遷移フラグのセッター
	void SetSceneTransitionFlag(const bool& sceneTransitionFlag) { m_sceneTransitionFlag = sceneTransitionFlag; }
	//ステージ遷移フラグのセッター
	bool GetSceneTransitionFlag() {return m_sceneTransitionFlag; }

	static const float FADE_TIME;


	/// <summary>
	/// コンストラクタ
	/// </summary>
	TutorialLetters();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~TutorialLetters();

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
	std::unique_ptr<TutorialLetter> m_WelcomeToTownLetter;
	std::unique_ptr<TutorialLetter> m_challengeLimitsLetter;
	std::unique_ptr<TutorialLetter> m_CoinGetLtter;
	std::unique_ptr<TutorialLetter> m_EnemyAndDesScoreLetter;
	std::unique_ptr<TutorialLetter> m_niceLetter;
	std::unique_ptr<TutorialLetter> m_niceLetter_02;
	std::unique_ptr<TutorialLetter> m_ScoreUpLetter;
	std::unique_ptr<TutorialLetter> m_ScoreUpLetter_02;
	std::unique_ptr<TutorialLetter> m_Time3minutesLetter;
	std::unique_ptr<TutorialLetter> m_BenchStreetLightGetLtter;

	std::unique_ptr<tito::OperationUI> m_operationUI[1];
	float m_timer;

	float m_adjustedTime;

	//コインをとったか
	bool m_coinGetFlag;

	//ものを破壊したか
	bool m_objectsKillFlag;

	bool m_sceneTransitionFlag;
};
