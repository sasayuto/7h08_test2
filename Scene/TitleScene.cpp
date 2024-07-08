#include "pch.h"
#include "TitleScene.h"
#include "GameTitle.h"
using namespace DirectX;

TitleScene::TitleScene() :
	m_menuSelect(nullptr),
	m_transitionState(nullptr),
	m_returnLetter(nullptr)
{

}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	m_transitionState->Initialize();
	m_returnLetter->Initialize();
	m_menuSelect->Initialize(this);
	m_menuBackGroundUI->Initialize();
}

void TitleScene::Update(float elapsedTime)
{
	//�L�[����
	auto keyboardTraker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
	if (KeyboardTracker::GetInstance()->Decision())
		m_transitionState->SetAnimationFlag(true);

	m_menuSelect->Update(m_transitionState->GetStageSelct(), m_transitionState->GetAnimationFlag());

	m_transitionState->Update(elapsedTime);

	//�^�u�������ꂽ��O�̉�ʂɖ߂�
	if (keyboardTraker.pressed.Tab)
		m_transitionState->SetAnimationReturnFlag(true);

	if (m_transitionState->GetStageReturnSelct())
		ChangeScene<GameTitle>();
	UNREFERENCED_PARAMETER(elapsedTime);
}

void TitleScene::Render()
{
	m_menuBackGroundUI->Render();
	m_menuSelect->Render();
	m_returnLetter->Render();

	m_transitionState->Render();

	auto* debugFont = SingletonDebugFont::GetInstance();
	debugFont->AddString(L"TitleScene", SimpleMath::Vector2(0.0f, debugFont->GetFontHeight()));

}

void TitleScene::Finalize()
{
	SaveGunData();
}

void TitleScene::SaveGunData()
{
	// JSON�I�u�W�F�N�g���쐬
	Json::Value root;
	// "Gun" �L�[�̔z����쐬
	Json::Value GunArray(Json::arrayValue);
	Json::Value GunElement;

	//���ږ������߂�
	GunElement["BULLET_COOL_TIME"] = Json::arrayValue;
	//�����ɏ����o�������l������
	GunElement["BULLET_COOL_TIME"].append(0.125f);

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

void TitleScene::CreateDeviceDependentResources()
{	
	//�w�i�̃C���X�^���X�𐶐�
	m_menuSelect = std::make_unique<MenuSelect>();

	m_transitionState = std::make_unique<TransitionState>();

	m_returnLetter = std::make_unique<ReturnLetter>();

	m_menuBackGroundUI = std::make_unique<MenuBackGroundUI>();
}

void TitleScene::CreateWindowSizeDependentResources()
{
}

void TitleScene::OnDeviceLost()
{
	Finalize();
}
