#include "pch.h"
#include"AirshipMotion.h"
#include <math.h>
#include<random>
using namespace DirectX;

#define BULLET_COOL_TIME		(1.0f)		//���N�[���^�C��	(s)
#define ENEMY_MAX_SPEED			(8.0f / 60)	//�O�i�̍ő�X�s�[�h	(m/s)
#define ENEMY_MAX_DISTANCE		(300.0f*300.0f)	//�`��͈�(2��)		(m)



AirshipMotion::AirshipMotion(Airship* parent, Player* player) :
	m_pAirship(parent),
	m_pPlayer(player)
{

}

AirshipMotion::~AirshipMotion()
{
}

void AirshipMotion::Initialize()
{
	//�G�������Ă��邩
	m_pAirship->Reset();
	m_pAirship->SetSurvival(true);
	m_pAirship->SetSpeed(ENEMY_MAX_SPEED);
}

void AirshipMotion::Update(const float& elapsedTime)
{
	Motion();

	//����
	float bulletCoolTime = m_pAirship->GetBulletCoolTime();
	//���̃N�[���^�C��
	if (bulletCoolTime > 0.0f)
		bulletCoolTime -= elapsedTime;
	else
		bulletCoolTime = 0.0f;

	m_pAirship->SetBulletCoolTime(bulletCoolTime);

	m_pAirship->Shot(BULLET_COOL_TIME);

	//�p�[�c�̍X�V
	m_pAirship->PartsUpdate();

	////HP���O�ɂȂ�����
	//if (m_pAirship->GetHP() <= 0)
	//{
	//	
	//	//�L���̏�Ԃ�
	//	m_pAirship->SetIState(m_pAirship->GetEnemyKillMotion());
	//}

}

void AirshipMotion::Render()
{
	m_pAirship->PartsRender();
}

void AirshipMotion::Finalize()
{
}


void AirshipMotion::Motion()
{
	SimpleMath::Vector3 enemyPosition = m_pAirship->GetPosition();
	SimpleMath::Vector3 enemyAngle = m_pAirship->GetAngle();
	SimpleMath::Vector3 distance = m_pAirship->GetPosition() - m_pPlayer->GetPosition();

	//�f�X�|�[������
	if (distance.LengthSquared() >= ENEMY_MAX_DISTANCE)
	{
		m_pAirship->SetSurvival(false);
		return;
	}

	//�v���C���[��HP���Ȃ��Ȃ�����ǔ����Ȃ�
	if (m_pPlayer->GetHP() > 0)
	{
		//�v���C���[�|�W�V��������p�x�����߂�
		enemyAngle.y = static_cast<float>(atan2(distance.y, distance.z));
		enemyAngle.x = static_cast<float>(atan2(distance.x, distance.z));
	}
	//Y�����O�x����P�W�O�x�̉�]�ɕύX����
	if (( - 1.57f <= enemyAngle.y && enemyAngle.y < 0)|| (1.57f >= enemyAngle.y && enemyAngle.y > 0))
	{
		enemyAngle.y *= -1;			//�t��]�ɂ���
		enemyAngle.y += XMConvertToRadians(180.0f);		//�P�W�O�x��
	}

	SimpleMath::Quaternion q;
	//��s�@�̃A�j���[�V����
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, enemyAngle.y + XMConvertToRadians(180.0f));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, enemyAngle.x);

	m_pAirship->SetRotate(q);
	m_pAirship->SetPosition(
		m_pAirship->GetPosition() + 
		SimpleMath::Vector3::Transform(
			SimpleMath::Vector3(
			0.0f, 
			0.0f, 
			-m_pAirship->GetSpeed()
			), 
			m_pAirship->GetRotate()
		)
	);

	if (m_pAirship->GetFuel() >= 0)
	{
		m_pAirship->SetFuel(m_pAirship->GetFuel() - 1);

		m_pAirship->PartsMotion();
	}
	m_pAirship->SetAngle(enemyAngle);

}
