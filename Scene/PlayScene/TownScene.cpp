#include "pch.h"
#include "TownScene.h"
#include"Scene/ResultScene.h"
#include"Scene/GameObjects/Models/Textures.h"
using namespace DirectX;

const float TIME_LIMIT(180.0f);		//�������ԁis�j

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

	//�J�����̃C���X�^���X�𐶐�
	m_Camera = std::make_unique<PlaySceneCamera>();
	m_Camera->Initialize();
	//�v���C���[�̏�����
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
	//�Q�[�W�̏�����
	m_playerGaueg->Initialize();
	m_HouseMove_03Manager->Intialize<HouseMove_03>(m_bulletManager.get(), "Resources/Json/TwonScene/Objects/MoveObjects/House/House_03.json");
	m_HouseMove_01Manager->Intialize<HouseMove_01>(m_bulletManager.get(), "Resources/Json/TwonScene/Objects/MoveObjects/House/House_01.json");
	m_HouseMove_02Manager->Intialize<HouseMove_02>(m_bulletManager.get(), "Resources/Json/TwonScene/Objects/MoveObjects/House/House_02.json");

	//�I�u�W�F�N�g�̏�����
	m_objectsManager->Intialize();

	m_stoneFloor->Initialize();
	//���̏�����
	m_bulletManager->Intialize();

	m_floorManager_01->Intialize();
	//���̏�����
	m_fenceManager->Intialize(m_bulletManager.get());

	//���̏�����
	m_benchManager->Intialize(m_bulletManager.get());

	//�w�i�̏�����
	m_cloudyBackGround->Initialize();
	m_cloudyBackGround->SetScale(SimpleMath::Vector3::One * 1000);

	m_transitionState->Initialize();

	m_windmillManager->Intialize();

	m_streetLightManager->Intialize(m_bulletManager.get());

	m_coinManager->Intialize("Resources/json/TwonScene/Json_TwonCoin.Json");

	m_airshipManager->Intialize(m_bulletManager.get(),m_player.get(),m_objectsManager.get());

	//�G�̏�����
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
	//�J�����̏����Z�b�g�i�r���{�[�h�A�\�[�g�A�`��͈͂Ȃǂ����߂邽�߁B���Ȃ��Ȃ�Z�b�g���Ȃ��Ă��悢�j
	Draw::GetInstance()->SetCameraTarget(m_Camera->GetTargetPosition());
	Draw::GetInstance()->SetCameraPosition(m_Camera->GetEyePosition());
	Draw::GetInstance()->SetCameraUp(m_Camera->GetUpPosition());
	Draw::GetInstance()->SetCameraDir(m_Camera->GetDir());

	//�v���C���[�̍X�V
	m_player->Update(elapsedTime);

	//�J�����̍X�V
	m_Camera->Update(m_player->GetHP(),m_player->GetCameraRotate(), m_player->GetPosition());

	//�G�̍X�V
	m_enemyManager->Update(elapsedTime);

	//�I�u�W�F�N�g�̍X�V
	m_objectsManager->Update();

	m_floorManager_01->Update();

	//���̍X�V
	m_bulletManager->Update();

	//���̍X�V
	m_benchManager->Update(elapsedTime);

	//���̍X�V
	m_fenceManager->Update(elapsedTime);
	//���̍X�V
	m_streetLightManager->Update(elapsedTime);
	m_HouseMove_03Manager->Update(elapsedTime);
	m_HouseMove_02Manager->Update(elapsedTime);
	m_HouseMove_01Manager->Update(elapsedTime);

	//���̍X�V
	m_windmillManager->Update();

	//�ǂ̊Ǘ��҂̍X�V
	m_bigBrickWallManager->Update();

	//�Q�[�W�̍X�V
	m_playerGaueg->Update();

	//�Q�[�W�̍X�V
	m_coinManager->Update(elapsedTime);

	//�Q�[�W�̍X�V
	m_airshipManager->Update(elapsedTime);

	//�Q�[�W�̍X�V
	m_sndstormManager->Update(elapsedTime);

	m_supplyPointManager->Update(elapsedTime);
	m_stoneFloor->Update();
		
	m_transitionState->Update(elapsedTime);

	//����L�[����������J�ڃA�j���[�V�����J�n
	if (GetTimer()>= TIME_LIMIT)
		m_transitionState->SetAnimationFlag(true);


	//�X�R�A�̌v�Z�̏���
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


	//���U���g�V�[����
	if (m_transitionState->GetStageSelct())
		ChangeScene<ResultScene>();

	UNREFERENCED_PARAMETER(elapsedTime);
}

void TownScene::Render()
{
	//�e�ɂȂ�I�u�W�F�N�g�͂��̊Ԃɏ���
	ShadowMapRender();
	//�����f���̕`��
	m_cloudyBackGround->Render();

	Draw::GetInstance()->ShadowMapTexCreateEndCon();

	//�G�̕`��
	m_enemyManager->Render();

	//���̕`��
	m_bulletManager->Render();

	//���̕`��
	m_benchManager->Render();
	//���̕`��
	m_fenceManager->Render();

	//���̕`��
	m_streetLightManager->Render();

	//���̕`��
	m_windmillManager->Render();
	m_HouseMove_03Manager->Render();
	m_HouseMove_01Manager->Render();
	m_HouseMove_02Manager->Render();

	m_floorManager_01->Render();

	//�G�t�F�N�g������̂͂ł��邾�����ɕ`�悷��

	//�R�C���n�_�̕`��
	m_stoneFloor->Render();

	//�R�C���n�_�̕`��
	m_supplyPointManager->Render();

	//�R�C���n�_�̕`��
	m_airshipManager->Render();

	//�ǂ̊Ǘ��҂̕`��
	m_bigBrickWallManager->Render();

	//�I�u�W�F�N�g�̕`��
	m_objectsManager->Render();

	//�R�C���n�_�̕`��
	m_coinManager->Render();

	//�v���C���[�̕`��
	m_sndstormManager->Render();

	//�v���C���[�̕`��
	m_player->Render();

	//�QDUI�͂�������

	//�Q�[�W�̕`��
	m_playerGaueg->Render();

	PlayScene::Render();
	//m_returnLetter->Render();

	m_transitionState->Render();
	Draw::GetInstance()->DrawEndUpdate();

}

void TownScene::Finalize()
{
	////�V���h�E�}�b�v�̉摜���N���A
	//Draw::GetInstance()->ShadowMapTexCreateStart();
	//Draw::GetInstance()->ShadowMapTexCreateEnd();

	PlayScene::Finalize();
	m_enemyManager->Finalize();
	m_player->Finalize();
	m_bulletManager->Finalize();
}

void TownScene::CreateDeviceDependentResources()
{
	//�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	m_objectsManager = std::make_unique<ObjectsManager>();
	//�w�i�̃C���X�^���X�𐶐�
	m_cloudyBackGround = std::make_unique<CloudyBackGround>();

	//���̃C���X�^���X�𐶐�
	m_bulletManager = std::make_unique<BulletManager>();

	//�R�C���̃C���X�^���X�𐶐�
	m_stoneFloor = std::make_unique<StoneFloor>();

	//�v���C���[�̃C���X�^���X�𐶐�
	m_player = std::make_unique<Player>();

	//�Q�[�W�̃C���X�^���X�𐶐�
	m_playerGaueg = std::make_unique<Gaueg>(m_player.get());

	//�G�̃C���X�^���X�𐶐�
	m_enemyManager = std::make_unique<EnemyManager>();

	//�G�̃C���X�^���X�𐶐�
	m_benchManager = std::make_unique<BenchManager>();

	//�G�̃C���X�^���X�𐶐�
	m_transitionState = std::make_unique<TransitionState>();

	//�G�̃C���X�^���X�𐶐�
	m_floorManager_01 = std::make_unique<FloorManager_01>();

	//�G�̃C���X�^���X�𐶐�
	m_windmillManager = std::make_unique<WindmillManager>(); 

	//�G�̃C���X�^���X�𐶐�
	m_streetLightManager = std::make_unique<StreetLightManager>();

	//�G�̃C���X�^���X�𐶐�
	m_coinManager = std::make_unique<CoinManager>();

	//�G�̃C���X�^���X�𐶐�
	m_airshipManager = std::make_unique<AirshipManager>();

	//�G�̃C���X�^���X�𐶐�
	m_supplyPointManager = std::make_unique<SupplyPointManager>();

	//�G�̃C���X�^���X�𐶐�
	m_sndstormManager = std::make_unique<SandstormManager>();
	//�ǂ̊Ǘ��҂̃C���X�^���X�𐶐�
	m_fenceManager = std::make_unique<FenceManager>();

	m_returnLetter = std::make_unique<ReturnLetter>();

	//�ǂ̊Ǘ��҂̃C���X�^���X�𐶐�
	m_bigBrickWallManager = std::make_unique<BigBrickWallManager>();
	//�ǂ̊Ǘ��҂̃C���X�^���X�𐶐�
	m_HouseMove_03Manager = std::make_unique<HouseMoveObjectsManager>();
	m_HouseMove_01Manager = std::make_unique<HouseMoveObjectsManager>();
	//�ǂ̊Ǘ��҂̃C���X�^���X�𐶐�
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

	//�e�ɂȂ�I�u�W�F�N�g�͂��̊Ԃɏ���
	if (m_timespeed >= Draw::SHADOW_UPDATE_SECONDS)
	{
		for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
		{
			Draw::GetInstance()->StaticShadowMapTexCreateStart(i, m_timespeed);
			//���̕`��
			m_streetLightManager->RenderShadowTex(false);
			m_benchManager->RenderShadowTex(false);
			m_fenceManager->RenderShadowTex(false);
			m_HouseMove_02Manager->RenderShadowTex(false);
			m_HouseMove_01Manager->RenderShadowTex(false);
			m_HouseMove_03Manager->RenderShadowTex(false);

			//�I�u�W�F�N�g�̕`��
			m_objectsManager->RenderShadowTex();
			m_bigBrickWallManager->RenderShadowTex();
			//////���̕`��
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
