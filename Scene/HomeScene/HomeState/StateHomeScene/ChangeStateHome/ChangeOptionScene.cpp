//--------------------------------------------------------------------------------------
// File: ChangeStateItem.cpp
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "ChangeOptionScene.h"

using namespace DirectX;

ChangeOptionScene::ChangeOptionScene(StateHomeScene::FSM* fsm)
{
	m_fsm = fsm;
}

ChangeOptionScene::~ChangeOptionScene()
{
}

// 初期化
void ChangeOptionScene::Initialize()
{
	CreateDeviceDependentResources();

}

// 更新
void ChangeOptionScene::Update(const float& elapsedTime)
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();

	auto homeState = m_fsm->GetOwner()->GetParentFSM();

	if (KeyboardTracker::GetInstance()->Decision())
		homeState->RequestTransition(HomeScene::HomeState::OPTION_SCENE);

	if (KeyboardTracker::GetInstance()->Up())
		m_fsm->RequestTransition(StateHomeScene::HomeState::PLAYER_CUSTOM_SCENE);
}

// 描画
void ChangeOptionScene::Render()
{
}

// 終了処理
void ChangeOptionScene::Finalize()
{
}

void ChangeOptionScene::Enter()
{
	//文字枠の位置を移動
	m_fsm->GetOwner()->GetUnderBar()->SetPosition(
		DirectX::SimpleMath::Vector2(
			0, -HomeScene::LETTER_WIDTH * StateHomeScene::HomeState::OPTION_SCENE)
	);
}

void ChangeOptionScene::Exit()
{
}

void ChangeOptionScene::CreateDeviceDependentResources()
{
}
