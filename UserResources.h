//--------------------------------------------------------------------------------------
// File: UserResources.h
//
// シーンへ渡すユーザーリソースクラス（サンプル）
//
// Date: 2023.4.13
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "StepTimer.h"
#include "ImaseLib/DebugFont.h"
#include"Scene/GameObjects/ScoreCalculation/ScoreCalculation.h"
// 各シーンに渡す共通リソースを記述してください
class UserResources
{
private:

	// ステップタイマー
	DX::StepTimer* m_timer;

	ScoreCalculation* m_scoreCalculation;
	// 共通ステート
	DirectX::CommonStates* m_states;

public:

	// コンストラクタ
	UserResources()
		: m_timer(nullptr)
		,m_scoreCalculation(nullptr)
	{
	}

	// ------------------------------------------ //
	// 共通ステート	
	// ------------------------------------------ //

	// 共通ステートを設定する関数
	void SetCommonStates(DirectX::CommonStates* states) { m_states = states; }

	// 共通ステートを取得する関数
	DirectX::CommonStates* GetCommonStates() { return m_states; }

	// ------------------------------------------ //
	// ステップタイマー	
	// ------------------------------------------ //

	// ステップタイマーを設定する関数
	void SetStepTimerStates(DX::StepTimer* timer) { m_timer = timer; }

	// ステップタイマーを取得する関数
	DX::StepTimer* GetStepTimer() { return m_timer; }

	// ------------------------------------------ //
	// スコア	
	// ------------------------------------------ //

	// スコアを設定する関数
	void SetScoreCalculation(ScoreCalculation* scoreCalculation) { m_scoreCalculation = scoreCalculation; }

	// スコアを取得する関数
	ScoreCalculation* GetScoreCalculation() { return m_scoreCalculation; }
};

