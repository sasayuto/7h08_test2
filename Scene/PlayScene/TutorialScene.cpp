#include "pch.h"
#include "TutorialScene.h"
#include"Scene/StageSelectScene.h"
#include"Scene/GameObjects/Models/Textures.h"
using namespace DirectX;
TutorialScene::TutorialScene() :
	m_rect(),
	m_deviceResources(nullptr),
	m_bulletManager(nullptr),
	m_Camera(nullptr),
	m_enemyManager(nullptr),
	m_player(nullptr),
	m_playerGaueg(nullptr),
	m_transitionState(nullptr),
	m_floorManager_01(nullptr),
	m_streetLightManager(nullptr),
	m_windmillManager(nullptr),
	m_coinManager(nullptr),
	m_bigBrickWallManager(nullptr),
	m_fenceManager(nullptr),
	m_timespeed(1)
{
}

TutorialScene::~TutorialScene()
{
}
void TutorialScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	PlayScene::Initialize();

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
		nullptr,
		m_windmillManager.get(),
		m_stoneFloor.get(),
		m_streetLightManager.get(),
		m_benchManager.get(),
		m_fenceManager.get(),
		nullptr,
		nullptr,	
		m_floorManager_01.get(),
		m_bigBrickWallManager.get(),
		m_HouseMove_01Manager.get(),
		m_HouseMove_02Manager.get(),
		m_HouseMove_03Manager.get()
	);

	//�`���[�g���A���Ȃ̂�HP�𔼕��ɂ���
	m_player->SetHP(m_player->GetHP() / 2);
	//�Q�[�W�̏�����
	m_playerGaueg->Initialize();

	//�I�u�W�F�N�g�̏�����
	m_objectsManager->Intialize();

	m_stoneFloor->Initialize();
	//���̏�����
	m_bulletManager->Intialize();

	m_floorManager_01->Intialize();

	//���̏�����
	m_benchManager->Intialize(m_bulletManager.get());

	m_HouseMove_03Manager->Intialize<HouseMove_03>(m_bulletManager.get(), "Resources/Json/TwonScene/Objects/MoveObjects/House/House_03.json");
	m_HouseMove_01Manager->Intialize<HouseMove_01>(m_bulletManager.get(), "Resources/Json/TwonScene/Objects/MoveObjects/House/House_01.json");
	m_HouseMove_02Manager->Intialize<HouseMove_02>(m_bulletManager.get(), "Resources/Json/TwonScene/Objects/MoveObjects/House/House_02.json");

	//���̏�����
	m_fenceManager->Intialize(m_bulletManager.get());

	//�w�i�̏�����
	m_cloudyBackGround->Initialize();
	m_cloudyBackGround->SetScale(SimpleMath::Vector3::One*1000);

	m_transitionState->Initialize();

	m_windmillManager->Intialize();

	m_streetLightManager->Intialize(m_bulletManager.get());

	m_tutorialLetters->Initialize();

	m_bigBrickWallManager->Intialize();

	m_supplyPointManager->Intialize("Resources/json/TutorialScene/Json_TutorialItem.Json");

	m_coinManager->Intialize("Resources/json/TutorialScene/Json_TutorialCoin.Json");
}

void TutorialScene::Update(float elapsedTime)
{
	PlayScene::Update(elapsedTime);
	if (GetMenuFlag())
		return;

	//�J�����̏����Z�b�g�i�r���{�[�h�A�\�[�g�A�`��͈͂Ȃǂ����߂邽�߁B���Ȃ��Ȃ�Z�b�g���Ȃ��Ă��悢�j
	Draw::GetInstance()->SetCameraTarget(m_Camera->GetTargetPosition());
	Draw::GetInstance()->SetCameraPosition(m_Camera->GetEyePosition());
	Draw::GetInstance()->SetCameraUp(m_Camera->GetUpPosition());
	Draw::GetInstance()->SetCameraDir(m_Camera->GetDir());

	//
	m_timespeed += elapsedTime;

	//�O�̃R�C���̖���
	int previousCoinNum = m_coinManager->GetCount();

	//�O�̃R�C���̖���
	int previousObjectsNum = m_streetLightManager->GetStreetLightKillCount() + m_benchManager->GetBenchKillCount();

	//�O�̃R�C���̖���
	int previousItemsNum = m_supplyPointManager->GetItemGetCount();

	//�v���C���[�̍X�V
	m_player->Update(elapsedTime);

	//�J�����̍X�V
	m_Camera->Update(m_player->GetHP(), m_player->GetCameraRotate(), m_player->GetPosition());
	m_HouseMove_03Manager->Update(elapsedTime);
	m_HouseMove_02Manager->Update(elapsedTime);
	m_HouseMove_01Manager->Update(elapsedTime);
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

	//���̍X�V
	m_supplyPointManager->Update(elapsedTime);

	//�ǂ̊Ǘ��҂̍X�V
	m_bigBrickWallManager->Update();

	//���̍X�V
	m_windmillManager->Update();

	//�Q�[�W�̍X�V
	m_playerGaueg->Update();

	//�Q�[�W�̍X�V
	m_coinManager->Update(elapsedTime);

	m_stoneFloor->Update();

	m_transitionState->Update(elapsedTime);

	m_tutorialLetters->Update(elapsedTime);

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
		ScoreCount::KindsScore::STREET_LIGHT,
		m_streetLightManager->GetStreetLightKillCount()
	);
	GetUserResources()->GetScoreCalculation()->SetScoreCount(
		ScoreCount::KindsScore::ENEMY,
		m_enemyManager->GetKillCount()
	);

	GetUserResources()->GetScoreCalculation()->SetScoreCount(
		ScoreCount::KindsScore::FENCE,
		m_fenceManager->GetBenchKillCount()
	);

	//�R�C�������P�ł��������`���[�g���A���ꂽ�[�ɕ�
	if (m_coinManager->GetCount() != previousCoinNum)
		m_tutorialLetters->SetCoinGetFlag(true);

	//�R�C�������P�ł��������`���[�g���A���ꂽ�[�ɕ�
	if (m_supplyPointManager->GetItemGetCount() != previousItemsNum)
		m_tutorialLetters->SetItemsFlag(true);

	//�I�u�W�F�N�g���P�ł��󂵂���`���[�g���A���ꂽ�[�ɕ�
	if (m_benchManager->GetBenchKillCount() +
		m_streetLightManager->GetStreetLightKillCount() != previousObjectsNum)
		m_tutorialLetters->SetObjectsKillFlag(true);

	//�`���[�g���A�����^�[���I��������X�e�[�W�J�ڊJ�n
	if (m_tutorialLetters->GetSceneTransitionFlag())
		m_transitionState->SetAnimationFlag(true);

	//�Z���N�g�V�[����
	if (m_transitionState->GetStageSelct())
		ChangeScene<StageSelectScene>();

	UNREFERENCED_PARAMETER(elapsedTime);
}

void TutorialScene::Render()
{
	ShadowMapRender();

	//�����f���̕`��
	m_cloudyBackGround->Render();

	Draw::GetInstance()->ShadowMapTexCreateEndCon();
	//���̕`��
	m_bulletManager->Render();

	//���̕`��
	m_benchManager->Render();

	//���̕`��
	m_fenceManager->Render();
	m_HouseMove_03Manager->Render();
	m_HouseMove_01Manager->Render();
	m_HouseMove_02Manager->Render();
	//���̕`��
	m_supplyPointManager->Render();

	//���̕`��
	m_streetLightManager->Render();

	m_floorManager_01->Render();

	//�G�t�F�N�g������̂͂ł��邾�����ɕ`�悷��
	
	//�R�C���n�_�̕`��
	m_stoneFloor->Render();
	//���̍X�V
	m_windmillManager->Render();

	//�I�u�W�F�N�g�̕`��
	m_objectsManager->Render();

	//�ǂ̊Ǘ��҂̕`��
	m_bigBrickWallManager->Render();
	//�R�C���n�_�̕`��
	m_coinManager->Render();


	Draw::GetInstance()->DrawEndUpdate();

	//�v���C���[�̕`��
	m_player->Render();

	//�QDUI�͂�������

	//�Q�[�W�̕`��
	m_playerGaueg->Render();

	m_tutorialLetters->Render();
	PlayScene::Render();

	m_transitionState->Render();
}

void TutorialScene::Finalize()
{
	PlayScene::Finalize();
	m_enemyManager->Finalize();
	m_player->Finalize();
	m_bulletManager->Finalize();
	//���U���g������n������
	GetUserResources()->GetScoreCalculation()->Finalize();
}

void TutorialScene::ShadowMapRender()
{
	for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
	{
		Draw::GetInstance()->DynamicShadowMapTexCreateStart(i, m_timespeed);
		m_player->RenderShadowTex();
		m_bulletManager->RenderShadowTex();
		m_benchManager->RenderShadowTex(true);
		m_fenceManager->RenderShadowTex(true);
		m_streetLightManager->RenderShadowTex(true);
		m_HouseMove_03Manager->RenderShadowTex(true);
		m_HouseMove_01Manager->RenderShadowTex(true);
		m_HouseMove_02Manager->RenderShadowTex(true);
		m_windmillManager->RenderShadowTex();

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
			//m_coinManager->RenderShadowTex();
		}
		m_timespeed = 0;
	}
	Draw::GetInstance()->ShadowMapTexCreateEnd();
}

void TutorialScene::CreateDeviceDependentResources()
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
	m_supplyPointManager = std::make_unique<SupplyPointManager>();

	//�G�̃C���X�^���X�𐶐�
	m_tutorialLetters = std::make_unique<TutorialUI>();

	//�ǂ̊Ǘ��҂̃C���X�^���X�𐶐�
	m_bigBrickWallManager = std::make_unique<BigBrickWallManager>();

	//�ǂ̊Ǘ��҂̃C���X�^���X�𐶐�
	m_fenceManager = std::make_unique<FenceManager>();

	//�ǂ̊Ǘ��҂̃C���X�^���X�𐶐�
	m_HouseMove_03Manager = std::make_unique<HouseMoveObjectsManager>();
	m_HouseMove_01Manager = std::make_unique<HouseMoveObjectsManager>();
	//�ǂ̊Ǘ��҂̃C���X�^���X�𐶐�
	m_HouseMove_02Manager = std::make_unique<HouseMoveObjectsManager>();
}

void TutorialScene::CreateWindowSizeDependentResources()
{
}

void TutorialScene::OnDeviceLost()
{
	Finalize();
}
