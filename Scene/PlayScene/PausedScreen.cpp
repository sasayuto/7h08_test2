#include "pch.h"
#include "PausedScreen.h"
#include"Scene/StageSelectScene.h"
#include"Scene/PlayScene/PlayScene.h"
using namespace DirectX;

PausedScreen::PausedScreen(Imase::Scene<UserResources>* pPlayScene) :
	m_menuSceneFlag(false),
	m_menuSceneSelectFlag(false),
	m_pPlayScene(pPlayScene)
{
}

PausedScreen::~PausedScreen()
{
}

void PausedScreen::Initialize()
{
	PausedScreen::CreateDeviceDependentResources();
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

	m_homeLetter[PausedState::RESUME_GAME]->LoadTexture(L"Resources/Textures/ReturnLetter_01.png");
	m_homeLetter[PausedState::PLAYER_CUSTOM_SCENE]->LoadTexture(L"Resources/Textures/CustomLetter.png");
	m_homeLetter[PausedState::STAGE_SELECT_SCENE]->LoadTexture(L"Resources/Textures/StageSelectLetter.png");

	for (int i = 0; i < COUNT; i++)
	{
		//当たり判定の初期化
		//位置、サイズを修正した値を渡す
		m_homeLetterCollision[i]->Initialize(
			m_homeLetter[i]->TexPositionCalculation(),
			m_underBar->TexSizeCalculation()
		);
	}

	m_transitionState->Initialize();
	m_transitionState->SetAnimationTime(0.0f);
	m_Translucent->Initialize();
	m_Translucent->SetAnimationTime(0.0f);
}

bool PausedScreen::Update(float elapsedTime)
{
	auto keyboardTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();

	m_transitionState->Update(elapsedTime);
	m_Translucent->Update(elapsedTime);
	//メニューから遷移が選ばれたら何もしない
	if (m_menuSceneSelectFlag)
	{
		m_Translucent->SetAnimationTime(0.5f);
		m_transitionState->SetAnimationFlag(true);
		//セレクトシーンへ
		if (m_transitionState->GetStageSelct())
			m_pPlayScene->ChangeScene<StageSelectScene>();

		return true;
	}

	//menuを開く閉じる
	if (keyboardTracker.pressed.Tab)
	{
		if (m_menuSceneFlag)
			m_menuSceneFlag = false;
		else
			m_menuSceneFlag = true;
	}

	if (m_menuSceneFlag)
	{
		MenuUpdate();
		return true;
	}
	return false;
}

void PausedScreen::Render()
{

	m_Translucent->Render();

	if (m_menuSceneFlag)
	{
		m_underBar->Render();

		for (int i = 0; i < COUNT; i++)
		{
			m_homeLetter[i]->Render();
		}
	}

	m_transitionState->Render();
}

void PausedScreen::Finalize()
{
}

void PausedScreen::Enter()
{
}

void PausedScreen::Exit()
{
}

void PausedScreen::CreateDeviceDependentResources()
{
	m_transitionState = std::make_unique<TransitionState>();
	m_Translucent = std::make_unique<TransitionState>();

	for (int i = 0; i < COUNT; i++)
	{
		m_homeLetter[i] = std::make_unique<tito::UserInterface>();
		m_homeLetterCollision[i] = std::make_unique<Collider::Box2D>();
	}

	m_underBar = std::make_unique<tito::MoveUserInterface>();

}

void PausedScreen::MenuInitialize()
{

}

void PausedScreen::MenuUpdate()
{
	auto keyboardTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
	auto mouse = KeyboardSingleton::GetInstance()->GetMouseState();

	//背景を暗くする
	m_Translucent->SetAnimationTime(0.5f);

	//選ばれてなかったら飛ばしとく
	m_underBar->SetPosition(DirectX::SimpleMath::Vector2(10000,10000));

	//マウスとテクスチャがあたっていたらステートを変更
	for (int i = 0; i < PausedState::COUNT; i++)
	{
		if (!m_homeLetterCollision[i]->CheckHitPoint(mouse.x, mouse.y))
			continue;

		//文字枠を移動
		m_underBar->SetPosition(DirectX::SimpleMath::Vector2(0, static_cast<float>(-90 * i)));

		//決定が押されてなかったら終了
		if (!KeyboardTracker::GetInstance()->Decision())
			continue;

		//文字枠の位置を移動
		switch (static_cast<PausedState>(i))
		{
		case PausedScreen::STAGE_SELECT_SCENE:
			m_menuSceneSelectFlag = true;
			break;
		case PausedScreen::PLAYER_CUSTOM_SCENE:
			break;
		case PausedScreen::RESUME_GAME:
			m_menuSceneFlag = false;
			break;
		case PausedScreen::COUNT:
			break;
		default:
			break;
		}
	}
}
