//--------------------------------------------------------------------------------------
// File: ChangeHomeReturnScene.cpp
//
// �V�[���̐��^�Ɏg�p���Ă�������
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

// ������
void ChangeHomeReturnScene::Initialize()
{
	CreateDeviceDependentResources();

}

// �X�V
void ChangeHomeReturnScene::Update(const float& elapsedTime)
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();

	auto homeState = m_fsm->GetOwner()->GetParentFSM();

	if (KeyboardTracker::GetInstance()->Decision())
		homeState->GetOwner()->GetTransitionState()->SetAnimationFlag(true);

}

// �`��
void ChangeHomeReturnScene::Render()
{
}

// �I������
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
