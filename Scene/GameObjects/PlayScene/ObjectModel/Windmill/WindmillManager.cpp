#include"pch.h"
#include"WindmillManager.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"

using namespace DirectX;
const int WINDMILL_COUNT(0);

WindmillManager::WindmillManager(): 
	m_mapLoader(nullptr)
{
}

//�R���X�g���N�^�ƌĂ΂��֐�
WindmillManager::~WindmillManager()
{

}

//�Q�[���̏��������s���֐�
void WindmillManager::Intialize()
{
	std::ifstream obj("Resources/json/TwonScene/Json_TwonWindmill.Json");
	Json::CharReaderBuilder reader;
	Json::Value root;

	// �t�@�C�����J����Ă��邩���m�F���܂��B
	if (obj.is_open()) {
		std::string errors;

		// �t�@�C������JSON���p�[�X���܂��B
		if (Json::parseFromStream(reader, obj, &root, &errors))
		{
			// "house" �z����擾���܂��B
			const Json::Value& Array = root["windmill"];

			// "house" �z����̊e�v�f�ɑ΂��ă��[�v�����s���܂��B
			for (const Json::Value& wallData : Array)
			{
				// �V�����I�u�W�F�N�g���쐬���A�ʒu�Ɖ�]��ݒ肵�܂��B
				std::unique_ptr<Windmill> objects = std::make_unique<Windmill>();
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
				m_objectsList.push_back(std::move(objects));
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

	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//����������
		m_objectsList[i]->Initialize();
	}

}

//�Q�[���̍X�V���s���֐�
void WindmillManager::Update()
{
	//���̍X�V
	for (int i = 0; i < m_objectsList.size(); i++)
	{		
		//�I�u�W�F�N�g�̍X�V
		m_objectsList[i]->Update();
	}
}

//�Q�[���̍X�V�������s���֐�
void WindmillManager::Render()
{

	//���̕`��
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//���E�ɓ����Ă��邩
		if (Draw::GetInstance()->VisibilityRange(m_objectsList[i]->GetPosition(), 20))
			continue;

		//�I�u�W�F�N�g�̕`��
		m_objectsList[i]->Render();
	}
}
//�Q�[���̍X�V�������s���֐�
void WindmillManager::RenderShadowTex()
{

	//���̕`��
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//���E�ɓ����Ă��邩
		if (Draw::GetInstance()->DistanceRange(m_objectsList[i]->GetPosition()))
			continue;

		//�I�u�W�F�N�g�̕`��
		m_objectsList[i]->RenderShadowTex();
	}
}

//�Q�[���̏I���������s���֐��B����������K�v�ȏꍇ�@�iRelease�֐��Ȃǂ��Ăяo���j�́A���̊֐����ł���邷��
void WindmillManager::Finalize()
{
	//�㏈��
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		m_objectsList[i].reset();
	}
}

void WindmillManager::CheckHitCharacter(Player* player)
{
	//�v���C���[�Ƃ̓����蔻��
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//��܂��ȃv���C���[�Ƒ�܂��ȓG�̓����蔻��
		if (!m_objectsList[i]->GetRoughCollider()->CheckHitSphere(player->GetCollider()))
			continue;

		//�v���C���[�̃p�[�c�ƓG�̃p�[�c�̓����蔻��
		for (auto& airshipParts : m_objectsList[i]->GetParts())
		{

			//�v���C���[�̃p�[�c�Ƒ�܂��ȓG�̓����蔻��
			if (!airshipParts->CollisionPlayer(player))
				continue;

			player->Damage(player->GetHP());
			return;

		}
	}
}

void WindmillManager::CheckHitEnemy(Enemy* enemy)
{
	//�v���C���[�Ƃ̓����蔻��
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//��܂��ȃv���C���[�Ƒ�܂��ȓG�̓����蔻��
		if (!m_objectsList[i]->GetRoughCollider()->CheckHitSphere(enemy->GetCollider()))
			continue;

		//�v���C���[�̃p�[�c�ƓG�̃p�[�c�̓����蔻��
		for (auto& airshipParts : m_objectsList[i]->GetParts())
		{
			//�������ق��������i�j�p�[�c�Ƒ�g�̃v���C���[�œ����蔻����s��

			//�v���C���[�̃p�[�c�Ƒ�܂��ȓG�̓����蔻��
			if (!airshipParts->CollisionEnemy(enemy))
				continue;

			enemy->Damage(enemy->GetHP());
			return;
		}
	}
}
void WindmillManager::CheckHitAirship(Airship* airship)
{
	//�v���C���[�Ƃ̓����蔻��
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//��܂��ȃv���C���[�Ƒ�܂��ȓG�̓����蔻��
		if (!m_objectsList[i]->GetRoughCollider()->CheckHitSphere(airship->GetCollider()))
			continue;

		//�v���C���[�̃p�[�c�ƓG�̃p�[�c�̓����蔻��
		for (auto& airshipParts : m_objectsList[i]->GetParts())
		{
			//�������ق��������i�j�p�[�c�Ƒ�g�̃v���C���[�œ����蔻����s��
			//���������瓖�������p�[�c��Ԃ��������ĂȂ�������"null"
			IWindmillComponent* HitAirshipPart = airshipParts->Collision(airship);
			if (!HitAirshipPart)
				continue;

			//for (auto& playerParts : player->GetPlayerParts())
			//{
			//	//�v���C���[�̃p�[�c�Ƒ�܂��ȓG�̓����蔻��
			//	if (!playerParts->Collision(HitAirshipPart))
			//		continue;

			airship->Damage(Player::PLAYER_MAX_HP);
			return;
			//}
		}
	}
}
