//--------------------------------------------------------------------------------------
// File: ChangeSoundOptionScene.cpp
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "ChangeSoundOptionScene.h"

using namespace DirectX;

ChangeSoundOptionScene::ChangeSoundOptionScene(StateOptionScene::FSM* fsm)
{
	m_fsm = fsm;
}

ChangeSoundOptionScene::~ChangeSoundOptionScene()
{
}

// 初期化
void ChangeSoundOptionScene::Initialize()
{
	CreateDeviceDependentResources();

}

// 更新
void ChangeSoundOptionScene::Update(const float& elapsedTime)
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
	auto homeState = m_fsm->GetOwner()->GetParentFSM();

	if (KeyboardTracker::GetInstance()->Decision())
		homeState->RequestTransition(OptionScene::OptionState::SOUND_OPTION_SCENE);

	if (KeyboardTracker::GetInstance()->Up())
		m_fsm->RequestTransition(StateOptionScene::OptionState::DRAW_OPTION_SCENE);
}

// 描画
void ChangeSoundOptionScene::Render()
{
}

// 終了処理
void ChangeSoundOptionScene::Finalize()
{
}

void ChangeSoundOptionScene::Enter()
{
	//文字枠の位置を移動
	m_fsm->GetOwner()->GetUnderBar()->SetPosition(
		DirectX::SimpleMath::Vector2(
			0, -HomeScene::LETTER_WIDTH * StateOptionScene::OptionState::SOUND_OPTION_SCENE)
	);
}

void ChangeSoundOptionScene::Exit()
{
}

void ChangeSoundOptionScene::CreateDeviceDependentResources()
{
}
