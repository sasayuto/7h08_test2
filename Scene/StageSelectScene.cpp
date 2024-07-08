#include "pch.h"
#include "StageSelectScene.h"
#include"HomeScene/HomeScene.h"
#include"Scene/GameObjects/Models/Textures.h"

using namespace DirectX;

const float StageSelectScene::TRANSITION_TIME(1.0f);//遷移までの時間

StageSelectScene::StageSelectScene() :
	m_stageSelect(nullptr),
	m_titleCamera(nullptr),
	m_transitionState(nullptr),
	m_stageSelectLetter(nullptr),
	m_sun(nullptr),
	m_palace(nullptr),
	m_decisionFlag(false),
	m_ReturnDecisionFlag(false),
	m_decisionStopTimer(0),
	m_m_decisionFlag(false),
	m_timerShadowSpeed(1)
{
}

StageSelectScene::~StageSelectScene()
{
}

void StageSelectScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	m_transitionState->Initialize();
	//m_stageSelectLetter->Initialize();
	m_stageSelect->Initialize(this);
	m_returnLetter->Initialize();
	m_sun->Initialize();
	Draw::GetInstance()->SetSun(m_sun.get());
	Textures::GetInstance()->SetSun(m_sun.get());
	m_player->Initialize(nullptr);
	m_palace->Initialize();
	m_decisionCol = std::make_unique<Collider::Box2D>();

	m_decision->Create(
		L"Resources/Textures/decisionTex.png"
		, DirectX::SimpleMath::Vector2(-0, -200)
		, DirectX::SimpleMath::Vector2(0.9f,0.85f)
		, tito::ANCHOR::MIDDLE_CENTER
		, tito::POSITION_ANCHOR::MIDDLE_CENTER
	);
	m_decisionCol->Initialize(m_decision->TexPositionCalculation(),
		m_decision->TexSizeCalculation()
		);
	Mouse::Get().SetVisible(Mouse::Mode::MODE_RELATIVE);

}

void StageSelectScene::Update(float elapsedTime)
{
	Mouse::Get().SetVisible(Mouse::Mode::MODE_RELATIVE);

	m_returnLetter->Update(elapsedTime);
	//キー入力
	auto kbTraker = KeyboardTracker::GetInstance()->GetKeyboardTracker();

	//選択がされた時のアニメーション中は選択できない
	m_stageSelect->Update(m_transitionState->GetStageSelct(), m_decisionFlag, m_ReturnDecisionFlag);


	m_titleCamera->Update(
		m_player->GetPosition(),
		m_player->GetRotate()
	);
	//カメラの情報をセット（ビルボード、ソート、描画範囲などを決めるため。しないならセットしなくてもよい）
	Draw::GetInstance()->SetCameraTarget(m_titleCamera->GetTargetPosition());
	Draw::GetInstance()->SetCameraPosition(m_titleCamera->GetEyePosition());
	Draw::GetInstance()->SetCameraUp(m_titleCamera->GetUpPosition());
	Draw::GetInstance()->SetCameraDir(m_titleCamera->GetDir());

	m_player->Update(elapsedTime, m_decisionFlag, m_ReturnDecisionFlag);
	//m_stageSelectLetter->Update();

	TransitionProcessing(elapsedTime, TRANSITION_TIME);

	m_transitionState->Update(elapsedTime);

	//タブが押されたら前の画面に戻る
	if(!m_decisionFlag)
	if (kbTraker.pressed.Tab)
	{
		m_transitionState->SetAnimationReturnFlag(true);
		m_ReturnDecisionFlag = true;
	}
	if (m_returnLetter->GetMouseFlag())
	{
		if (KeyboardTracker::GetInstance()->Decision())
		{
			m_transitionState->SetAnimationReturnFlag(true);
			m_ReturnDecisionFlag = true;
		}
	}

	if (m_transitionState->GetStageReturnSelct())
		ChangeScene<HomeScene>();

	m_palace->Update(elapsedTime);

	UNREFERENCED_PARAMETER(elapsedTime);

}

void StageSelectScene::Render()
{
	ShadowMapRender();
	Draw::GetInstance()->ShadowMapTexCreateEndCon();
	m_palace->Render();
	m_player->Render();
	//m_stageSelectLetter->Render();
	m_stageSelect->Render();
	m_returnLetter->Render();
	m_decision->Render();
	m_transitionState->Render();
}

void StageSelectScene::Finalize()
{
	for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
	{
		Draw::GetInstance()->DynamicShadowMapTexCreateStart(i, 1);
		Draw::GetInstance()->StaticShadowMapTexCreateStart(i, 1);
	}
}

void StageSelectScene::CreateDeviceDependentResources()
{	
	//背景のインスタンスを生成
	m_stageSelect = std::make_unique<StageSelect>();

	m_transitionState = std::make_unique<TransitionState>();

	m_titleCamera = std::make_unique<TitleCamera>();
	
	m_stageSelectLetter = std::make_unique<StageSelectLetter>();

	m_returnLetter = std::make_unique<ReturnLetter>();

	m_sun = std::make_unique<Sun>();

	//プレイヤーのインスタンスを生成
	m_player = std::make_unique<SelectPlayer>();

	//プレイヤーのインスタンスを生成
	m_decision = std::make_unique<tito::MoveUserInterface>();

	//プレイヤーのインスタンスを生成
	m_palace = std::make_unique<Palace>();

}

void StageSelectScene::CreateWindowSizeDependentResources()
{
}

void StageSelectScene::OnDeviceLost()
{
	Finalize();
}

void StageSelectScene::TransitionProcessing(const float& elapsedTime, const float& transitionTime)
{
	//アニメーション
	if (!m_ReturnDecisionFlag)
	{
		//キー入力
		auto mouse = KeyboardSingleton::GetInstance()->GetMouseState();
		auto mouseTr = KeyboardTracker::GetInstance()->GetMouseTracker();

		m_decision->SetScale(DirectX::SimpleMath::Vector2(1.f, 1.f));

		if (m_decisionCol->CheckHitPoint(mouse.x, mouse.y))
		{

			m_decision->SetScale(DirectX::SimpleMath::Vector2(1.2f, 1.2f));
			if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
				m_decisionFlag = true;;
			if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
				m_m_decisionFlag = true;
		}
		if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
		{
			m_m_decisionFlag = false;
		}

		if (m_m_decisionFlag)
			m_decision->SetBrightness(0.5f);
		else
			m_decision->SetBrightness(1);
	}

	if (m_decisionFlag)
		m_decisionStopTimer += elapsedTime;

	if (m_decisionStopTimer >= transitionTime)
		m_transitionState->SetAnimationFlag(true);


}
void StageSelectScene::ShadowMapRender()
{
	for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
	{
		Draw::GetInstance()->DynamicShadowMapTexCreateStart(i, m_timerShadowSpeed);
		m_player->ShadowMapRender();

	}
	//影になるオブジェクトはこの間に書く
	if (m_timerShadowSpeed >= Draw::SHADOW_UPDATE_SECONDS)
	{
		for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
		{
			Draw::GetInstance()->StaticShadowMapTexCreateStart(i, m_timerShadowSpeed);
		}
		m_timerShadowSpeed = 0;
	}
	Draw::GetInstance()->ShadowMapTexCreateEnd();
}
