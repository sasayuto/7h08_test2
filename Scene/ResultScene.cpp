#include"pch.h"
#include "ResultScene.h"
#include"StageSelectScene.h"
using namespace DirectX;

void ResultScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();


	//スコアを計算する
	GetUserResources()->GetScoreCalculation()->Initialize();

	m_ResultBaseUI->Create(
		L"Resources/Textures/Black.png"
		, DirectX::SimpleMath::Vector2(0, 0)
		, DirectX::SimpleMath::Vector2(1, 1)
		, tito::ANCHOR::MIDDLE_CENTER
		, tito::POSITION_ANCHOR::MIDDLE_CENTER
	);
	m_ResultBaseUI->SetTransparency(0.7f);
	m_CloudyBackGround->Initialize();
	m_CloudyBackGround->SetScale(DirectX::SimpleMath::Vector3(1000, 1000, 1000));
	m_stoneFloor->Initialize();

	m_transitionState->Initialize();
	Mouse::Get().SetVisible(Mouse::Mode::MODE_RELATIVE);


}

void ResultScene::Update(float elapsedTime)
{
	Mouse::Get().SetVisible(Mouse::Mode::MODE_RELATIVE);

	//遷移の更新処理
	m_transitionState->Update(elapsedTime);

	//スコアを計算する
	GetUserResources()->GetScoreCalculation()->Update(elapsedTime);

	m_camera->Update(
		DirectX::SimpleMath::Vector3(10, 0, 0),
		DirectX::SimpleMath::Quaternion::Identity
	);
	//カメラの情報をセット（ビルボード、ソート、描画範囲などを決めるため。しないならセットしなくてもよい）
	Draw::GetInstance()->SetCameraTarget(m_camera->GetTargetPosition());
	Draw::GetInstance()->SetCameraPosition(m_camera->GetEyePosition());
	Draw::GetInstance()->SetCameraUp(m_camera->GetUpPosition());
	Draw::GetInstance()->SetCameraDir(m_camera->GetDir());
	m_stoneFloor->Update();


	//スコアの表示が終わったか
	if (GetUserResources()->GetScoreCalculation()->GetSceneTransitionFlag())
		//決定ボタンを押したか
		if (KeyboardTracker::GetInstance()->Decision())
			m_transitionState->SetAnimationFlag(true);

	//決定ボタンを押したか
	if (KeyboardTracker::GetInstance()->Decision())
		//スコアを強制表示
		GetUserResources()->GetScoreCalculation()->SetTimer(100);

	//セレクトシーンへ
	if (m_transitionState->GetStageSelct())
		ChangeScene<StageSelectScene>();

}

void ResultScene::Render()
{
	for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
	{
		Draw::GetInstance()->DynamicShadowMapTexCreateStart(i, 0);
	}

	//影になるオブジェクトはこの間に書く
	for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
	{
		Draw::GetInstance()->StaticShadowMapTexCreateStart(i, 0);
		//////球の描写
		//m_coinManager->RenderShadowTex();
	}
	Draw::GetInstance()->ShadowMapTexCreateEnd();

	//背景
	m_CloudyBackGround->Render();
	Draw::GetInstance()->ShadowMapTexCreateEndCon();

	//コイン地点の描画
	m_stoneFloor->Render();
	m_ResultBaseUI->Render();
	//スコアを計算する
	GetUserResources()->GetScoreCalculation()->Render();
	m_transitionState->Render();

}

void ResultScene::Finalize()
{
	//リザルトだけ後始末する
	GetUserResources()->GetScoreCalculation()->Finalize();
}

void ResultScene::CreateDeviceDependentResources()
{
	m_camera = std::make_unique<TitleCamera>();
	m_stoneFloor = std::make_unique<StoneFloor>();

	m_CloudyBackGround = std::make_unique<CloudyBackGround>();

	m_transitionState = std::make_unique<TransitionState>();
	m_ResultBaseUI = std::make_unique<tito::UserInterface>();
}

void ResultScene::CreateWindowSizeDependentResources()
{
}

void ResultScene::OnDeviceLost()
{
	Finalize();
}
