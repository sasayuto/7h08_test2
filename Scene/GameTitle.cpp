#include "pch.h"
#include "GameTitle.h"
#include"Scene/HomeScene/HomeScene.h"
#include"Scene/GameObjects/Models/Textures.h"
using namespace DirectX;
#include <iomanip>
#include"ImaseLib/DebugFont.h"

const float GameTitle::SELECT_TINE(3);

GameTitle::GameTitle():
	m_titleName(nullptr),
	m_titleCamera(nullptr),
	m_nowTimer(),
	m_transition(0),
	m_timerShadowSpeed(Draw::SHADOW_UPDATE_SECONDS)
{
}

GameTitle::~GameTitle()
{
}

void GameTitle::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	m_transitionState->Initialize();

	m_sun->Initialize();
	m_grandCanyon->Initialize();
	m_grandCanyon->SetScale(SimpleMath::Vector3::One * 1000.0f);
	m_bulletManager->Intialize();
	m_enemy->Initialize(
		m_bulletManager.get(),
		nullptr,
		m_objectsManager.get(),
		nullptr,
		nullptr,
		nullptr,
		m_stoneFloor.get(),
		nullptr,
		nullptr,
		m_bigBrickWallManager.get()
	);
	m_HouseMove_03Manager->Intialize<HouseMove_03>(m_bulletManager.get(), "Resources/Json/TwonScene/Objects/MoveObjects/House/House_03.json");
	m_HouseMove_01Manager->Intialize<HouseMove_01>(m_bulletManager.get(), "Resources/Json/TwonScene/Objects/MoveObjects/House/House_01.json");
	m_HouseMove_02Manager->Intialize<HouseMove_02>(m_bulletManager.get(), "Resources/Json/TwonScene/Objects/MoveObjects/House/House_02.json");

	m_objectsManager->Intialize();
	m_bigBrickWallManager->Intialize();
	m_titleName->Initialize();
	m_spaseLetter->Initialize();
	m_translucent->Create();
	m_enemy->SetPosition(SimpleMath::Vector3(20, 35,30));
	Draw::GetInstance()->SetSun(m_sun.get());
	Textures::GetInstance()->SetSun(m_sun.get());
	m_floorManager_01->Intialize();
	m_stoneFloor->Initialize();
}

void GameTitle::Update(float elapsedTime)
{

	//カメラの情報をセット（ビルボード、ソート、描画範囲などを決めるため。しないならセットしなくてもよい）
	Draw::GetInstance()->SetCameraTarget(m_titleCamera->GetTargetPosition());
	Draw::GetInstance()->SetCameraPosition(m_titleCamera->GetEyePosition());
	Draw::GetInstance()->SetCameraUp(m_titleCamera->GetUpPosition());
	Draw::GetInstance()->SetCameraDir(m_titleCamera->GetDir());


	m_timerShadowSpeed += elapsedTime;
	//時間計測
	m_nowTimer += elapsedTime;

	m_stoneFloor->Update();
	//カメラの更新処理
	m_titleCamera->Update(m_enemy->GetPosition());

	//床の管理者の更新処理
	m_floorManager_01->Update();

	//敵の更新処理
	m_enemy->Update(elapsedTime);
	m_HouseMove_03Manager->Update(elapsedTime);
	m_HouseMove_02Manager->Update(elapsedTime);
	m_HouseMove_01Manager->Update(elapsedTime);

	//無理やり死んだら敵を生き返らせる
	if (!m_enemy->GetSurvival())
	{
		m_enemy->SetPosition(SimpleMath::Vector3(20, 35, 10));
		m_enemy->Reset();
		m_enemy->SetIState(m_enemy->GetEnemyMotion());
	}
	m_bigBrickWallManager->Update();
	//球の更新処理
	m_bulletManager->Update();

	//遷移の更新処理
	m_transitionState->Update(elapsedTime);

	if (!m_transitionState->GetAnimationFlag())
	{
		//アニメーションの秒数が終わったか
		if (m_nowTimer > SELECT_TINE)
		{
			//画面の暗さを徐々に下げる
			m_transition += 0.01f;
			//暗さの制限
			if (m_transition >= 0.5f)
				m_transition = 0.5f;
			//透明度をセット
			m_translucent->SetRemderRatio(m_transition);

			//決定キーを押したら遷移アニメーション開始
    			if (KeyboardTracker::GetInstance()->Decision())
				m_transitionState->SetAnimationFlag(true);
		}
	}

	//決定キーを押したらタイトルアニメーション強制終了
	if (KeyboardTracker::GetInstance()->Decision())
		m_nowTimer = SELECT_TINE;

	//セレクトシーンへ
	if (m_transitionState->GetStageSelct())
		ChangeScene<HomeScene>();

	UNREFERENCED_PARAMETER(elapsedTime);
	m_titleName->Update(m_nowTimer);
	m_spaseLetter->Update(m_nowTimer);
}

void GameTitle::Render()
{
	ShadowMapRender();

	Draw::GetInstance()->ShadowMapTexCreateEndCon();

	m_objectsManager->Render();
	m_enemy->Render();
	m_bulletManager->Render();
	m_floorManager_01->Render();
	m_stoneFloor->Render();
	m_bigBrickWallManager->Render();
	m_HouseMove_03Manager->Render();
	m_HouseMove_01Manager->Render();
	m_HouseMove_02Manager->Render();
	m_grandCanyon->Render();

	Draw::GetInstance()->DrawEndUpdate();
	//画像
	m_translucent->Render();
	m_titleName->Render();
	m_spaseLetter->Render();
	m_transitionState->Render();

}

void GameTitle::Finalize()
{
	for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
	{
		Draw::GetInstance()->DynamicShadowMapTexCreateStart(i, 1);
		Draw::GetInstance()->StaticShadowMapTexCreateStart(i, 1);
	}

}

void GameTitle::CreateDeviceDependentResources()
{	
	m_titleName = std::make_unique<SwayUserInterface>();

	m_transitionState = std::make_unique<TransitionState>();
	m_titleCamera = std::make_unique<StageSelectCamera>();
	m_grandCanyon = std::make_unique<CloudyBackGround>();
	m_enemy = std::make_unique<Enemy_03>();
	m_bulletManager = std::make_unique<BulletManager>();
	m_objectsManager = std::make_unique<ObjectsManager>();
	m_spaseLetter = std::make_unique<SpaseLetter>();
	m_translucent = std::make_unique<tito::Transition>();
	m_sun = std::make_unique<Sun>();
	m_stoneFloor = std::make_unique<StoneFloor>();;
	m_bigBrickWallManager = std::make_unique<BigBrickWallManager>();
	m_floorManager_01 = std::make_unique<FloorManager_01>();
	//壁の管理者のインスタンスを生成
	m_HouseMove_03Manager = std::make_unique<HouseMoveObjectsManager>();
	m_HouseMove_01Manager = std::make_unique<HouseMoveObjectsManager>();
	//壁の管理者のインスタンスを生成
	m_HouseMove_02Manager = std::make_unique<HouseMoveObjectsManager>();
}

void GameTitle::CreateWindowSizeDependentResources()
{
	
}

void GameTitle::OnDeviceLost()
{
	Finalize();
}

void GameTitle::ShadowMapRender()
{
	for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
	{
		Draw::GetInstance()->DynamicShadowMapTexCreateStart(i, m_timerShadowSpeed);

		m_enemy->RenderShadowTex();
		m_HouseMove_03Manager->RenderShadowTex(true);
		m_HouseMove_01Manager->RenderShadowTex(true);
		m_HouseMove_02Manager->RenderShadowTex(true);

	}

	//影になるオブジェクトはこの間に書く
	if (m_timerShadowSpeed >= Draw::SHADOW_UPDATE_SECONDS)
	{
		for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
		{
			Draw::GetInstance()->StaticShadowMapTexCreateStart(i, m_timerShadowSpeed);
			m_objectsManager->RenderShadowTex();
			m_bigBrickWallManager->RenderShadowTex();
			m_bulletManager->RenderShadowTex();
			m_HouseMove_02Manager->RenderShadowTex(false);
			m_HouseMove_01Manager->RenderShadowTex(false);
			m_HouseMove_03Manager->RenderShadowTex(false);

			//球の描写
		}
		m_timerShadowSpeed = 0;
	}

	Draw::GetInstance()->ShadowMapTexCreateEnd();
}
