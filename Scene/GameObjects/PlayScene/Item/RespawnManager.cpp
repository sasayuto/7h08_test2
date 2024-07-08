#include"pch.h"
#include"RespawnManager.h"
#include"Scene/GameObjects/PlayScene//Character/Player/Player.h"

using namespace DirectX;

#define RESPAWN_COUNT			(50)		//���X�|�[���̌�

RespawnManager::RespawnManager() :
	m_RespawnList(),
	m_respawnPosition(SimpleMath::Vector3(000.0f,250.0f,0.0f))
{
	//���ׂẴ��X�|�[���̃C���X�^���X�𐶐�����
	for (int i = 0; i < RESPAWN_COUNT; i++)
	{
		std::unique_ptr<Item> respawnList = std::make_unique<Respawn>();
		m_RespawnList.push_back(std::move(respawnList));
	}
}
//�R���X�g���N�^�ƌĂ΂��֐�
RespawnManager::~RespawnManager()
{

}

//�Q�[���̏��������s���֐�
void RespawnManager::Intialize()
{

	for (int i = 0; i < RESPAWN_COUNT; i++)
	{
		//�͈͓��̃����_���Ȉʒu�ɃZ�b�g
		m_RespawnList[i]->SetpositionRandam(-250,250);

		//����������
		m_RespawnList[i]->Initialize();

	}

}

//�Q�[���̍X�V���s���֐�
void RespawnManager::Update(const float& elapsedTime)
{
	//���̍X�V
	for (int i = 0; i < RESPAWN_COUNT; i++)
	{		
		//���X�|�[���̍X�V
		m_RespawnList[i]->Update(elapsedTime);
	}
}

//�Q�[���̍X�V�������s���֐�
void RespawnManager::Render()
{
	//���̕`��
	for (int i = 0; i < RESPAWN_COUNT; i++)
	{
		//���E�ɓ����Ă��邩
		if (Draw::GetInstance()->VisibilityRange(m_RespawnList[i]->GetPosition()))
			continue;

		m_RespawnList[i]->Render();
	}
}

//�Q�[���̏I���������s���֐��B����������K�v�ȏꍇ�@�iRelease�֐��Ȃǂ��Ăяo���j�́A���̊֐����ł���邷��
void RespawnManager::Finalize()
{
	//�㏈��
	for (int i = 0; i < RESPAWN_COUNT; i++)
	{
		m_RespawnList[i].reset();
	}
}

void RespawnManager::CheckHitCharacter(Player* player)
{
	for (int i = 0; i < RESPAWN_COUNT; i++)
	{
		//�v���C���[�Ƃ̓����蔻��
		if (!m_RespawnList[i]->GetCollider()->CheckHitSphere(player->GetCollider()))
		{
			continue;
		}

		for (auto& playerParts : player->GetParts())
		{
			//�p�[�c�Ƃ̓����蔻��
			if (!playerParts->CollisionItem(m_RespawnList[i].get()))
				continue;

			//���X�|�[���n�_��ێ�����
			m_respawnPosition = m_RespawnList[i]->GetPosition();

			//�g�p�ς݂�
			if (!m_RespawnList[i]->GetSurvival())	continue;

			////�񕜏���
			m_RespawnList[i]->Recovery(player);

			//��[�s�ɂ���
			m_RespawnList[i]->SetSurvival(false);
			
			//�����y���̂��߁i�������Ă�����I���j
			return;
		}
		return;
	}
}
