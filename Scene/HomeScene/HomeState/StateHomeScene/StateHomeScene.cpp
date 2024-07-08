//--------------------------------------------------------------------------------------
// File: StateHomeScene.cpp
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "StateHomeScene.h"

#include"ChangeStateHome/ChangeOptionScene.h"
#include"ChangeStateHome/ChangePlayerCustomScene.h"
#include"Scene/GameTitle.h"
#include"ChangeStateHome/ChangeStageSelectScene.h"
#include"ChangeStateHome/ChangeHomeReturnScene.h"
#include"ChangeStateHome/ChangeNoneScene.h"

using namespace DirectX;

StateHomeScene::StateHomeScene(HomeScene::FSM* fsm)
{
	m_pParentFsm = fsm;
	
}

StateHomeScene::~StateHomeScene()
{
}

// 初期化
void StateHomeScene::Initialize()
{
	CreateDeviceDependentResources();

	for (int i = 0; i < COUNT; i++)
	{
		m_homeLetter[i]->Create(
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
	m_homeLetter[HomeState::OPTION_SCENE]->LoadTexture(L"Resources/Textures/OptionLetter.png");
	m_homeLetter[HomeState::PLAYER_CUSTOM_SCENE]->LoadTexture(L"Resources/Textures/CustomLetter.png");
	m_homeLetter[HomeState::STAGE_SELECT_SCENE]->LoadTexture(L"Resources/Textures/StageSelectLetter.png");

	for (int i = 0; i < COUNT; i++)
	{
		//当たり判定の初期化
		//位置、サイズを修正した値を渡す
		m_homeLetterCollision[i]->Initialize(
			m_homeLetter[i]->TexPositionCalculation(),
			m_underBar->TexSizeCalculation()
		);
	}

	m_fsm = std::make_unique<FSM>(this);


	m_StateOptionScene = std::make_unique<ChangeOptionScene>(m_fsm.get());
	m_StateOptionScene->Initialize();

	m_StatePlayerCustomScene = std::make_unique<ChangePlayerCustomScene>(m_fsm.get());
	m_StatePlayerCustomScene->Initialize();

	m_StateStageSelectScene = std::make_unique<ChangeStageSelectScene>(m_fsm.get());
	m_StateStageSelectScene->Initialize();

	m_StateHomeReturnScene = std::make_unique<ChangeHomeReturnScene>(m_fsm.get());
	m_StateHomeReturnScene->Initialize();

	m_StateNoneScene = std::make_unique<ChangeNoneScene>(m_fsm.get());
	m_StateNoneScene->Initialize();


	m_fsm->RegisterState(HomeState::OPTION_SCENE, m_StateOptionScene.get());
	m_fsm->RegisterState(HomeState::PLAYER_CUSTOM_SCENE, m_StatePlayerCustomScene.get());
	m_fsm->RegisterState(HomeState::STAGE_SELECT_SCENE, m_StateStageSelectScene.get());
	m_fsm->RegisterState(HomeState::RETURN_SCENE, m_StateHomeReturnScene.get());
	m_fsm->RegisterState(HomeState::NONE_SCENE, m_StateNoneScene.get());
	m_fsm->Start(HomeState::NONE_SCENE);

}

// 更新
void StateHomeScene::Update(const float& elapsedTime)
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
	auto mouse = KeyboardSingleton::GetInstance()->GetMouseState();

	if (m_pParentFsm->GetOwner()->GetTransitionState()->GetStageSelct())
		m_pParentFsm->GetOwner()->ChangeScene<GameTitle>();

	if (m_pParentFsm->GetOwner()->GetTransitionState()->GetAnimationFlag())
		return;

	//前の画面に戻る
	if (kbTracker.pressed.Tab)
		m_pParentFsm->GetOwner()->GetTransitionState()->SetAnimationFlag(true);

	//前の画面に戻るアニメーションが開始したら更新しない
	m_fsm->Update(elapsedTime);

	//初めになのもしない状態に入れる
	m_fsm->RequestTransition(HomeState::NONE_SCENE);

	//マウスとテクスチャがあたっていたらステートを変更
	for (int i = 0; i < HomeState::COUNT; i++)
	{
		if (m_homeLetterCollision[i]->CheckHitPoint(mouse.x, mouse.y))
			m_fsm->RequestTransition(static_cast<HomeState>(i));
	}
	if (m_pParentFsm->GetOwner()->GetReturnLetter()->GetMouseFlag())
		m_fsm->RequestTransition(HomeState::RETURN_SCENE);
}

// 描画
void StateHomeScene::Render()
{
	m_underBar->Render();

	m_fsm->Render();
	for (int i = 0; i < COUNT; i++)
	{
		m_homeLetter[i]->Render();
	}

}

// 終了処理
void StateHomeScene::Finalize()
{
	m_fsm->Finalize();
}

void StateHomeScene::Enter()
{
	m_fsm->Start(HomeState::NONE_SCENE);
}

void StateHomeScene::Exit()
{
}

void StateHomeScene::CreateDeviceDependentResources()
{
	for (int i = 0; i < COUNT; i++)
	{
		m_homeLetter[i] = std::make_unique<tito::UserInterface>();
		m_homeLetterCollision[i] = std::make_unique<Collider::Box2D>();
	}

	m_underBar = std::make_unique<tito::MoveUserInterface>();

}
