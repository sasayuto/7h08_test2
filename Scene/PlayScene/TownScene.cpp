#include "pch.h"
#include "TownScene.h"
#include"Scene/ResultScene.h"
#include"Scene/GameObjects/Models/Textures.h"
using namespace DirectX;

const float TIME_LIMIT(180.0f);		//制限時間（s）

TownScene::TownScene() :
	m_rect(),
	m_deviceResources(nullptr),
	m_bulletManager(nullptr),
	m_Camera(nullptr),
	m_enemyManager(nullptr),
	m_player(nullptr),
	m_fenceManager(nullptr),
	m_playerGaueg(nullptr),
	m_transitionState(nullptr),
	m_floorManager_01(nullptr),
	m_streetLightManager(nullptr),
	m_windmillManager(nullptr),
	m_coinManager(nullptr),
	m_supplyPointManager(nullptr), 
	m_bigBrickWallManager(nullptr),
	m_timespeed(1)
{
}

TownScene::~TownScene()
{
}

void TownScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	//カメラのインスタンスを生成
	m_Camera = std::make_unique<PlaySceneCamera>();
	m_Camera->Initialize();
	//プレイヤーの初期化
	m_player->Initialize(
		m_bulletManager.get(),
		m_enemyManager.get(),
		m_coinManager.get(),
		m_objectsManager.get(),
		nullptr,
		m_supplyPointManager.get(),
		m_airshipManager.get(),
		m_windmillManager.get(),
		m_stoneFloor.get(),
		m_streetLightManager.get(),
		m_benchManager.get(),
		m_fenceManager.get(),
		m_sndstormManager.get(),
		nullptr,
		m_floorManager_01.get(),
		m_bigBrickWallManager.get(),
		m_HouseMove_01Manager.get(),
		m_HouseMove_02Manager.get(),
		m_HouseMove_03Manager.get()

	);

	m_supplyPointManager->Intialize("Resources/json/TwonScene/Json_TwonItem.Json");
	//ゲージの初期化
	m_playerGaueg->Initialize();
	m_HouseMove_03Manager->Intialize<HouseMove_03>(m_bulletManager.get(), "Resources/Json/TwonScene/Objects/MoveObjects/House/House_03.json");
	m_HouseMove_01Manager->Intialize<HouseMove_01>(m_bulletManager.get(), "Resources/Json/TwonScene/Objects/MoveObjects/House/House_01.json");
	m_HouseMove_02Manager->Intialize<HouseMove_02>(m_bulletManager.get(), "Resources/Json/TwonScene/Objects/MoveObjects/House/House_02.json");

	//オブジェクトの初期化
	m_objectsManager->Intialize();

	m_stoneFloor->Initialize();
	//球の初期化
	m_bulletManager->Intialize();

	m_floorManager_01->Intialize();
	//球の初期化
	m_fenceManager->Intialize(m_bulletManager.get());

	//球の初期化
	m_benchManager->Intialize(m_bulletManager.get());

	//背景の初期化
	m_cloudyBackGround->Initialize();
	m_cloudyBackGround->SetScale(SimpleMath::Vector3::One * 1000);

	m_transitionState->Initialize();

	m_windmillManager->Intialize();

	m_streetLightManager->Intialize(m_bulletManager.get());

	m_coinManager->Intialize("Resources/json/TwonScene/Json_TwonCoin.Json");

	m_airshipManager->Intialize(m_bulletManager.get(),m_player.get(),m_objectsManager.get());

	//敵の初期化
	m_enemyManager->Intialize(
		m_bulletManager.get(),
		m_player.get(),
		m_objectsManager.get(),
		m_airshipManager.get(),
		m_windmillManager.get(),
		m_stoneFloor.get(),
		m_sndstormManager.get(),
		m_floorManager_01.get(),
		m_bigBrickWallManager.get()
	);


	m_sndstormManager->Intialize(m_bulletManager.get(), m_benchManager.get(),m_streetLightManager.get());

	m_returnLetter->Initialize();
	PlayScene::Initialize();

	m_bigBrickWallManager->Intialize();

}

void TownScene::Update(float elapsedTime)
{
	PlayScene::Update(elapsedTime);

	if (GetMenuFlag())
		return;

	m_timespeed += elapsedTime;
	//カメラの情報をセット（ビルボード、ソート、描画範囲などを決めるため。しないならセットしなくてもよい）
	Draw::GetInstance()->SetCameraTarget(m_Camera->GetTargetPosition());
	Draw::GetInstance()->SetCameraPosition(m_Camera->GetEyePosition());
	Draw::GetInstance()->SetCameraUp(m_Camera->GetUpPosition());
	Draw::GetInstance()->SetCameraDir(m_Camera->GetDir());

	//プレイヤーの更新
	m_player->Update(elapsedTime);

	//カメラの更新
	m_Camera->Update(m_player->GetHP(),m_player->GetCameraRotate(), m_player->GetPosition());

	//敵の更新
	m_enemyManager->Update(elapsedTime);

	//オブジェクトの更新
	m_objectsManager->Update();

	m_floorManager_01->Update();

	//球の更新
	m_bulletManager->Update();

	//球の更新
	m_benchManager->Update(elapsedTime);

	//球の更新
	m_fenceManager->Update(elapsedTime);
	//球の更新
	m_streetLightManager->Update(elapsedTime);
	m_HouseMove_03Manager->Update(elapsedTime);
	m_HouseMove_02Manager->Update(elapsedTime);
	m_HouseMove_01Manager->Update(elapsedTime);

	//球の更新
	m_windmillManager->Update();

	//壁の管理者の更新
	m_bigBrickWallManager->Update();

	//ゲージの更新
	m_playerGaueg->Update();

	//ゲージの更新
	m_coinManager->Update(elapsedTime);

	//ゲージの更新
	m_airshipManager->Update(elapsedTime);

	//ゲージの更新
	m_sndstormManager->Update(elapsedTime);

	m_supplyPointManager->Update(elapsedTime);
	m_stoneFloor->Update();
		
	m_transitionState->Update(elapsedTime);

	//決定キーを押したら遷移アニメーション開始
	if (GetTimer()>= TIME_LIMIT)
		m_transitionState->SetAnimationFlag(true);


	//スコアの計算の処理
	GetUserResources()->GetScoreCalculation()->SetScoreCount(
		ScoreCount::KindsScore::BENCH,
		m_benchManager->GetBenchKillCount()
	);
	GetUserResources()->GetScoreCalculation()->SetScoreCount(
		ScoreCount::KindsScore::COIN,
		m_coinManager->GetCount()
	);
	GetUserResources()->GetScoreCalculation()->SetScoreCount(
		ScoreCount::KindsScore::TURRET,
		m_HouseMove_01Manager->GetBenchKillCount()+ m_HouseMove_02Manager->GetBenchKillCount()+ m_HouseMove_03Manager->GetBenchKillCount()
	);
	GetUserResources()->GetScoreCalculation()->SetScoreCount(
		ScoreCount::KindsScore::STREET_LIGHT,
		m_streetLightManager->GetStreetLightKillCount()
	);
	GetUserResources()->GetScoreCalculation()->SetScoreCount(
		ScoreCount::KindsScore::ENEMY,
		m_enemyManager->GetKillCount() + m_airshipManager->GetKillCount()
	);
	
	GetUserResources()->GetScoreCalculation()->SetScoreCount(
		ScoreCount::KindsScore::FENCE,
		m_fenceManager->GetBenchKillCount()
	);


	//リザルトシーンへ
	if (m_transitionState->GetStageSelct())
		ChangeScene<ResultScene>();

	UNREFERENCED_PARAMETER(elapsedTime);
}

void TownScene::Render()
{
	//影になるオブジェクトはこの間に書く
	ShadowMapRender();
	//床モデルの描画
	m_cloudyBackGround->Render();

	Draw::GetInstance()->ShadowMapTexCreateEndCon();

	//敵の描写
	m_enemyManager->Render();

	//球の描写
	m_bulletManager->Render();

	//球の描写
	m_benchManager->Render();
	//球の描写
	m_fenceManager->Render();

	//球の描写
	m_streetLightManager->Render();

	//球の描写
	m_windmillManager->Render();
	m_HouseMove_03Manager->Render();
	m_HouseMove_01Manager->Render();
	m_HouseMove_02Manager->Render();

	m_floorManager_01->Render();

	//エフェクトがあるのはできるだけ下に描画する

	//コイン地点の描画
	m_stoneFloor->Render();

	//コイン地点の描画
	m_supplyPointManager->Render();

	//コイン地点の描画
	m_airshipManager->Render();

	//壁の管理者の描写
	m_bigBrickWallManager->Render();

	//オブジェクトの描写
	m_objectsManager->Render();

	//コイン地点の描画
	m_coinManager->Render();

	//プレイヤーの描写
	m_sndstormManager->Render();

	//プレイヤーの描写
	m_player->Render();

	//２DUIはここから

	//ゲージの描写
	m_playerGaueg->Render();

	PlayScene::Render();
	//m_returnLetter->Render();

	m_transitionState->Render();
	Draw::GetInstance()->DrawEndUpdate();

}

void TownScene::Finalize()
{
	////シャドウマップの画像をクリア
	//Draw::GetInstance()->ShadowMapTexCreateStart();
	//Draw::GetInstance()->ShadowMapTexCreateEnd();

	PlayScene::Finalize();
	m_enemyManager->Finalize();
	m_player->Finalize();
	m_bulletManager->Finalize();
}

void TownScene::CreateDeviceDependentResources()
{
	//オブジェクトのインスタンスを生成
	m_objectsManager = std::make_unique<ObjectsManager>();
	//背景のインスタンスを生成
	m_cloudyBackGround = std::make_unique<CloudyBackGround>();

	//球のインスタンスを生成
	m_bulletManager = std::make_unique<BulletManager>();

	//コインのインスタンスを生成
	m_stoneFloor = std::make_unique<StoneFloor>();

	//プレイヤーのインスタンスを生成
	m_player = std::make_unique<Player>();

	//ゲージのインスタンスを生成
	m_playerGaueg = std::make_unique<Gaueg>(m_player.get());

	//敵のインスタンスを生成
	m_enemyManager = std::make_unique<EnemyManager>();

	//敵のインスタンスを生成
	m_benchManager = std::make_unique<BenchManager>();

	//敵のインスタンスを生成
	m_transitionState = std::make_unique<TransitionState>();

	//敵のインスタンスを生成
	m_floorManager_01 = std::make_unique<FloorManager_01>();

	//敵のインスタンスを生成
	m_windmillManager = std::make_unique<WindmillManager>(); 

	//敵のインスタンスを生成
	m_streetLightManager = std::make_unique<StreetLightManager>();

	//敵のインスタンスを生成
	m_coinManager = std::make_unique<CoinManager>();

	//敵のインスタンスを生成
	m_airshipManager = std::make_unique<AirshipManager>();

	//敵のインスタンスを生成
	m_supplyPointManager = std::make_unique<SupplyPointManager>();

	//敵のインスタンスを生成
	m_sndstormManager = std::make_unique<SandstormManager>();
	//壁の管理者のインスタンスを生成
	m_fenceManager = std::make_unique<FenceManager>();

	m_returnLetter = std::make_unique<ReturnLetter>();

	//壁の管理者のインスタンスを生成
	m_bigBrickWallManager = std::make_unique<BigBrickWallManager>();
	//壁の管理者のインスタンスを生成
	m_HouseMove_03Manager = std::make_unique<HouseMoveObjectsManager>();
	m_HouseMove_01Manager = std::make_unique<HouseMoveObjectsManager>();
	//壁の管理者のインスタンスを生成
	m_HouseMove_02Manager = std::make_unique<HouseMoveObjectsManager>();

}

void TownScene::CreateWindowSizeDependentResources()
{
}

void TownScene::ShadowMapRender()
{
	for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
	{
		Draw::GetInstance()->DynamicShadowMapTexCreateStart(i, m_timespeed);
		m_player->RenderShadowTex();
		m_fenceManager->RenderShadowTex(true);
		m_bulletManager->RenderShadowTex();
		m_benchManager->RenderShadowTex(true);
		m_streetLightManager->RenderShadowTex(true);
		m_windmillManager->RenderShadowTex();
		m_HouseMove_03Manager->RenderShadowTex(true);
		m_HouseMove_01Manager->RenderShadowTex(true);
		m_HouseMove_02Manager->RenderShadowTex(true);


	}

	//影になるオブジェクトはこの間に書く
	if (m_timespeed >= Draw::SHADOW_UPDATE_SECONDS)
	{
		for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
		{
			Draw::GetInstance()->StaticShadowMapTexCreateStart(i, m_timespeed);
			//球の描写
			m_streetLightManager->RenderShadowTex(false);
			m_benchManager->RenderShadowTex(false);
			m_fenceManager->RenderShadowTex(false);
			m_HouseMove_02Manager->RenderShadowTex(false);
			m_HouseMove_01Manager->RenderShadowTex(false);
			m_HouseMove_03Manager->RenderShadowTex(false);

			//オブジェクトの描写
			m_objectsManager->RenderShadowTex();
			m_bigBrickWallManager->RenderShadowTex();
			//////球の描写
			m_coinManager->RenderShadowTex();
			m_supplyPointManager->RenderShadowTex();
		}
		m_timespeed = 0;
	}

	Draw::GetInstance()->ShadowMapTexCreateEnd();

}

void TownScene::OnDeviceLost()
{
	Finalize();
}
