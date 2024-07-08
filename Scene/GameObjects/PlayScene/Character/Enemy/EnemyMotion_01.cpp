#include "pch.h"
#include"EnemyMotion_01.h"
#include <math.h>
#include<random>
#include"EnemyManager.h"
using namespace DirectX;

#define BULLET_COOL_TIME		(1.0f)		//���N�[���^�C��	(s)
#define ENEMY_MAX_SPEED			(8.0f / 60)	//�O�i�̍ő�X�s�[�h	(m/s)
#define ENEMY_MAX_DISTANCE		(300.0f*300.0f)	//�`��͈�(2��)		(m)



EnemyMotion_01::EnemyMotion_01(Enemy* parent, EnemyManager* enemyManager, Player* player) :
	m_pEnemy(parent),
	m_pEnemyManager(enemyManager),
	m_pPlayer(player)
{

}

EnemyMotion_01::~EnemyMotion_01()
{
}

void EnemyMotion_01::Initialize()
{
	//�G�������Ă��邩
	m_pEnemy->SetSpeed(ENEMY_MAX_SPEED);
	m_pEnemy->SetAngle(DirectX::SimpleMath::Vector3(1,0,0));
	m_pEnemy->GetCollider()->SetRadius(1.3f);
}

void EnemyMotion_01::Update(const float& elapsedTime)
{
	Motion(elapsedTime);

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
	if (m_pEnemy->GetHP() <= 0)
	{
		if (m_pEnemyManager)
			m_pEnemyManager->SetKillCount(m_pEnemyManager->GetKillCount() + 1);
		m_pEnemy->SetIState(m_pEnemy->GetEnemyKillMotion());
	}

}

void EnemyMotion_01::Render()
{
	m_pEnemy->PartsRender();
}

void EnemyMotion_01::Finalize()
{
}


void EnemyMotion_01::Motion(const float& elapsedTime)
{
	elapsedTime;
	SimpleMath::Vector3 position = m_pEnemy->GetPosition();

	SimpleMath::Quaternion q;
	//��s�@�̃A�j���[�V����
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(
		SimpleMath::Vector3::UnitX, 
		XMConvertToRadians(m_pEnemy->GetAngle().y)
	);
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(
		SimpleMath::Vector3::UnitY, 
		XMConvertToRadians(m_pEnemy->GetAngle().x)
	);

	m_pEnemy->SetRotate(m_pEnemy->GetRotate() * q);

	position += SimpleMath::Vector3::Transform(
		SimpleMath::Vector3(0.0f, 0.0f, -m_pEnemy->GetSpeed())
		, m_pEnemy->GetRotate()
	);

	m_pEnemy->SetPosition(position);

	if (m_pEnemy->GetFuel() >= 0)
	{
		m_pEnemy->SetFuel(m_pEnemy->GetFuel() - 1);

		m_pEnemy->PartsMotion();
	}
}
