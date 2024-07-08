#include"pch.h"
#include"FloorManager_01.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"../MinStoneFloor/MinStoneFloor.h"
using namespace DirectX;


FloorManager_01::FloorManager_01() 
{	
}

//�R���X�g���N�^�ƌĂ΂��֐�
FloorManager_01::~FloorManager_01()
{

}

//�Q�[���̏��������s���֐�
void FloorManager_01::Intialize()
{
	std::ifstream obj("Resources/json/TwonScene/Json_TwonFloor.Json");
	Json::CharReaderBuilder reader;
	Json::Value root;

	// �t�@�C�����J����Ă��邩���m�F���܂��B
	if (obj.is_open()) {
		std::string errors;

		// �t�@�C������JSON���p�[�X���܂��B
		if (Json::parseFromStream(reader, obj, &root, &errors)) 
		{
			// JSON�� "house" �����݂��A�z��ł��邩�ǂ������m�F���܂��B
			if (root.isMember("floor") && root["floor"].isArray())
			{
				// "house" �z����擾���܂��B
				const Json::Value& Array = root["floor"][0]["minStoneFloor"];

				// "house" �z����̊e�v�f�ɑ΂��ă��[�v�����s���܂��B
				for (const Json::Value& wallData : Array)
				{
					// �V�����I�u�W�F�N�g���쐬���A�ʒu�Ɖ�]��ݒ肵�܂��B
					std::unique_ptr<Floor> objects = std::make_unique<MinStoneFloor>();
					objects->SetPosition(SimpleMath::Vector3(
						wallData["position"][0].asFloat(),
						wallData["position"][1].asFloat(),
						wallData["position"][2].asFloat()
					));
					objects->SetRotate(DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
						DirectX::XMConvertToRadians(wallData["rotate"][0].asFloat()),
						DirectX::XMConvertToRadians(wallData["rotate"][1].asFloat()),
						DirectX::XMConvertToRadians(wallData["rotate"][2].asFloat())
					));

					// ���X�g�ɃI�u�W�F�N�g��ǉ����܂��B
					m_floorsList.push_back(std::move(objects));
				}

			}
			else {
				std::cerr << "JSON�� 'house' �f�[�^���܂܂�Ă��܂���B" << std::endl;
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

	// �I�u�W�F�N�g�����������܂��B
	for (int i = 0; i < m_floorsList.size(); i++) {
		m_floorsList[i]->Initialize();
	}
}

//�Q�[���̍X�V���s���֐�
void FloorManager_01::Update()
{
	//���̍X�V
	for (int i = 0; i < m_floorsList.size(); i++)
	{		
		//�I�u�W�F�N�g�̍X�V
		m_floorsList[i]->Update();
	}
}

//�Q�[���̍X�V�������s���֐�
void FloorManager_01::Render()
{
	//���̕`��
	for (int i = 0; i < m_floorsList.size(); i++)
	{
		//�I�u�W�F�N�g�̕`��
		m_floorsList[i]->Render();
	}
}

//�Q�[���̏I���������s���֐��B����������K�v�ȏꍇ�@�iRelease�֐��Ȃǂ��Ăяo���j�́A���̊֐����ł���邷��
void FloorManager_01::Finalize()
{
	//�㏈��
	for (int i = 0; i < m_floorsList.size(); i++)
	{
		m_floorsList[i].reset();
	}
}

void FloorManager_01::CheckHitCharacter(Player* player)
{
	for (int i = 0; i < m_floorsList.size(); i++)
	{
		//�v���C���[�Ƃ̓����蔻��
		if (!m_floorsList[i]->GetCollider()->CheckHitSphere(player->GetCollider()))
			continue;

		for (auto& playerParts : player->GetParts())
		{
			//�p�[�c�Ƃ̓����蔻��
			if (!playerParts->CollisionFloor(m_floorsList[i].get()))
				continue;

			player->Damage(player->GetHP());
			//�����y���̂��߁i�������Ă�����I���j
		}
	}
}

void FloorManager_01::CheckHitEnemy(Enemy* enemy)
{
	for (int i = 0; i < m_floorsList.size(); i++)
	{
		//�v���C���[�Ƃ̓����蔻��
		if (!m_floorsList[i]->GetCollider()->CheckHitSphere(enemy->GetCollider()))
			continue;

		for (auto& playerParts : enemy->GetParts())
		{
			//�p�[�c�Ƃ̓����蔻��
			if (!playerParts->CollisionFloor(m_floorsList[i].get()))
				continue;

			enemy->Damage(enemy->GetHP());
			//�����y���̂��߁i�������Ă�����I���j
		}
	}

}

