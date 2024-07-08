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

	//�J�����̏����Z�b�g�i�r���{�[�h�A�\�[�g�A�`��͈͂Ȃǂ����߂邽�߁B���Ȃ��Ȃ�Z�b�g���Ȃ��Ă��悢�j
	Draw::GetInstance()->SetCameraTarget(m_titleCamera->GetTargetPosition());
	Draw::GetInstance()->SetCameraPosition(m_titleCamera->GetEyePosition());
	Draw::GetInstance()->SetCameraUp(m_titleCamera->GetUpPosition());
	Draw::GetInstance()->SetCameraDir(m_titleCamera->GetDir());


	m_timerShadowSpeed += elapsedTime;
	//���Ԍv��
	m_nowTimer += elapsedTime;

	m_stoneFloor->Update();
	//�J�����̍X�V����
	m_titleCamera->Update(m_enemy->GetPosition());

	//���̊Ǘ��҂̍X�V����
	m_floorManager_01->Update();

	//�G�̍X�V����
	m_enemy->Update(elapsedTime);
	m_HouseMove_03Manager->Update(elapsedTime);
	m_HouseMove_02Manager->Update(elapsedTime);
	m_HouseMove_01Manager->Update(elapsedTime);

	//������莀�񂾂�G�𐶂��Ԃ点��
	if (!m_enemy->GetSurvival())
	{
		m_enemy->SetPosition(SimpleMath::Vector3(20, 35, 10));
		m_enemy->Reset();
		m_enemy->SetIState(m_enemy->GetEnemyMotion());
	}
	m_bigBrickWallManager->Update();
	//���̍X�V����
	m_bulletManager->Update();

	//�J�ڂ̍X�V����
	m_transitionState->Update(elapsedTime);

	if (!m_transitionState->GetAnimationFlag())
	{
		//�A�j���[�V�����̕b�����I�������
		if (m_nowTimer > SELECT_TINE)
		{
			//��ʂ̈Â������X�ɉ�����
			m_transition += 0.01f;
			//�Â��̐���
			if (m_transition >= 0.5f)
				m_transition = 0.5f;
			//�����x���Z�b�g
			m_translucent->SetRemderRatio(m_transition);

			//����L�[����������J�ڃA�j���[�V�����J�n
    			if (KeyboardTracker::GetInstance()->Decision())
				m_transitionState->SetAnimationFlag(true);
		}
	}

	//����L�[����������^�C�g���A�j���[�V���������I��
	if (KeyboardTracker::GetInstance()->Decision())
		m_nowTimer = SELECT_TINE;

	//�Z���N�g�V�[����
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
	//�摜
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
	//�ǂ̊Ǘ��҂̃C���X�^���X�𐶐�
	m_HouseMove_03Manager = std::make_unique<HouseMoveObjectsManager>();
	m_HouseMove_01Manager = std::make_unique<HouseMoveObjectsManager>();
	//�ǂ̊Ǘ��҂̃C���X�^���X�𐶐�
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

	//�e�ɂȂ�I�u�W�F�N�g�͂��̊Ԃɏ���
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

			//���̕`��
		}
		m_timerShadowSpeed = 0;
	}

	Draw::GetInstance()->ShadowMapTexCreateEnd();
}
