//--------------------------------------------------------------------------------------
// File: ChangeStateItem.cpp
//
// �V�[���̐��^�Ɏg�p���Ă�������
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

// ������
void ChangeDrawOptionScene::Initialize()
{
	CreateDeviceDependentResources();

}

// �X�V
void ChangeDrawOptionScene::Update(const float& elapsedTime)
{
	auto homeState = m_fsm->GetOwner()->GetParentFSM();
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();

	if (KeyboardTracker::GetInstance()->Decision())
		homeState->RequestTransition(OptionScene::OptionState::DRAW_OPTION_SCENE);

	if (KeyboardTracker::GetInstance()->Down())
		m_fsm->RequestTransition(StateOptionScene::OptionState::SOUND_OPTION_SCENE);

}

// �`��
void ChangeDrawOptionScene::Render()
{
}

// �I������
void ChangeDrawOptionScene::Finalize()
{
}

void ChangeDrawOptionScene::Enter()
{
	//�����g�̈ʒu���ړ�
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
