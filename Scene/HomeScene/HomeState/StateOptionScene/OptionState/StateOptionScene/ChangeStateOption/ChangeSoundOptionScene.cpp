//--------------------------------------------------------------------------------------
// File: ChangeSoundOptionScene.cpp
//
// �V�[���̐��^�Ɏg�p���Ă�������
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

// ������
void ChangeSoundOptionScene::Initialize()
{
	CreateDeviceDependentResources();

}

// �X�V
void ChangeSoundOptionScene::Update(const float& elapsedTime)
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
	auto homeState = m_fsm->GetOwner()->GetParentFSM();

	if (KeyboardTracker::GetInstance()->Decision())
		homeState->RequestTransition(OptionScene::OptionState::SOUND_OPTION_SCENE);

	if (KeyboardTracker::GetInstance()->Up())
		m_fsm->RequestTransition(StateOptionScene::OptionState::DRAW_OPTION_SCENE);
}

// �`��
void ChangeSoundOptionScene::Render()
{
}

// �I������
void ChangeSoundOptionScene::Finalize()
{
}

void ChangeSoundOptionScene::Enter()
{
	//�����g�̈ʒu���ړ�
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
