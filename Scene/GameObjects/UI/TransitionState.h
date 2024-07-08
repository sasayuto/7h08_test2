#pragma once

#include "ImaseLib/Transition.h"

/// <summary>
/// シーン遷移のアニメーションのクラスを定義する
/// </summary>
class TransitionState
{
public:
	//シーン遷移フラグのゲッター
	bool GetStageSelct() const { return m_stageSelct; }

	//シーン遷移フラグのゲッター
	bool GetStageReturnSelct() const { return m_stageReturnSelct; }

	//アニメーションフラグのゲッター、セッター
	bool GetAnimationFlag() const { return m_animationFlag; }
	void SetAnimationFlag(const bool& animationFlag) { m_animationFlag = animationFlag; }

	void SetAnimationReturnFlag(const bool& animationreturnFlag) { m_animationReturnFlag = animationreturnFlag; }

	//アニメーションタイムのゲッター
	float GetAnimationTime() const { return m_animationTime; }
	void SetAnimationTime(const float& animationTime) {
		m_animationTime = animationTime;
		m_transition->SetRemderRatio(m_animationTime);
	}

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TransitionState();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TransitionState();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">1フレーム時間</param>
	void Update(const float& elapsedTime);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

private:
	//シーン遷移のアニメーションのポインタ
	std::unique_ptr<tito::Transition> m_transition;

	//アニメーションの時間
	float m_animationTime;

	//シーン遷移アニメーションを開始するフラグ
	bool m_animationFlag;

	//シーン遷移フラグ
	bool m_stageSelct;

	//戻るシーン遷移アニメーションを開始するフラグ
	bool m_animationReturnFlag;

	//戻るシーン遷移フラグ
	bool m_stageReturnSelct;

	bool m_startFade;
};