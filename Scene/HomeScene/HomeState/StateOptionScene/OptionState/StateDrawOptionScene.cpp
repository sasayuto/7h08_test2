//--------------------------------------------------------------------------------------
// File: StateIteme.cpp
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "StateDrawOptionScene.h"
#include "Scene/GameObjects/Models/Draw.h"

using namespace DirectX;

const int StateDrawOptionScene::DRAW_MAX_DISTANCE(1000);
const int StateDrawOptionScene::DRAW_MIN_DISTANCE(300);

StateDrawOptionScene::StateDrawOptionScene(OptionScene::FSM* fsm):
	m_drawDistance(0)
{
	m_fsm = fsm;
}

StateDrawOptionScene::~StateDrawOptionScene()
{
}

// ������
void StateDrawOptionScene::Initialize()
{	
	CreateDeviceDependentResources();
	std::ifstream obj("Resources/json/Json_DrawOptionDate.Json");
	Json::CharReaderBuilder reader;
	Json::Value root;

	// �t�@�C�����J����Ă��邩���m�F���܂��B
	if (obj.is_open()) {
		std::string errors;

		// �t�@�C������JSON���p�[�X���܂��B
		if (Json::parseFromStream(reader, obj, &root, &errors))
		{
			// JSON�� "house" �����݂��A�z��ł��邩�ǂ������m�F���܂��B
			if (root.isMember("DrawOption") && root["DrawOption"].isArray())
			{
				// "house" �z����擾���܂��B
				const Json::Value& drawData = root["DrawOption"][0];
				float drawDistance = drawData["DRAW_DISTANCE"][0].asFloat();		//���N�[���^�C��	(s)

				//�������v�Z
				float drawDistanceRatio = (drawDistance - DRAW_MIN_DISTANCE) / (DRAW_MAX_DISTANCE - DRAW_MIN_DISTANCE);
				//bgm�̃Q�[�W��������
				m_drawDistanceGaueg->Initialize(
					DirectX::SimpleMath::Vector2(0, 0),
					DirectX::SimpleMath::Vector2::One,
					tito::ANCHOR::MIDDLE_CENTER,
					tito::POSITION_ANCHOR::MIDDLE_CENTER,
					drawDistanceRatio
				);

				float drawDisance = drawData["DRAW_DITANCE"][0].asFloat();		//���N�[���^�C��	(s)

				//�������v�Z
				float drawDisanceRatio = (drawDisance - DRAW_MIN_DISTANCE) / (DRAW_MAX_DISTANCE - DRAW_MIN_DISTANCE);

				//���ʉ��̃Q�[�W��������
				m_soundEffectGaueg->Initialize(
					DirectX::SimpleMath::Vector2(0, -100),
					DirectX::SimpleMath::Vector2::One,
					tito::ANCHOR::MIDDLE_CENTER,
					tito::POSITION_ANCHOR::MIDDLE_CENTER,
					drawDisanceRatio
				);

			}
		}
		else {
			std::cerr << "JSON�̃p�[�X�G���[: " << errors << std::endl;
		}
		obj.close();
	}
	else {
		std::cerr << "JSON�t�@�C�����J���ۂɃG���[���������܂����B" << std::endl;
	}

	for (int i = 0; i < 2; i++)
	{
		m_Letter[i]->Create(
			L"Resources/Textures/OptionLetter.png",
			DirectX::SimpleMath::Vector2(-130.0f, static_cast<float>(-(i * 100)))
			, DirectX::SimpleMath::Vector2(1, 1)
			, tito::ANCHOR::MIDDLE_RIGHT
			, tito::POSITION_ANCHOR::MIDDLE_CENTER
		);
	}
	m_Letter[0]->LoadTexture(L"Resources/Textures/DrawingDisLetter.png");
	m_Letter[1]->LoadTexture(L"Resources/Textures/EffectDrawingDisLetter.png");

}

// �X�V
void StateDrawOptionScene::Update(const float& elapsedTime)
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();

	if (kbTracker.pressed.Tab)
		m_fsm->RequestTransition(OptionScene::OptionState::OPTION_SCENE);
	auto mouse = KeyboardSingleton::GetInstance()->GetMouseState();

	if (m_fsm->GetOwner()->GetParentFSM()->GetOwner()->GetReturnLetter()->GetMouseFlag())
		if (KeyboardTracker::GetInstance()->Decision())
			m_fsm->RequestTransition(OptionScene::OptionState::OPTION_SCENE);


	m_drawDistanceGaueg->Update();
	m_soundEffectGaueg->Update();


	// JSON�I�u�W�F�N�g���쐬
	Json::Value root;
	// "Gun" �L�[�̔z����쐬
	Json::Value GunArray(Json::arrayValue);
	Json::Value GunElement;

	//�`�拗���͈̔͂���b�㋗�������߂�
	m_drawDistance = DRAW_MIN_DISTANCE +
		(m_drawDistanceGaueg->GetRatio() * (DRAW_MAX_DISTANCE - DRAW_MIN_DISTANCE));
	//���ږ������߂�
	GunElement["DRAW_DISTANCE"] = Json::arrayValue;
	//�����ɏ����o�������l������
	GunElement["DRAW_DISTANCE"].append(m_drawDistance);

	//�`�拗���͈̔͂���b�㋗�������߂�i���j
	int dra = DRAW_MIN_DISTANCE +
		(m_soundEffectGaueg->GetRatio() * (DRAW_MAX_DISTANCE - DRAW_MIN_DISTANCE));
	//���ږ������߂�
	GunElement["DRAW_DITANCE"] = Json::arrayValue;
	//�����ɏ����o�������l������
	GunElement["DRAW_DITANCE"].append(dra);

	//�l�������
	GunArray.append(GunElement);
	// root�I�u�W�F�N�g�� "Gun"��ǉ�
	root["DrawOption"] = GunArray;
	// JSON�f�[�^�𕶎���ɕϊ�
	Json::StreamWriterBuilder writer;
	std::string jsonString = Json::writeString(writer, root);
	// JSON�f�[�^���t�@�C���ɏ����o��
	std::ofstream outputFile(L"Resources/Json/Json_DrawOptionDate.json");
	if (outputFile.is_open())
	{
		outputFile << jsonString;
		outputFile.close();
	}
	Draw::GetInstance()->SetDrawDistance(m_drawDistance * m_drawDistance);
	Draw::GetInstance()->SetFogFar(m_drawDistance);
	Draw::GetInstance()->SetFogNear(m_drawDistance - Draw::FOG_LENGTH);


}

// �`��
void StateDrawOptionScene::Render()
{
	m_drawDistanceGaueg->Render();
	m_soundEffectGaueg->Render();

	for (int i = 0; i < 2; i++)
	{
		m_Letter[i]->Render();
	}
}

// �I������
void StateDrawOptionScene::Finalize()
{
}

void StateDrawOptionScene::Enter()
{
}

void StateDrawOptionScene::Exit()
{
	Draw::GetInstance()->SetDrawDistance(m_drawDistance * m_drawDistance);
	Draw::GetInstance()->SetFogFar(m_drawDistance);
	Draw::GetInstance()->SetFogNear(m_drawDistance - Draw::FOG_LENGTH);
}

void StateDrawOptionScene::CreateDeviceDependentResources()
{
	//BGM�Q�[�W�̃C���X�^���X���擾
	m_drawDistanceGaueg = std::make_unique<VolumeGaueg>();

	//BGM�Q�[�W�̃C���X�^���X���擾
	m_soundEffectGaueg = std::make_unique<VolumeGaueg>();

	for (int i = 0; i < 2; i++)
	{
		m_Letter[i] = std::make_unique<tito::UserInterface>();
	}

}

