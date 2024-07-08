//--------------------------------------------------------------------------------------
// File: StatePlayerCustomScene.cpp
//
// シーンの雛型に使用してください
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

// 初期化
void StatePlayerCustomScene::Initialize()
{
	CreateDeviceDependentResources();

	//初期位置
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

// 更新
void StatePlayerCustomScene::Update(const float& elapsedTime)
{

	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
	auto mouse = KeyboardSingleton::GetInstance()->GetMouseState();

	//前の画面に戻る
	if (kbTracker.pressed.Tab)
		m_fsm->RequestTransition(HomeScene::HomeState::HOME_SCENE);


	if (m_fsm->GetOwner()->GetReturnLetter()->GetMouseFlag())
		if (KeyboardTracker::GetInstance()->Decision())
			m_fsm->RequestTransition(HomeScene::HomeState::HOME_SCENE);

}

// 描画
void StatePlayerCustomScene::Render()
{
	m_underBar->Render();

	m_Letter->Render();

	auto debugFont = SingletonDebugFont::GetInstance();

	debugFont->AddString(L"StatePlayerCustomScene", SimpleMath::Vector2(0.0f, debugFont->GetFontHeight()));
}

// 終了処理
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

