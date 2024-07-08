#include"pch.h"
#include"SupplyPointManager.h"
#include"Scene/GameObjects/PlayScene//Character/Player/Player.h"

using namespace DirectX;

//int�^�����́A�錾�Ɠ����ɐ��l�ݒ肪�\
#define  SUPPLYPOINT_HP_COUNT					(20)		//HP�񕜂̌�
#define  SUPPLYPOINT_FUEl_COUNT					(20)		//�R���񕜂̌�

//����
#define  SUPPLYPOINT_COUNT		(SUPPLYPOINT_HP_COUNT + SUPPLYPOINT_FUEl_COUNT+COIN_COUNT);

SupplyPointManager::SupplyPointManager():
	m_itemGetCount(0)
{

}

SupplyPointManager::~SupplyPointManager()
{

}

void SupplyPointManager::Intialize(std::string failName)
{
	std::ifstream obj(failName);

	Json::CharReaderBuilder reader;

	Json::Value root;
	//�t�@�C�����J��
	if (obj.is_open())
	{
		std::string errors;
		//
		if (Json::parseFromStream(reader, obj, &root, &errors))
		{
			const Json::Value& wallsArray = root["Heat"];
			for (const Json::Value& wallDate : wallsArray)
			{
				//float����Vector3�ɕϊ�
				std::unique_ptr<Item> windmill = std::make_unique<HpSupplyPoint>();
				windmill->SetPosition(
					SimpleMath::Vector3(wallDate["position"][0].asFloat(),
						wallDate["position"][1].asFloat(),
						wallDate["position"][2].asFloat()
					));
				windmill->SetRotate(DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
					DirectX::XMConvertToRadians(wallDate["rotate"][0].asFloat()),
					DirectX::XMConvertToRadians(wallDate["rotate"][1].asFloat()),
					DirectX::XMConvertToRadians(wallDate["rotate"][2].asFloat())
				));
				m_supplyPointList.push_back(std::move(windmill));
			}
			for (const Json::Value& wallDate : root["Fuel"])
			{
				//float����Vector3�ɕϊ�
				std::unique_ptr<Item> windmill = std::make_unique<FuelSupplyPoint>();
				windmill->SetPosition(
					SimpleMath::Vector3(wallDate["position"][0].asFloat(),
						wallDate["position"][1].asFloat(),
						wallDate["position"][2].asFloat()
					));
				windmill->SetRotate(DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
					DirectX::XMConvertToRadians(wallDate["rotate"][0].asFloat()),
					DirectX::XMConvertToRadians(wallDate["rotate"][1].asFloat()),
					DirectX::XMConvertToRadians(wallDate["rotate"][2].asFloat())
				));
				m_supplyPointList.push_back(std::move(windmill));
			}
		}
		else
		{
			std::cerr << "a" << errors << std::endl;
		}
		obj.close();
	}
	else
	{
		std::cerr << "Error opening JSON obj:" << std::endl;
	}


	//���ׂẴA�C�e���𖢎g�p��Ԃɂ���
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{
		m_supplyPointList[i]->Initialize();
	}

}

void SupplyPointManager::Update(const float& elapsedTime)
{
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{
		//�G�������Ă��邩
		if (!m_supplyPointList[i]->GetSurvival())		continue;

		//�A�C�e���̍X�V
		m_supplyPointList[i]->Update(elapsedTime);
	}

}

//�Q�[���̍X�V�������s���֐�
void SupplyPointManager::Render()
{
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{
		//�G�������Ă��邩
		if (!m_supplyPointList[i]->GetSurvival())		continue;

		//���E�ɓ����Ă��邩
		if (Draw::GetInstance()->VisibilityRange(m_supplyPointList[i]->GetPosition()))
			continue;

		//�A�C�e���̍X�V
		m_supplyPointList[i]->Render();
	}
}

void SupplyPointManager::RenderShadowTex()
{
	//���̕`��
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{
		//�G�������Ă��邩
		if (!m_supplyPointList[i]->GetSurvival())		continue;
		//���E�ɓ����Ă��邩
		if (Draw::GetInstance()->DistanceRange(m_supplyPointList[i]->GetPosition()))
			continue;

		//�I�u�W�F�N�g�̕`��
		m_supplyPointList[i]->RenderShadowTex();
	}
}

void SupplyPointManager::Finalize()
{
	//�㏈��
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{		
		m_supplyPointList[i].reset();
	}
}

void SupplyPointManager::CheckHitCharacter(Player* player)
{
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{		
		//�G�������Ă��邩
		if (!m_supplyPointList[i]->GetSurvival())	
			continue;

		//�v���C���[�̓����蔻��
		if (!m_supplyPointList[i]->GetCollider()->CheckHitSphere(player->GetCollider()))
			continue;

		for (auto& playerParts : player->GetParts())
		{
			//�p�[�c�Ƃ̓����蔻��
			if (!playerParts->CollisionItem(m_supplyPointList[i].get()))
				continue;

			//�񕜏���
			m_supplyPointList[i]->Recovery(player);

			//��[�s�ɂ���
			m_supplyPointList[i]->SetSurvival(false);

			m_itemGetCount++;
			//�����y���̂��߁i�������Ă�����I���j
			return;
		}
		return;
	}
}
