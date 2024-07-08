//--------------------------------------------------------------------------------------
// File: StateOptionScene.cpp
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "StateOptionScene.h"
#include"ChangeStateOption/ChangeDrawOptionScene.h"
#include"ChangeStateOption/ChangeSoundOptionScene.h"
using namespace DirectX;

StateOptionScene::StateOptionScene(OptionScene::FSM* fsm)
{
	m_pParentFsm = fsm;
	
}

StateOptionScene::~StateOptionScene()
{
}

// 初期化
void StateOptionScene::Initialize()
{
	CreateDeviceDependentResources();

	for (int i = 0; i < COUNT; i++)
	{
		m_optionLetter[i]->Create(
			L"Resources/Textures/OptionLetter.png",
			DirectX::SimpleMath::Vector2(0, static_cast<float>(-(i * 90)))
			, DirectX::SimpleMath::Vector2(1, 1)
			, tito::ANCHOR::MIDDLE_CENTER
			, tito::POSITION_ANCHOR::MIDDLE_CENTER
		);
	}

	m_underBar->Create(
		L"Resources/Textures/LetterBase.png"
		, DirectX::SimpleMath::Vector2(0, 0)
		, DirectX::SimpleMath::Vector2(1, 1)
		, tito::ANCHOR::MIDDLE_CENTER
		, tito::POSITION_ANCHOR::MIDDLE_CENTER
	);

	m_optionLetter[OptionState::DRAW_OPTION_SCENE]->LoadTexture(L"Resources/Textures/DrawOptionLetter.png");
	m_optionLetter[OptionState::SOUND_OPTION_SCENE]->LoadTexture(L"Resources/Textures/SoundOptionLetter.png");

	for (int i = 0; i < COUNT; i++)
	{
		//当たり判定の初期化
		//位置、サイズを修正した値を渡す
		m_optionLetterCollision[i]->Initialize(
			m_optionLetter[i]->TexPositionCalculation(),
			m_underBar->TexSizeCalculation()
		);
	}

	m_fsm = std::make_unique<FSM>(this);

	m_StateDrawOptionScene = std::make_unique<ChangeDrawOptionScene>(m_fsm.get());
	m_StateDrawOptionScene->Initialize();

	m_StateSoundOptionScene = std::make_unique<ChangeSoundOptionScene>(m_fsm.get());
	m_StateSoundOptionScene->Initialize();

	m_fsm->RegisterState(StateOptionScene::OptionState::DRAW_OPTION_SCENE, m_StateDrawOptionScene.get());
	m_fsm->RegisterState(StateOptionScene::OptionState::SOUND_OPTION_SCENE, m_StateSoundOptionScene.get());

	m_fsm->Start(StateOptionScene::OptionState::DRAW_OPTION_SCENE);

}

// 更新
void StateOptionScene::Update(const float& elapsedTime)
{
	m_fsm->Update(elapsedTime);

	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
	auto mouse = KeyboardSingleton::GetInstance()->GetMouseState();

	if (m_pParentFsm->GetOwner()->GetParentFSM()->GetOwner()->GetReturnLetter()->GetMouseFlag())
		if (KeyboardTracker::GetInstance()->Decision())
			m_fsm->GetOwner()->GetParentFSM()->GetOwner()->GetParentFSM()->RequestTransition(HomeScene::HomeState::HOME_SCENE);

	if (kbTracker.pressed.Tab)
		m_fsm->GetOwner()->GetParentFSM()->GetOwner()->GetParentFSM()->RequestTransition(HomeScene::HomeState::HOME_SCENE);


	//マウスとテクスチャがあたっていたらステートを変更
	for (int i = 0; i < COUNT; i++)
	{
		if (m_optionLetterCollision[i]->CheckHitPoint(mouse.x, mouse.y))
			m_fsm->RequestTransition(static_cast<OptionState>(i));
	}

}

// 描画
void StateOptionScene::Render()
{
	m_underBar->Render();

	m_fsm->Render();
	for (int i = 0; i < COUNT; i++)
	{
		m_optionLetter[i]->Render();
	}

}

// 終了処理
void StateOptionScene::Finalize()
{
	m_fsm->Finalize();
}

void StateOptionScene::Enter()
{
}

void StateOptionScene::Exit()
{
}

void StateOptionScene::CreateDeviceDependentResources()
{
	for (int i = 0; i < COUNT; i++)
	{
		m_optionLetter[i] = std::make_unique<tito::UserInterface>();
		m_optionLetterCollision[i] = std::make_unique<Collider::Box2D>();
	}

	m_underBar = std::make_unique<tito::MoveUserInterface>();
}
