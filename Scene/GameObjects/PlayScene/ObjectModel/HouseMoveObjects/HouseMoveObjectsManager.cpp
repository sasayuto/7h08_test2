#include"pch.h"
#include"HouseMoveObjectsManager.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/Effect/SandstormEffect.h"

using namespace DirectX;
const int WINDMILL_COUNT(100);

HouseMoveObjectsManager::HouseMoveObjectsManager():
	m_benchKillCount(0),
	m_HouseMoveObjectsManager{},
	m_pBulletManager(nullptr)
{
}

//�R���X�g���N�^�ƌĂ΂��֐�
HouseMoveObjectsManager::~HouseMoveObjectsManager()
{
}
//�Q�[���̍X�V���s���֐�
void HouseMoveObjectsManager::Update(const float& elapsedTime)
{
	//m_HouseMoveObjectsManager.clear();
	//Intialize(m_pBulletManager);
	//���̍X�V
	for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
	{		
		//����ł�����X�V���Ȃ�
		if (!m_HouseMoveObjectsManager[i]->GetSurvival())
			continue;

		//�I�u�W�F�N�g�̍X�V
		m_HouseMoveObjectsManager[i]->Update(elapsedTime);
	}
}

//�Q�[���̍X�V�������s���֐�
void HouseMoveObjectsManager::Render()
{

	//���̕`��
	for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
	{
		//����ł�����X�V���Ȃ�
		if (!m_HouseMoveObjectsManager[i]->GetSurvival())
			continue;

		//�I�u�W�F�N�g�̕`��
		m_HouseMoveObjectsManager[i]->Render();
	}
}
//�Q�[���̍X�V�������s���֐�
void HouseMoveObjectsManager::RenderShadowTex(const bool dynamicflag)
{

	//���̕`��
	for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
	{		
		//����ł�����X�V���Ȃ�
		if (m_HouseMoveObjectsManager[i]->GetAllSurvivalFlag() == dynamicflag)
			continue;

		//����ł�����X�V���Ȃ�
		if (!m_HouseMoveObjectsManager[i]->GetSurvival())
			continue;

		//���E�ɓ����Ă��邩
		if (Draw::GetInstance()->DistanceRange(m_HouseMoveObjectsManager[i]->GetPosition()))
			continue;

		//�I�u�W�F�N�g�̕`��
		m_HouseMoveObjectsManager[i]->RenderShadowTex();
	}
}

//�Q�[���̏I���������s���֐��B����������K�v�ȏꍇ�@�iRelease�֐��Ȃǂ��Ăяo���j�́A���̊֐����ł���邷��
void HouseMoveObjectsManager::Finalize()
{
	//�㏈��
	for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
	{
		m_HouseMoveObjectsManager[i].reset();
	}
}

void HouseMoveObjectsManager::CheckHitCharacter(Player* player)
{
	////�v���C���[�Ƃ̓����蔻��
	for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
	{
		//����ł�����X�V���Ȃ�
		if (!m_HouseMoveObjectsManager[i]->GetSurvival())
			continue;

		//��܂��ȃv���C���[�Ƒ�܂��ȓG�̓����蔻��
		if (!m_HouseMoveObjectsManager[i]->GetRoughCollider()->CheckHitSphere(player->GetCollider()))
			continue;

		//�v���C���[�̃p�[�c�ƓG�̃p�[�c�̓����蔻��
		for (auto& airshipParts : m_HouseMoveObjectsManager[i]->GetParts())
		{
			//�������ق��������i�j�p�[�c�Ƒ�g�̃v���C���[�œ����蔻����s��
			//���������瓖�������p�[�c��Ԃ��������ĂȂ�������"null"
			if (!airshipParts->CollisionPlayer(player))
				continue;

			player->Damage(player->GetHP());

			m_HouseMoveObjectsManager[i]->GetRoughCollider()->SetRadius(
				m_HouseMoveObjectsManager[i]->GetRoughCollider()->GetRadius() * 5.0f
			);

		}
	}
}

void HouseMoveObjectsManager::CheckHitEnemy(Enemy* enemy)
{
	////�v���C���[�Ƃ̓����蔻��
	for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
	{
		//����ł�����X�V���Ȃ�
		if (!m_HouseMoveObjectsManager[i]->GetSurvival())
			continue;

		//��܂��ȃv���C���[�Ƒ�܂��ȓG�̓����蔻��
		if (!m_HouseMoveObjectsManager[i]->GetRoughCollider()->CheckHitSphere(enemy->GetCollider()))
			continue;

		//�v���C���[�̃p�[�c�ƓG�̃p�[�c�̓����蔻��
		for (auto& airshipParts : m_HouseMoveObjectsManager[i]->GetParts())
		{
			//�������ق��������i�j�p�[�c�Ƒ�g�̃v���C���[�œ����蔻����s��
			//���������瓖�������p�[�c��Ԃ��������ĂȂ�������"null"
			if (!airshipParts->Collision(enemy))
				continue;

			enemy->Damage(enemy->GetHP());

			m_HouseMoveObjectsManager[i]->GetRoughCollider()->SetRadius(
				m_HouseMoveObjectsManager[i]->GetRoughCollider()->GetRadius() * 5.0f
			);

		}
	}
}
void HouseMoveObjectsManager::CheckHitAirship(Airship* airship)
{
	airship;
	////�v���C���[�Ƃ̓����蔻��
	//for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
	//{
	// 
	//	//��܂��ȃv���C���[�Ƒ�܂��ȓG�̓����蔻��
	//	if (!m_HouseMoveObjectsManager[i]->GetRoughCollider()->CheckHitSphere(airship->GetCollider()))
	//		continue;

	//	//�v���C���[�̃p�[�c�ƓG�̃p�[�c�̓����蔻��
	//	for (auto& airshipParts : m_HouseMoveObjectsManager[i]->GetParts())
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

void HouseMoveObjectsManager::CheckHitSandstorm(SandstormEffect* sandstormEffect)
{
	////�v���C���[�Ƃ̓����蔻��
	for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
	{
		//����ł�����X�V���Ȃ�
		if (!m_HouseMoveObjectsManager[i]->GetSurvival())
			continue;

		//��܂��ȃv���C���[�Ƒ�܂��ȓG�̓����蔻��
		if (!m_HouseMoveObjectsManager[i]->GetRoughCollider()->CheckHitSphereBox(sandstormEffect->GetCollider()))
			continue;

		//�v���C���[�̃p�[�c�ƓG�̃p�[�c�̓����蔻��
		for (auto& airshipParts : m_HouseMoveObjectsManager[i]->GetParts())
		{
			//�������ق��������i�j�p�[�c�Ƒ�g�̃v���C���[�œ����蔻����s��
			//���������瓖�������p�[�c��Ԃ��������ĂȂ�������"null"
			if (!airshipParts->CollisionSandstorm(sandstormEffect))
			continue;

			//�p�[�c���Ƃł΂炯��̂Őe�̓����蔻���傫������
			m_HouseMoveObjectsManager[i]->GetRoughCollider()->SetRadius(
				m_HouseMoveObjectsManager[i]->GetRoughCollider()->GetRadius() * 5.0f
			);
		}
	}

}
