//--------------------------------------------------------------------------------------
// File: StateSoundOptionScene.cpp
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "StateSoundOptionScene.h"

using namespace DirectX;
StateSoundOptionScene::StateSoundOptionScene(OptionScene::FSM* fsm):
	m_bgmGaueg(nullptr),
	m_soundEffectGaueg(nullptr),
	m_fsm(nullptr)
{
	m_fsm = fsm;
}

StateSoundOptionScene::~StateSoundOptionScene()
{
}

// ������
void StateSoundOptionScene::Initialize()
{
	CreateDeviceDependentResources();
	std::ifstream obj("Resources/json/Json_SoundOptionDate.Json");
	Json::CharReaderBuilder reader;
	Json::Value root;

	// �t�@�C�����J����Ă��邩���m�F���܂��B
	if (obj.is_open()) {
		std::string errors;

		// �t�@�C������JSON���p�[�X���܂��B
		if (Json::parseFromStream(reader, obj, &root, &errors))
		{
			// JSON�� "house" �����݂��A�z��ł��邩�ǂ������m�F���܂��B
			if (root.isMember("SoundOption") && root["SoundOption"].isArray())
			{
				// "house" �z����擾���܂��B
				const Json::Value& drawData = root["SoundOption"][0];
				float SOUND_BGM_VOLUME = drawData["SOUND_BGM_VOLUME"][0].asFloat();		//���N�[���^�C��	(s)

				//bgm�̃Q�[�W��������
				m_bgmGaueg->Initialize(
					DirectX::SimpleMath::Vector2(0, 0),
					DirectX::SimpleMath::Vector2::One,
					tito::ANCHOR::MIDDLE_CENTER,
					tito::POSITION_ANCHOR::MIDDLE_CENTER,
					SOUND_BGM_VOLUME
				);

				float SOUND_EFFECT_VOLUME = drawData["SOUND_EFFECT_VOLUME"][0].asFloat();		//���N�[���^�C��	(s)

				//���ʉ��̃Q�[�W��������
				m_soundEffectGaueg->Initialize(
					DirectX::SimpleMath::Vector2(0, -100),
					DirectX::SimpleMath::Vector2::One,
					tito::ANCHOR::MIDDLE_CENTER,
					tito::POSITION_ANCHOR::MIDDLE_CENTER,
					SOUND_EFFECT_VOLUME
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
	m_Letter[0]->LoadTexture(L"Resources/Textures/BgmSoundLetter.png");
	m_Letter[1]->LoadTexture(L"Resources/Textures/SeSoundLetter.png");

}

// �X�V
void StateSoundOptionScene::Update(const float& elapsedTime)
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
	auto mouse = KeyboardSingleton::GetInstance()->GetMouseState();

	if (kbTracker.pressed.Tab)
		m_fsm->RequestTransition(OptionScene::OptionState::OPTION_SCENE);


	if (m_fsm->GetOwner()->GetParentFSM()->GetOwner()->GetReturnLetter()->GetMouseFlag())
		if (KeyboardTracker::GetInstance()->Decision())
			m_fsm->RequestTransition(OptionScene::OptionState::OPTION_SCENE);

	m_bgmGaueg->Update();
	m_soundEffectGaueg->Update();


	// JSON�I�u�W�F�N�g���쐬
	Json::Value root;
	// "Gun" �L�[�̔z����쐬
	Json::Value GunArray(Json::arrayValue);
	Json::Value GunElement;

	//���ږ������߂�
	GunElement["SOUND_BGM_VOLUME"] = Json::arrayValue;
	//�����ɏ����o�������l������
	GunElement["SOUND_BGM_VOLUME"].append(m_bgmGaueg->GetRatio());

	//���ږ������߂�
	GunElement["SOUND_EFFECT_VOLUME"] = Json::arrayValue;
	//�����ɏ����o�������l������
	GunElement["SOUND_EFFECT_VOLUME"].append(m_soundEffectGaueg->GetRatio());

	//�l�������
	GunArray.append(GunElement);
	// root�I�u�W�F�N�g�� "Gun"��ǉ�
	root["SoundOption"] = GunArray;
	// JSON�f�[�^�𕶎���ɕϊ�
	Json::StreamWriterBuilder writer;
	std::string jsonString = Json::writeString(writer, root);
	// JSON�f�[�^���t�@�C���ɏ����o��
	std::ofstream outputFile(L"Resources/Json/Json_SoundOptionDate.json");
	if (outputFile.is_open())
	{
		outputFile << jsonString;
		outputFile.close();
	}

}

// �`��
void StateSoundOptionScene::Render()
{
	m_bgmGaueg->Render();
	m_soundEffectGaueg->Render();
	for (int i = 0; i < 2; i++)
	{
		m_Letter[i]->Render();
	}


}

// �I������
void StateSoundOptionScene::Finalize()
{
}

void StateSoundOptionScene::Enter()
{
}

void StateSoundOptionScene::Exit()
{
}

void StateSoundOptionScene::CreateDeviceDependentResources()
{
	//BGM�Q�[�W�̃C���X�^���X���擾
	m_bgmGaueg = std::make_unique<VolumeGaueg>();

	//BGM�Q�[�W�̃C���X�^���X���擾
	m_soundEffectGaueg = std::make_unique<VolumeGaueg>();

	for (int i = 0; i < 2; i++)
	{
		m_Letter[i] = std::make_unique<tito::UserInterface>();
	}

}

