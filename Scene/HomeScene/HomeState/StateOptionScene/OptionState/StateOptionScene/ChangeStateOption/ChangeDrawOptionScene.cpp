//--------------------------------------------------------------------------------------
// File: ChangeStateItem.cpp
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "ChangeDrawOptionScene.h"

using namespace DirectX;

ChangeDrawOptionScene::ChangeDrawOptionScene(StateOptionScene::FSM* fsm)
{
	m_fsm = fsm;
}

ChangeDrawOptionScene::~ChangeDrawOptionScene()
{
}

// 初期化
void ChangeDrawOptionScene::Initialize()
{
	CreateDeviceDependentResources();

}

// 更新
void ChangeDrawOptionScene::Update(const float& elapsedTime)
{
	auto homeState = m_fsm->GetOwner()->GetParentFSM();
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();

	if (KeyboardTracker::GetInstance()->Decision())
		homeState->RequestTransition(OptionScene::OptionState::DRAW_OPTION_SCENE);

	if (KeyboardTracker::GetInstance()->Down())
		m_fsm->RequestTransition(StateOptionScene::OptionState::SOUND_OPTION_SCENE);

}

// 描画
void ChangeDrawOptionScene::Render()
{
}

// 終了処理
void ChangeDrawOptionScene::Finalize()
{
}

void ChangeDrawOptionScene::Enter()
{
	//文字枠の位置を移動
	m_fsm->GetOwner()->GetUnderBar()->SetPosition(
		DirectX::SimpleMath::Vector2(
			0, -HomeScene::LETTER_WIDTH * StateOptionScene::OptionState::DRAW_OPTION_SCENE)
	);
}

void ChangeDrawOptionScene::Exit()
{
}

void ChangeDrawOptionScene::CreateDeviceDependentResources()
{
}
