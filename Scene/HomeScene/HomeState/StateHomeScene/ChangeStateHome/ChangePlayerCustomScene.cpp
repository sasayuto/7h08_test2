//--------------------------------------------------------------------------------------
// File: ChangeStateGunCustom.cpp
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "ChangePlayerCustomScene.h"

using namespace DirectX;

ChangePlayerCustomScene::ChangePlayerCustomScene(StateHomeScene::FSM* fsm)
{
	m_fsm = fsm;
}

ChangePlayerCustomScene::~ChangePlayerCustomScene()
{
}

// 初期化
void ChangePlayerCustomScene::Initialize()
{
	CreateDeviceDependentResources();

}

// 更新
void ChangePlayerCustomScene::Update(const float& elapsedTime)
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();

	auto homeState = m_fsm->GetOwner()->GetParentFSM();

	if (KeyboardTracker::GetInstance()->Decision())
		homeState->RequestTransition(HomeScene::HomeState::PLAYER_CUSTOM_SCENE);

	if (KeyboardTracker::GetInstance()->Up())
		m_fsm->RequestTransition(StateHomeScene::HomeState::STAGE_SELECT_SCENE);
	if (KeyboardTracker::GetInstance()->Down())
		m_fsm->RequestTransition(StateHomeScene::HomeState::OPTION_SCENE);

}

// 描画
void ChangePlayerCustomScene::Render()
{
}

// 終了処理
void ChangePlayerCustomScene::Finalize()
{
}

void ChangePlayerCustomScene::Enter()
{
	//文字枠の位置を移動
	m_fsm->GetOwner()->GetUnderBar()->SetPosition(
		DirectX::SimpleMath::Vector2(
			0, -HomeScene::LETTER_WIDTH * StateHomeScene::HomeState::PLAYER_CUSTOM_SCENE)
	);

}

void ChangePlayerCustomScene::Exit()
{
}

void ChangePlayerCustomScene::CreateDeviceDependentResources()
{
}
