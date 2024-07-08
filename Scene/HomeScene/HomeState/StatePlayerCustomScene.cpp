//--------------------------------------------------------------------------------------
// File: StatePlayerCustomScene.cpp
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "StatePlayerCustomScene.h"
#include <fstream>

#include"../../StageSelectScene.h"

using namespace DirectX;

StatePlayerCustomScene::StatePlayerCustomScene(HomeScene::FSM* fsm)
{
	m_fsm = fsm;
}

StatePlayerCustomScene::~StatePlayerCustomScene()
{
}

// ������
void StatePlayerCustomScene::Initialize()
{
	CreateDeviceDependentResources();

	//�����ʒu
	int LETTER_POS_Y = -50;

	m_Letter->Create(
		L"Resources/Textures/OptionLetter.png",
		DirectX::SimpleMath::Vector2(0, LETTER_POS_Y)
		, DirectX::SimpleMath::Vector2(1, 1)
		, tito::ANCHOR::MIDDLE_CENTER
		, tito::POSITION_ANCHOR::MIDDLE_CENTER
	);
	m_underBar->Create(
		L"Resources/Textures/LetterBase.png"
		, DirectX::SimpleMath::Vector2(0, LETTER_POS_Y)
		, DirectX::SimpleMath::Vector2(1, 1)
		, tito::ANCHOR::MIDDLE_CENTER
		, tito::POSITION_ANCHOR::MIDDLE_CENTER
	);
	m_Letter->LoadTexture(L"Resources/Textures/CurrentlyUnavailable.png");


}

// �X�V
void StatePlayerCustomScene::Update(const float& elapsedTime)
{

	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
	auto mouse = KeyboardSingleton::GetInstance()->GetMouseState();

	//�O�̉�ʂɖ߂�
	if (kbTracker.pressed.Tab)
		m_fsm->RequestTransition(HomeScene::HomeState::HOME_SCENE);


	if (m_fsm->GetOwner()->GetReturnLetter()->GetMouseFlag())
		if (KeyboardTracker::GetInstance()->Decision())
			m_fsm->RequestTransition(HomeScene::HomeState::HOME_SCENE);

}

// �`��
void StatePlayerCustomScene::Render()
{
	m_underBar->Render();

	m_Letter->Render();

	auto debugFont = SingletonDebugFont::GetInstance();

	debugFont->AddString(L"StatePlayerCustomScene", SimpleMath::Vector2(0.0f, debugFont->GetFontHeight()));
}

// �I������
void StatePlayerCustomScene::Finalize()
{
}

void StatePlayerCustomScene::Enter()
{

}

void StatePlayerCustomScene::Exit()
{
}

void StatePlayerCustomScene::CreateDeviceDependentResources()
{
	m_Letter = std::make_unique<tito::UserInterface>();
	m_underBar = std::make_unique<tito::MoveUserInterface>();

}

