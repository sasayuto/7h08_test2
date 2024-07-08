#include"pch.h"
#include"MoveObjectsManager.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/Effect/SandstormEffect.h"

using namespace DirectX;
const int WINDMILL_COUNT(100);

MoveObjectsManager::MoveObjectsManager():
	m_benchKillCount(0),
	m_MoveObjectsManager{},
	m_pBulletManager(nullptr)
{
}

//�R���X�g���N�^�ƌĂ΂��֐�
MoveObjectsManager::~MoveObjectsManager()
{

}

//�Q�[���̏��������s���֐�
void MoveObjectsManager::Intialize(BulletManager* bulletManager)
{
	m_pBulletManager = bulletManager;

	for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	{
		//����������
		m_MoveObjectsManager[i]->Initialize(bulletManager,this);
	}

}

//�Q�[���̍X�V���s���֐�
void MoveObjectsManager::Update(const float& elapsedTime)
{
	//m_MoveObjectsManager.clear();
	//Intialize(m_pBulletManager);
	//���̍X�V
	for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	{		
		//����ł�����X�V���Ȃ�
		if (!m_MoveObjectsManager[i]->GetSurvival())
			continue;

		//�I�u�W�F�N�g�̍X�V
		m_MoveObjectsManager[i]->Update(elapsedTime);
	}
}

//�Q�[���̍X�V�������s���֐�
void MoveObjectsManager::Render()
{

	//���̕`��
	for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	{
		//����ł�����X�V���Ȃ�
		if (!m_MoveObjectsManager[i]->GetSurvival())
			continue;

		//�I�u�W�F�N�g�̕`��
		m_MoveObjectsManager[i]->Render();
	}
}
//�Q�[���̍X�V�������s���֐�
void MoveObjectsManager::RenderShadowTex(const bool dynamicflag)
{

	//���̕`��
	for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	{		
		//����ł�����X�V���Ȃ�
		if (m_MoveObjectsManager[i]->GetAllSurvivalFlag() == dynamicflag)
			continue;

		//����ł�����X�V���Ȃ�
		if (!m_MoveObjectsManager[i]->GetSurvival())
			continue;

		//���E�ɓ����Ă��邩
		if (Draw::GetInstance()->DistanceRange(m_MoveObjectsManager[i]->GetPosition()))
			continue;

		//�I�u�W�F�N�g�̕`��
		m_MoveObjectsManager[i]->RenderShadowTex();
	}
}

//�Q�[���̏I���������s���֐��B����������K�v�ȏꍇ�@�iRelease�֐��Ȃǂ��Ăяo���j�́A���̊֐����ł���邷��
void MoveObjectsManager::Finalize()
{
	//�㏈��
	for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	{
		m_MoveObjectsManager[i].reset();
	}
}

void MoveObjectsManager::CheckHitCharacter(Player* player)
{
	////�v���C���[�Ƃ̓����蔻��
	for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	{
		//����ł�����X�V���Ȃ�
		if (!m_MoveObjectsManager[i]->GetSurvival())
			continue;

		//��܂��ȃv���C���[�Ƒ�܂��ȓG�̓����蔻��
		if (!m_MoveObjectsManager[i]->GetRoughCollider()->CheckHitSphere(player->GetCollider()))
			continue;

		//�v���C���[�̃p�[�c�ƓG�̃p�[�c�̓����蔻��
		for (auto& airshipParts : m_MoveObjectsManager[i]->GetParts())
		{
			//�������ق��������i�j�p�[�c�Ƒ�g�̃v���C���[�œ����蔻����s��
			//���������瓖�������p�[�c��Ԃ��������ĂȂ�������"null"
			if (!airshipParts->CollisionPlayer(player))
				continue;

			m_MoveObjectsManager[i]->GetRoughCollider()->SetRadius(
				m_MoveObjectsManager[i]->GetRoughCollider()->GetRadius() * 5.0f
			);

		}
	}
}

void MoveObjectsManager::CheckHitEnemy(Enemy* enemy)
{
	////�v���C���[�Ƃ̓����蔻��
	for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	{
		//����ł�����X�V���Ȃ�
		if (!m_MoveObjectsManager[i]->GetSurvival())
			continue;

		//��܂��ȃv���C���[�Ƒ�܂��ȓG�̓����蔻��
		if (!m_MoveObjectsManager[i]->GetRoughCollider()->CheckHitSphere(enemy->GetCollider()))
			continue;

		//�v���C���[�̃p�[�c�ƓG�̃p�[�c�̓����蔻��
		for (auto& airshipParts : m_MoveObjectsManager[i]->GetParts())
		{
			//�������ق��������i�j�p�[�c�Ƒ�g�̃v���C���[�œ����蔻����s��
			//���������瓖�������p�[�c��Ԃ��������ĂȂ�������"null"
			//if (!airshipParts->CollisionPlayer(enemy))
				continue;

				m_MoveObjectsManager[i]->GetRoughCollider()->SetRadius(
					m_MoveObjectsManager[i]->GetRoughCollider()->GetRadius() * 5.0f
				);

		}
	}
}
void MoveObjectsManager::CheckHitAirship(Airship* airship)
{
	////�v���C���[�Ƃ̓����蔻��
	//for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	//{
	// 
	//	//��܂��ȃv���C���[�Ƒ�܂��ȓG�̓����蔻��
	//	if (!m_MoveObjectsManager[i]->GetRoughCollider()->CheckHitSphere(airship->GetCollider()))
	//		continue;

	//	//�v���C���[�̃p�[�c�ƓG�̃p�[�c�̓����蔻��
	//	for (auto& airshipParts : m_MoveObjectsManager[i]->GetParts())
	//	{
	//		//�������ق��������i�j�p�[�c�Ƒ�g�̃v���C���[�œ����蔻����s��
	//		//���������瓖�������p�[�c��Ԃ��������ĂȂ�������"null"
	//		IWindmillComponent* HitAirshipPart = airshipParts->Collision(airship);
	//		if (!HitAirshipPart)
	//			continue;

	//		//for (auto& playerParts : player->GetPlayerParts())
	//		//{
	//		//	//�v���C���[�̃p�[�c�Ƒ�܂��ȓG�̓����蔻��
	//		//	if (!playerParts->Collision(HitAirshipPart))
	//		//		continue;

	//		airship->Damage(Player::PLAYER_MAX_HP);
	//		return;
	//		//}
	//	}
	//}
}

void MoveObjectsManager::CheckHitSandstorm(SandstormEffect* sandstormEffect)
{
	////�v���C���[�Ƃ̓����蔻��
	for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	{
		//����ł�����X�V���Ȃ�
		if (!m_MoveObjectsManager[i]->GetSurvival())
			continue;

		//��܂��ȃv���C���[�Ƒ�܂��ȓG�̓����蔻��
		if (!m_MoveObjectsManager[i]->GetRoughCollider()->CheckHitSphereBox(sandstormEffect->GetCollider()))
			continue;

		//�v���C���[�̃p�[�c�ƓG�̃p�[�c�̓����蔻��
		for (auto& airshipParts : m_MoveObjectsManager[i]->GetParts())
		{
			//�������ق��������i�j�p�[�c�Ƒ�g�̃v���C���[�œ����蔻����s��
			//���������瓖�������p�[�c��Ԃ��������ĂȂ�������"null"
			if (!airshipParts->CollisionSandstorm(sandstormEffect))
			continue;

			//�p�[�c���Ƃł΂炯��̂Őe�̓����蔻���傫������
			m_MoveObjectsManager[i]->GetRoughCollider()->SetRadius(
				m_MoveObjectsManager[i]->GetRoughCollider()->GetRadius() * 5.0f
			);
		}
	}

}
