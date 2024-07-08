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


	//�J�����̃C���X�^���X�𐶐�
	m_Camera = std::make_unique<Camera>();

	Textures::GetInstance()->SetCamera(m_Camera.get());

	//�v���C���[�̏�����
	m_player->Initialize(
		m_bulletManager.get(),
		m_respawnManager.get(),
		m_supplyPointManager.get(),
		m_objectsManager.get(),
		m_enemyManager.get(), m_coinManager.get()
	);

	//�Q�[�W�̏�����
	m_playerGaueg->Initialize(GetUserResources()->GetDeviceResources(), 
		m_rect.right, m_rect.bottom);

	//�G�̏�����
	m_enemyManager->Intialize(m_bulletManager.get(),m_player.get());

	//�A�C�e���̏�����
	m_supplyPointManager->Intialize();

	//�S�[���̏�����
	m_gool->Initialize();

	//���X�|�[���̏�����
	m_respawnManager->Intialize();

	//�R�C���̏�����
	m_coinManager->Intialize();

	//���̏�����
	m_bulletManager->Intialize();

	//�I�u�W�F�N�g�̏�����
	m_objectsManager->Intialize();

	//�w�i�̏�����
	m_grandCanyon->Initialize();
	m_grandCanyon->SetScale(SimpleMath::Vector3(300, 300, 300));

	m_transitionEnd->Initialize(GetUserResources()->GetDeviceResources());

}

void PlayScene::Update(float elapsedTime)
{

	//�v���C���[�̍X�V
	m_player->Update(elapsedTime);

	//�J�����̍X�V
	m_Camera->Update(m_player->GetCameraRotate(), m_player->GetPosition());

	//�G�̍X�V
	m_enemyManager->Update(elapsedTime);

	//�A�C�e���̍X�V
	m_supplyPointManager->Update();

	//���̍X�V
	m_bulletManager->Update();

	//�Q�[�W�̍X�V
	m_playerGaueg->Update();

	//�S�[���̍X�V
	m_gool->Update(m_player.get());

	//���X�|�[���̍X�V
	m_respawnManager->Update();

	//�I�u�W�F�N�g�̍X�V
	m_objectsManager->Update();

	//�R�C���̍X�V
	m_coinManager->Update(elapsedTime);


	m_transitionEnd->Update(elapsedTime);


	//�V�[���؂�ւ�
	if (m_coinManager->GetSceneFlag())
	{
		ChangeScene<ResultScene>();
	}

	UNREFERENCED_PARAMETER(elapsedTime);
}

void PlayScene::Render()
{
	//�����f���̕`��
	m_grandCanyon->Render();

	//�G�̕`��
	m_enemyManager->Render();

	//�⋋�n�_�̕`��
	m_supplyPointManager->Render();

	//���̕`��
	m_bulletManager->Render();

	//�Q�[�W�̕`��
	m_playerGaueg->Render();

	//���X�|�[���n�_�̕`��
	m_respawnManager->Render();

	//�I�u�W�F�N�g�̕`��
	m_objectsManager->Render();

	//���̕`��
	m_gool->Render();

	//�G�t�F�N�g������̂͂ł��邾�����ɕ`�悷��
	
	//�R�C���n�_�̕`��
	m_coinManager->Render();

	//�v���C���[�̕`��
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
	//�G�N�Z���̃}�b�v
	m_mapLoader = std::make_unique<MapLoader>();
	m_mapLoader->LoadMap();

	//�w�i�̃C���X�^���X�𐶐�
	m_grandCanyon = std::make_unique<GrandCanyon>();

	//���̃C���X�^���X�𐶐�
	m_bulletManager = std::make_unique<BulletManager>();

	//�A�C�e���̃C���X�^���X�𐶐�
	m_supplyPointManager = std::make_unique<SupplyPointManager>();

	//�S�[���̃C���X�^���X�𐶐�
	m_gool = std::make_unique<Gool>();

	//�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	m_objectsManager = std::make_unique<ObjectsManager>(m_mapLoader.get());

	//���X�|�[���̃C���X�^���X�𐶐�
	m_respawnManager = std::make_unique<RespawnManager>();

	//�R�C���̃C���X�^���X�𐶐�
	m_coinManager = std::make_unique<CoinManager>();

	//�v���C���[�̃C���X�^���X�𐶐�
	m_player = std::make_unique<Player>();

	//�Q�[�W�̃C���X�^���X�𐶐�
	m_playerGaueg = std::make_unique<tito::Gaueg>(m_player.get());

	//�G�̃C���X�^���X�𐶐�
	m_enemyManager = std::make_unique<EnemyManager>();

	//�G�̃C���X�^���X�𐶐�
	m_transitionEnd = std::make_unique<TransitionEnd>();
}

void PlayScene::CreateWindowSizeDependentResources()
{
}

void PlayScene::OnDeviceLost()
{
	Finalize();
}
