//--------------------------------------------------------------------------------------
// File: ChangeStageSelectScene.cpp
//
// �V�[���̐��^�Ɏg�p���Ă�������
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

// ������
void ChangeStageSelectScene::Initialize()
{
	CreateDeviceDependentResources();

}

// �X�V
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

// �`��
void ChangeStageSelectScene::Render()
{
}

// �I������
void ChangeStageSelectScene::Finalize()
{
}

void ChangeStageSelectScene::Enter()
{
	//�����g�̈ʒu���ړ�
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
