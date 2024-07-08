#include "pch.h"
#include "PlayScene.h"
#include"ResultScene.h"
#include"Scene/GameObjects/Models/Textures.h"
using namespace DirectX;

PlayScene::PlayScene() :
	m_rect(),
	m_deviceResources(nullptr),
	m_bulletManager(nullptr),
	m_Camera(nullptr),
	m_enemyManager(nullptr),
	m_player(nullptr),
	m_playerGaueg(nullptr),
	m_supplyPointManager(nullptr),
	m_respawnManager(nullptr),
	m_mapLoader(nullptr),
	m_objectsManager(nullptr),
	m_gool(nullptr),
	m_coinManager(nullptr),
	m_transitionEnd(nullptr)
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	m_rect = GetUserResources()->GetDeviceResources()->GetOutputSize();
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();


	//カメラのインスタンスを生成
	m_Camera = std::make_unique<Camera>();

	Textures::GetInstance()->SetCamera(m_Camera.get());

	//プレイヤーの初期化
	m_player->Initialize(
		m_bulletManager.get(),
		m_respawnManager.get(),
		m_supplyPointManager.get(),
		m_objectsManager.get(),
		m_enemyManager.get(), m_coinManager.get()
	);

	//ゲージの初期化
	m_playerGaueg->Initialize(GetUserResources()->GetDeviceResources(), 
		m_rect.right, m_rect.bottom);

	//敵の初期化
	m_enemyManager->Intialize(m_bulletManager.get(),m_player.get());

	//アイテムの初期化
	m_supplyPointManager->Intialize();

	//ゴールの初期化
	m_gool->Initialize();

	//リスポーンの初期化
	m_respawnManager->Intialize();

	//コインの初期化
	m_coinManager->Intialize();

	//球の初期化
	m_bulletManager->Intialize();

	//オブジェクトの初期化
	m_objectsManager->Intialize();

	//背景の初期化
	m_grandCanyon->Initialize();
	m_grandCanyon->SetScale(SimpleMath::Vector3(300, 300, 300));

	m_transitionEnd->Initialize(GetUserResources()->GetDeviceResources());

}

void PlayScene::Update(float elapsedTime)
{

	//プレイヤーの更新
	m_player->Update(elapsedTime);

	//カメラの更新
	m_Camera->Update(m_player->GetCameraRotate(), m_player->GetPosition());

	//敵の更新
	m_enemyManager->Update(elapsedTime);

	//アイテムの更新
	m_supplyPointManager->Update();

	//球の更新
	m_bulletManager->Update();

	//ゲージの更新
	m_playerGaueg->Update();

	//ゴールの更新
	m_gool->Update(m_player.get());

	//リスポーンの更新
	m_respawnManager->Update();

	//オブジェクトの更新
	m_objectsManager->Update();

	//コインの更新
	m_coinManager->Update(elapsedTime);


	m_transitionEnd->Update(elapsedTime);


	//シーン切り替え
	if (m_coinManager->GetSceneFlag())
	{
		ChangeScene<ResultScene>();
	}

	UNREFERENCED_PARAMETER(elapsedTime);
}

void PlayScene::Render()
{
	//床モデルの描画
	m_grandCanyon->Render();

	//敵の描写
	m_enemyManager->Render();

	//補給地点の描画
	m_supplyPointManager->Render();

	//球の描写
	m_bulletManager->Render();

	//ゲージの描写
	m_playerGaueg->Render();

	//リスポーン地点の描画
	m_respawnManager->Render();

	//オブジェクトの描写
	m_objectsManager->Render();

	//球の描写
	m_gool->Render();

	//エフェクトがあるのはできるだけ下に描画する
	
	//コイン地点の描画
	m_coinManager->Render();

	//プレイヤーの描写
	m_player->Render();

	m_transitionEnd->Render();


	wchar_t buft[32];
	swprintf_s(buft, 32, L"%d", m_enemyManager->GetKillCount());
	auto* debugFont = GetUserResources()->GetDebugFont();
	debugFont->AddString(buft, SimpleMath::Vector2(0.0f, 120.0f));

	swprintf_s(buft, 32, L"%d", m_player->GetCharacterHP());
	debugFont->AddString(buft, SimpleMath::Vector2(0.0f, 140.0f));
	swprintf_s(buft, 32, L"%d", m_coinManager->GetCount());
	debugFont->AddString(buft, SimpleMath::Vector2(0.0f, 160.0f));

}

void PlayScene::Finalize()
{
	m_enemyManager->Finalize();
	m_player->Finalize();
	m_bulletManager->Finalize();
	m_supplyPointManager->Finalize();
}

void PlayScene::CreateDeviceDependentResources()
{
	//エクセルのマップ
	m_mapLoader = std::make_unique<MapLoader>();
	m_mapLoader->LoadMap();

	//背景のインスタンスを生成
	m_grandCanyon = std::make_unique<GrandCanyon>();

	//球のインスタンスを生成
	m_bulletManager = std::make_unique<BulletManager>();

	//アイテムのインスタンスを生成
	m_supplyPointManager = std::make_unique<SupplyPointManager>();

	//ゴールのインスタンスを生成
	m_gool = std::make_unique<Gool>();

	//オブジェクトのインスタンスを生成
	m_objectsManager = std::make_unique<ObjectsManager>(m_mapLoader.get());

	//リスポーンのインスタンスを生成
	m_respawnManager = std::make_unique<RespawnManager>();

	//コインのインスタンスを生成
	m_coinManager = std::make_unique<CoinManager>();

	//プレイヤーのインスタンスを生成
	m_player = std::make_unique<Player>();

	//ゲージのインスタンスを生成
	m_playerGaueg = std::make_unique<tito::Gaueg>(m_player.get());

	//敵のインスタンスを生成
	m_enemyManager = std::make_unique<EnemyManager>();

	//敵のインスタンスを生成
	m_transitionEnd = std::make_unique<TransitionEnd>();
}

void PlayScene::CreateWindowSizeDependentResources()
{
}

void PlayScene::OnDeviceLost()
{
	Finalize();
}
