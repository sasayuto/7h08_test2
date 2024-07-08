#include "pch.h"
#include"EnemyKillMotion.h"
#include<random>

using namespace DirectX;

#define FALL_SPEED_ACCELERATION		(0.1f / 60)		//�����̉����x			(m/s)
#define EXPLOSIVE_POWER_XZ			(1.0f / 60)		//�����̉��̃p���[		(m/s)
#define EXPLOSIVE_ROTATE			(120 / 60)		//���f���̉�]�̑���	(��/s�j
#define NEXT_MOTION_TIME			(9)				//���̓����܂ł̎���	(s)

EnemyKillMotion::EnemyKillMotion(Enemy* parent):
	m_pEnemy(parent),
	m_nextMotionTime()
{
}

EnemyKillMotion::~EnemyKillMotion()
{
}

void EnemyKillMotion::Initialize()
{
	//������
	m_nextMotionTime = 0.0f;

	//360�x�����_���ȕ������擾
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> angle(0, 6.28f);
	float explosionAngleX = static_cast<float>(angle(engine));

	//�����͂������_���ɂ���
  	std::uniform_real_distribution<> power(5, 10);
	float explosionPower = static_cast<float>(power(engine)) / 60;
	//�����͂��d�͂ɕt����
	m_pEnemy->SetGravity(-explosionPower);

	//�����_���ȕ���
	m_killrotate *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, explosionAngleX);
	m_pEnemy->PartsInitialize();
}

void EnemyKillMotion::Update(const float& elapsedTime)
{
	//���Ԍo�߂Ŏ��̃��[�V������
	if (m_nextMotionTime >= NEXT_MOTION_TIME)
	{
		m_pEnemy->SetSurvival(false);
	}

	//�o�ߎ��Ԃ̌v�Z
	m_nextMotionTime += elapsedTime;

	m_pEnemy->PartsExplosion();
	Motion();
}

void EnemyKillMotion::Render()
{
	m_pEnemy->PartsRender();
}

void EnemyKillMotion::Finalize()
{
}

void EnemyKillMotion::Motion()
{
	//�j�󂳂������ɔ�΂�
	SimpleMath::Vector3 position = SimpleMath::Vector3::Transform(SimpleMath::Vector3(0, 0, EXPLOSIVE_POWER_XZ), m_killrotate)
		+ m_pEnemy->GetPosition();
	//�d�͂�����
	m_pEnemy->SetGravity(m_pEnemy->GetGravity() + FALL_SPEED_ACCELERATION);

	//�L�����W�ɏd�͂�����
	position.y -= m_pEnemy->GetGravity();

	SimpleMath::Quaternion q = SimpleMath::Quaternion::Identity;
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, XMConvertToRadians(EXPLOSIVE_ROTATE));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(EXPLOSIVE_ROTATE));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, XMConvertToRadians(EXPLOSIVE_ROTATE));

	m_pEnemy->SetRotate(q* m_pEnemy->GetRotate());
	m_pEnemy->SetPosition(position);
}

