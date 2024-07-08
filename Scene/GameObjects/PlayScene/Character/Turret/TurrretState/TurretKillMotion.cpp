#include "pch.h"
#include"TurretKillMotion.h"
#include<random>

using namespace DirectX;

#define FALL_SPEED_ACCELERATION		(0.1f / 60)		//�����̉����x			(m/s)
#define EXPLOSIVE_POWER_XZ			(1.0f / 60)		//�����̉��̃p���[		(m/s)
#define EXPLOSIVE_ROTATE			(120 / 60)		//���f���̉�]�̑���	(��/s�j
#define NEXT_MOTION_TIME			(4)				//���̓����܂ł̎���	(s)

TurretKillMotion::TurretKillMotion(Turret* turret):
	m_pTurret(turret),
	m_nextMotionTime()
{
}

TurretKillMotion::~TurretKillMotion()
{
}

void TurretKillMotion::Initialize()
{
	//������
	m_nextMotionTime = 0.0f;

	for (auto& parts : m_pTurret->GetParts())
	{
		parts->Initialize();
	}
}

void TurretKillMotion::Update(const float& elapsedTime)
{
	//�o�ߎ��Ԃ̌v�Z
	m_nextMotionTime += elapsedTime;

	//���Ԍo�߂Ŏ��̃��[�V������
	if (m_nextMotionTime >= NEXT_MOTION_TIME)
	{
		m_pTurret->SetSurvival(false);
	}

	for (auto& parts : m_pTurret->GetParts())
	{
		parts->Explosion(elapsedTime);
	}
}

void TurretKillMotion::Render()
{
	for (auto& parts : m_pTurret->GetParts())
	{
		parts->Render();
	}
}

void TurretKillMotion::Finalize()
{
}

void TurretKillMotion::Motion()
{
}

