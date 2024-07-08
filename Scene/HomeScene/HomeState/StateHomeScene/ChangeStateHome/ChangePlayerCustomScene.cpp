//--------------------------------------------------------------------------------------
// File: ChangeStateGunCustom.cpp
//
// �V�[���̐��^�Ɏg�p���Ă�������
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

// ������
void ChangePlayerCustomScene::Initialize()
{
	CreateDeviceDependentResources();

}

// �X�V
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

// �`��
void ChangePlayerCustomScene::Render()
{
}

// �I������
void ChangePlayerCustomScene::Finalize()
{
}

void ChangePlayerCustomScene::Enter()
{
	//�����g�̈ʒu���ړ�
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
