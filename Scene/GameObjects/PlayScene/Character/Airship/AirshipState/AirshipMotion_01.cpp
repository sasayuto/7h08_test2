#include "pch.h"
#include"AirshipMotion_01.h"
#include <math.h>
#include<random>
using namespace DirectX;

#define BULLET_COOL_TIME		(1.0f)		//���N�[���^�C��	(s)
#define ENEMY_MAX_SPEED			(8.0f / 60)	//�O�i�̍ő�X�s�[�h	(m/s)
#define ENEMY_MAX_DISTANCE		(1000.0f*1000.0f)	//�`��͈�(2��)		(m)



AirshipMotion_01::AirshipMotion_01(Airship* parent, Player* player) :
	m_pAirship(parent),
	m_pPlayer(player)
{

}

AirshipMotion_01::~AirshipMotion_01()
{
}

void AirshipMotion_01::Initialize()
{
	//�G�������Ă��邩
	m_pAirship->SetSpeed(ENEMY_MAX_SPEED);
	m_pAirship->SetAngle(DirectX::SimpleMath::Vector3(0.1f,0,0));
}

void AirshipMotion_01::Update(const float& elapsedTime)
{
	Motion();

	//����
	float bulletCoolTime = m_pAirship->GetBulletCoolTime();

	//���̃N�[���^�C��
	if (bulletCoolTime > 0.0f)
		bulletCoolTime -= elapsedTime;
	else
		bulletCoolTime = 0.0f;

	//���𔭎�
	m_pAirship->SetBulletCoolTime(bulletCoolTime);

	//m_pAirship->Shot(BULLET_COOL_TIME);


	//�p�[�c�̍X�V
	m_pAirship->PartsUpdate();
	if (m_pAirship->GetHP() <= 0)
	{
		//HP���Ȃ������玀�S
		m_pAirship->SetSurvival(false);
		//m_pAirship->SetIState(m_pAirship->GetEnemyKillMotion());
	}

}

void AirshipMotion_01::Render()
{
	//�`��
	m_pAirship->PartsRender();
}

void AirshipMotion_01::Finalize()
{
}


void AirshipMotion_01::Motion()
{
	//�ʒu���擾
	SimpleMath::Vector3 position = m_pAirship->GetPosition();

	//�v���C���[�Ƃ̋������擾
	SimpleMath::Vector3 distance = m_pAirship->GetPosition() - m_pPlayer->GetPosition();

	//�f�X�|�[������
	if (distance.LengthSquared() >= ENEMY_MAX_DISTANCE)
	{
		m_pAirship->SetSurvival(false);
		return;
	}

	//��s�D�̉�]
	SimpleMath::Quaternion q;
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(
		SimpleMath::Vector3::UnitY,
		XMConvertToRadians(m_pAirship->GetAngle().x)
	);

	//��]���Z�b�g
	m_pAirship->SetRotate(m_pAirship->GetRotate() * q);

	//�ʒu���v�Z
	position += SimpleMath::Vector3::Transform(
		SimpleMath::Vector3(0.0f, 0.0f, -m_pAirship->GetSpeed())
		, m_pAirship->GetRotate()
	);

	//�ʒu���Z�b�g
	m_pAirship->SetPosition(position);

	//�R��������
	m_pAirship->SetFuel(m_pAirship->GetFuel() - 1);

	//�p�[�c�̍X�V
	m_pAirship->PartsMotion();
}
