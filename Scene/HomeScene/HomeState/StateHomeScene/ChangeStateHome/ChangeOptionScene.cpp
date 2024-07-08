//--------------------------------------------------------------------------------------
// File: ChangeStateItem.cpp
//
// �V�[���̐��^�Ɏg�p���Ă�������
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

// ������
void ChangeOptionScene::Initialize()
{
	CreateDeviceDependentResources();

}

// �X�V
void ChangeOptionScene::Update(const float& elapsedTime)
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();

	auto homeState = m_fsm->GetOwner()->GetParentFSM();

	if (KeyboardTracker::GetInstance()->Decision())
		homeState->RequestTransition(HomeScene::HomeState::OPTION_SCENE);

	if (KeyboardTracker::GetInstance()->Up())
		m_fsm->RequestTransition(StateHomeScene::HomeState::PLAYER_CUSTOM_SCENE);
}

// �`��
void ChangeOptionScene::Render()
{
}

// �I������
void ChangeOptionScene::Finalize()
{
}

void ChangeOptionScene::Enter()
{
	//�����g�̈ʒu���ړ�
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
