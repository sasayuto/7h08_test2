//--------------------------------------------------------------------------------------
// File: ChangeHomeReturnScene.cpp
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "ChangeHomeReturnScene.h"

using namespace DirectX;

ChangeHomeReturnScene::ChangeHomeReturnScene(StateHomeScene::FSM* fsm)
{
	m_fsm = fsm;
}

ChangeHomeReturnScene::~ChangeHomeReturnScene()
{
}

// 初期化
void ChangeHomeReturnScene::Initialize()
{
	CreateDeviceDependentResources();

}

// 更新
void ChangeHomeReturnScene::Update(const float& elapsedTime)
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();

	auto homeState = m_fsm->GetOwner()->GetParentFSM();

	if (KeyboardTracker::GetInstance()->Decision())
		homeState->GetOwner()->GetTransitionState()->SetAnimationFlag(true);

}

// 描画
void ChangeHomeReturnScene::Render()
{
}

// 終了処理
void ChangeHomeReturnScene::Finalize()
{
}

void ChangeHomeReturnScene::Enter()
{
}

void ChangeHomeReturnScene::Exit()
{
}

void ChangeHomeReturnScene::CreateDeviceDependentResources()
{
}
