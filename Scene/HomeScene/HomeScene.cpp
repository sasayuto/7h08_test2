//--------------------------------------------------------------------------------------
// File: HomeScene.cpp
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "HomeScene.h"
#include"Scene/HomeScene/HomeState/StateHomeScene/StateHomeScene.h"
#include"Scene/HomeScene/HomeState/StateOptionScene/OptionScene.h"
#include"Scene/HomeScene/HomeState/StatePlayerCustomScene.h"
#include"Scene/HomeScene/HomeState/StateStageSelectScene.h"
using namespace DirectX;

// ������
void HomeScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	m_transitionState->Initialize();
	m_returnLetter->Initialize();
	m_CloudyBackGround->Initialize();
	m_CloudyBackGround->SetScale(DirectX::SimpleMath::Vector3(1000, 1000, 1000));
	for (int i = 0; i < HomeState::COUNT; i++)
	{
		m_State[i]->Initialize();	
		m_fsm->RegisterState(static_cast<HomeState>(i), m_State[i].get());
	}
	m_fsm->Start(HomeState::HOME_SCENE);
	m_stoneFloor->Initialize();

}

// �X�V
void HomeScene::Update(float elapsedTime)
{
	Mouse::Get().SetVisible(Mouse::Mode::MODE_RELATIVE);

	UNREFERENCED_PARAMETER(elapsedTime);
	m_camera->Update(
		DirectX::SimpleMath::Vector3(10,0,0),
		DirectX::SimpleMath::Quaternion::Identity
	);
	//�J�����̏����Z�b�g�i�r���{�[�h�A�\�[�g�A�`��͈͂Ȃǂ����߂邽�߁B���Ȃ��Ȃ�Z�b�g���Ȃ��Ă��悢�j
	Draw::GetInstance()->SetCameraTarget(m_camera->GetTargetPosition());
	Draw::GetInstance()->SetCameraPosition(m_camera->GetEyePosition());
	Draw::GetInstance()->SetCameraUp(m_camera->GetUpPosition());
	Draw::GetInstance()->SetCameraDir(m_camera->GetDir());
	m_stoneFloor->Update();

	//�X�e�[�g�̍X�V
	m_fsm->Update(elapsedTime);
	m_transitionState->Update(elapsedTime);
	m_returnLetter->Update(elapsedTime);

}

// �`��
void HomeScene::Render()
{
	for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
	{
		Draw::GetInstance()->DynamicShadowMapTexCreateStart(i, 0);
	}

	//�e�ɂȂ�I�u�W�F�N�g�͂��̊Ԃɏ���
		for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
		{
			Draw::GetInstance()->StaticShadowMapTexCreateStart(i, 0);
			//////���̕`��
			//m_coinManager->RenderShadowTex();
		}
	Draw::GetInstance()->ShadowMapTexCreateEnd();

	//�w�i
	m_CloudyBackGround->Render();
	Draw::GetInstance()->ShadowMapTexCreateEndCon();

	//�R�C���n�_�̕`��
	m_stoneFloor->Render();

	m_fsm->Render();
	m_returnLetter->Render();
	m_transitionState->Render();
}

// �I������
void HomeScene::Finalize()
{
	m_fsm->Finalize();
	SaveGunData();
}

// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
void HomeScene::CreateDeviceDependentResources()
{
	m_transitionState = std::make_unique<TransitionState>();

	m_returnLetter = std::make_unique<ReturnLetter>();

	m_camera = std::make_unique<TitleCamera>();
	m_stoneFloor = std::make_unique<StoneFloor>();

	m_CloudyBackGround = std::make_unique<CloudyBackGround>();
	m_fsm = std::make_unique<FSM>(this);

	m_State[HomeState::HOME_SCENE] = std::make_unique<StateHomeScene>(m_fsm.get());

	m_State[HomeState::OPTION_SCENE] = std::make_unique<OptionScene>(m_fsm.get());

	m_State[HomeState::PLAYER_CUSTOM_SCENE] = std::make_unique<StatePlayerCustomScene>(m_fsm.get());

	m_State[HomeState::STAGE_SELECT_SCENE] = std::make_unique<StateStageSelectScene>(m_fsm.get());

}

// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
void HomeScene::CreateWindowSizeDependentResources()
{

}

// �f�o�C�X���X�g�������ɌĂяo�����֐�
void HomeScene::OnDeviceLost()
{
	Finalize();
}

void HomeScene::SaveGunData()
{
	// JSON�I�u�W�F�N�g���쐬
	Json::Value root;
	// "Gun" �L�[�̔z����쐬
	Json::Value GunArray(Json::arrayValue);
	Json::Value GunElement;

	//���ږ������߂�
	GunElement["BULLET_COOL_TIME"] = Json::arrayValue;
	//�����ɏ����o�������l������
	GunElement["BULLET_COOL_TIME"].append(0.325f);

	//���ږ������߂�
	GunElement["PLAYER_MAX_SPEED"] = Json::arrayValue;
	//�����ɏ����o�������l������
	GunElement["PLAYER_MAX_SPEED"].append(15.0f / 60.0f);

	//���ږ������߂�
	GunElement["PLAYER_ACCELERATION"] = Json::arrayValue;
	//�����ɏ����o�������l������
	GunElement["PLAYER_ACCELERATION"].append(0.5f / 60.0f);

	//���ږ������߂�
	GunElement["PLAYER_BEND_ACCELERATION"] = Json::arrayValue;
	//�����ɏ����o�������l������
	GunElement["PLAYER_BEND_ACCELERATION"].append(6.0f / 60.0f);

	//���ږ������߂�
	GunElement["PLAYER_MAX_HP"] = Json::arrayValue;
	//�����ɏ����o�������l������
	GunElement["PLAYER_MAX_HP"].append(20000);

	//���ږ������߂�
	GunElement["PLAYER_MAX_FUEL"] = Json::arrayValue;
	//�����ɏ����o�������l������
	GunElement["PLAYER_MAX_FUEL"].append(5000);

	//���ږ������߂�
	GunElement["PLAYER_OFFENSIVE_POWER"] = Json::arrayValue;
	//�����ɏ����o�������l������
	GunElement["PLAYER_OFFENSIVE_POWER"].append(2);

	//�l�������
	GunArray.append(GunElement);
	// root�I�u�W�F�N�g�� "Gun"��ǉ�
	root["PlayerData"] = GunArray;
	// JSON�f�[�^�𕶎���ɕϊ�
	Json::StreamWriterBuilder writer;
	std::string jsonString = Json::writeString(writer, root);
	// JSON�f�[�^���t�@�C���ɏ����o��
	std::ofstream outputFile(L"Resources/Json/Json_playerDate.json");
	if (outputFile.is_open())
	{
		outputFile << jsonString;
		outputFile.close();
	}
}
