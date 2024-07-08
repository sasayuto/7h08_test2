#include "pch.h"
#include"EnemyMotion.h"
#include <math.h>
#include<random>
#include"EnemyManager.h"
using namespace DirectX;

#define BULLET_COOL_TIME		(1.0f)		//���N�[���^�C��	(s)
#define ENEMY_MAX_SPEED			(8.0f / 60)	//�O�i�̍ő�X�s�[�h	(m/s)
#define ENEMY_MAX_DISTANCE		(300.0f*300.0f)	//�`��͈�(2��)		(m)



EnemyMotion::EnemyMotion(Enemy* parent, EnemyManager* enemyManager, Player* player) :
	m_pEnemy(parent),
	m_pEnemyManager(enemyManager),
	m_pPlayer(player)
{

}

EnemyMotion::~EnemyMotion()
{
}

void EnemyMotion::Initialize()
{
	//�G�������Ă��邩
	m_pEnemy->SetSurvival(true);
	m_pEnemy->SetSpeed(ENEMY_MAX_SPEED);
	m_pEnemy->GetCollider()->SetRadius(1.3f);
}

void EnemyMotion::Update(const float& elapsedTime)
{
	Motion();

	//����
	float bulletCoolTime = m_pEnemy->GetBulletCoolTime();
	//���̃N�[���^�C��
	if (bulletCoolTime > 0.0f)
		bulletCoolTime -= elapsedTime;
	else
		bulletCoolTime = 0.0f;

	m_pEnemy->SetBulletCoolTime(bulletCoolTime);

	m_pEnemy->Shot(BULLET_COOL_TIME);

	//�p�[�c�̍X�V
	m_pEnemy->PartsUpdate();

	//HP���O�ɂȂ�����
	if (m_pEnemy->GetHP() <= 0)
	{
		//�L�����J�E���g
		m_pEnemyManager->SetKillCount(m_pEnemyManager->GetKillCount() + 1);
		
		//�L���̏�Ԃ�
		m_pEnemy->SetIState(m_pEnemy->GetEnemyKillMotion());
	}

}

void EnemyMotion::Render()
{
	m_pEnemy->PartsRender();
}

void EnemyMotion::Finalize()
{
}


void EnemyMotion::Motion()
{
	SimpleMath::Vector3 enemyPosition = m_pEnemy->GetPosition();
	SimpleMath::Vector3 enemyAngle = m_pEnemy->GetAngle();
	SimpleMath::Vector3 distance = m_pEnemy->GetPosition() - m_pPlayer->GetPosition();

	//�f�X�|�[������
	if (distance.LengthSquared() >= ENEMY_MAX_DISTANCE)
	{
		m_pEnemy->SetSurvival(false);
		return;
	}

	//�v���C���[�̐������Ă���ǔ�
	if (m_pPlayer->GetSurvival())
	{
		//�v���C���[�|�W�V��������p�x�����߂�
		enemyAngle.y = static_cast<float>(atan2(distance.y, distance.z));
		enemyAngle.x = static_cast<float>(atan2(distance.x, distance.z));

		//Y�����O�x����P�W�O�x�̉�]�ɕύX����
		if ((-1.57f <= enemyAngle.y && enemyAngle.y < 0) || (1.57f >= enemyAngle.y && enemyAngle.y > 0))
		{
			enemyAngle.y *= -1;			//�t��]�ɂ���
			enemyAngle.y += XMConvertToRadians(180.0f);		//�P�W�O�x��
		}
	}

	SimpleMath::Quaternion q;
	//��s�@�̃A�j���[�V����
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, enemyAngle.y + XMConvertToRadians(180.0f));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, enemyAngle.x);

	m_pEnemy->SetRotate(q);
	m_pEnemy->SetPosition(
		m_pEnemy->GetPosition() + 
		SimpleMath::Vector3::Transform(
			SimpleMath::Vector3(
			0.0f, 
			0.0f, 
			-m_pEnemy->GetSpeed()
			), 
			m_pEnemy->GetRotate()
		)
	);

	//�R�����؂ꂽ��
	if (m_pEnemy->GetFuel() >= 0)
	{
		m_pEnemy->SetFuel(m_pEnemy->GetFuel() - 1);

		m_pEnemy->PartsMotion();
	}

	//�A���O�����Z�b�g
	m_pEnemy->SetAngle(enemyAngle);

}
