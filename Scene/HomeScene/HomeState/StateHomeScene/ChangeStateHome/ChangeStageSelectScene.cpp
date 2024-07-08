//--------------------------------------------------------------------------------------
// File: ChangeStageSelectScene.cpp
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "ChangeStageSelectScene.h"

using namespace DirectX;

ChangeStageSelectScene::ChangeStageSelectScene(StateHomeScene::FSM* fsm)
{
	m_fsm = fsm;
}

ChangeStageSelectScene::~ChangeStageSelectScene()
{
}

// 初期化
void ChangeStageSelectScene::Initialize()
{
	CreateDeviceDependentResources();

}

// 更新
void ChangeStageSelectScene::Update(const float& elapsedTime)
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();

	auto homeState = m_fsm->GetOwner()->GetParentFSM();

	if (KeyboardTracker::GetInstance()->Decision())
	{
		homeState->RequestTransition(HomeScene::HomeState::STAGE_SELECT_SCENE);
		m_fsm->GetOwner()->GetParentFSM()->GetOwner()->GetTransitionState()->SetAnimationFlag(true);
	}


	if (KeyboardTracker::GetInstance()->Down())
		m_fsm->RequestTransition(StateHomeScene::HomeState::PLAYER_CUSTOM_SCENE);
}

// 描画
void ChangeStageSelectScene::Render()
{
}

// 終了処理
void ChangeStageSelectScene::Finalize()
{
}

void ChangeStageSelectScene::Enter()
{
	//文字枠の位置を移動
	m_fsm->GetOwner()->GetUnderBar()->SetPosition(
		DirectX::SimpleMath::Vector2(
			0, -HomeScene::LETTER_WIDTH * StateHomeScene::HomeState::STAGE_SELECT_SCENE)
	);
}

void ChangeStageSelectScene::Exit()
{
}

void ChangeStageSelectScene::CreateDeviceDependentResources()
{
}
