#include"pch.h"
#include"CoinManager.h"
#include"Scene/GameObjects/PlayScene//Character/Player/Player.h"

using namespace DirectX;

//int�^�����́A�錾�Ɠ����ɐ��l�ݒ肪�\
#define  COIN_CLEAR_COUNT			(100)		//�N���A�ɕK�v�ȃR�C���̌�
#define  COIN_COUNT			(50)		//�N���A�ɕK�v�ȃR�C���̌�

CoinManager::CoinManager():
	m_coinCount(0),
	m_supplyPointList(),
	m_sceneFlag(false)
{
}

CoinManager::~CoinManager()
{
}

void CoinManager::Intialize(std::string failName)
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
			const Json::Value& wallsArray = root["coin"];
			for (const Json::Value& wallDate : wallsArray)
			{
				//float����Vector3�ɕϊ�
				std::unique_ptr<Item> windmill = std::make_unique<Coin>();
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
	for (int i = 0; i < COIN_COUNT; i++)
	{
		std::unique_ptr<Item> respawnList = std::make_unique<Coin>();
		respawnList->SetpositionRandam(-300, 300);
		m_supplyPointList.push_back(std::move(respawnList));
	}

	//���ׂẴA�C�e���𖢎g�p��Ԃɂ���
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{
		m_supplyPointList[i]->Initialize();
	}
}

void CoinManager::Update(const float& elapsedTime)
{
	//m_supplyPointList.clear();
	//Intialize();
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{
		//�G�������Ă��邩
		if (!m_supplyPointList[i]->GetSurvival())		continue;

		//���E�ɓ����Ă��邩
		if (Draw::GetInstance()->VisibilityRange(m_supplyPointList[i]->GetPosition()))
			continue;

		//�A�C�e���̍X�V
		m_supplyPointList[i]->Update(elapsedTime);
	}

	//�N���A����
	if (m_coinCount == COIN_CLEAR_COUNT)
	{
		m_sceneFlag = true;
	}
}

//�Q�[���̍X�V�������s���֐�
void CoinManager::Render()
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
void CoinManager::RenderShadowTex()
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

void CoinManager::Finalize()
{
	//�㏈��
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{		
		m_supplyPointList[i].reset();
	}
}

void CoinManager::CheckHitCharacter(Player* player)
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

			m_coinCount++;
			//�A�C�e���𖢎g�p�ɂ���
			m_supplyPointList[i]->SetSurvival(false);
			return;
		}
		return;
	}
}
