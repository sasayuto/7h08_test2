//--------------------------------------------------------------------------------------
// File: StateStageSelectScene.cpp
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "StateStageSelectScene.h"

using namespace DirectX;

StateStageSelectScene::StateStageSelectScene(HomeScene::FSM* fsm)
{
	m_fsm = fsm;
}

StateStageSelectScene::~StateStageSelectScene()
{
}

// 初期化
void StateStageSelectScene::Initialize()
{
	CreateDeviceDependentResources();
	for (int i = 0; i < StateHomeScene::HomeState::COUNT; i++)
	{
		m_homeLetter[i]->Create(
			L"Resources/Textures/OptionLetter.png",
			DirectX::SimpleMath::Vector2(0, static_cast<float>(-(i * 90)))
			, DirectX::SimpleMath::Vector2(1, 1)
			, tito::ANCHOR::MIDDLE_CENTER
			, tito::POSITION_ANCHOR::MIDDLE_CENTER
		);
	}
	m_homeLetter[StateHomeScene::HomeState::OPTION_SCENE]->LoadTexture(L"Resources/Textures/OptionLetter.png");
	m_homeLetter[StateHomeScene::HomeState::PLAYER_CUSTOM_SCENE]->LoadTexture(L"Resources/Textures/CustomLetter.png");
	m_homeLetter[StateHomeScene::HomeState::STAGE_SELECT_SCENE]->LoadTexture(L"Resources/Textures/StageSelectLetter.png");

}

// 更新
void StateStageSelectScene::Update(const float& elapsedTime)
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();

	if (m_fsm->GetOwner()->GetTransitionState()->GetStageSelct())
		m_fsm->GetOwner()->ChangeScene<StageSelectScene>();

}

// 描画
void StateStageSelectScene::Render()
{

	for (int i = 0; i < StateHomeScene::HomeState::COUNT; i++)
	{
		m_homeLetter[i]->Render();
	}


	auto debugFont = SingletonDebugFont::GetInstance();

	//debugFont->AddString(L"StateStageSelectScene", SimpleMath::Vector2(0.0f, debugFont->GetFontHeight()));

}

// 終了処理
void StateStageSelectScene::Finalize()
{
}

void StateStageSelectScene::Enter()
{
}

void StateStageSelectScene::Exit()
{
}

void StateStageSelectScene::CreateDeviceDependentResources()
{
	for (int i = 0; i < StateHomeScene::HomeState::COUNT; i++)
	{
		m_homeLetter[i] = std::make_unique<tito::UserInterface>();
	}


}

