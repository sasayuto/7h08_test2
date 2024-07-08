#include "pch.h"
#include"CrabRobotKillMotion.h"
#include<random>

using namespace DirectX;

#define FALL_SPEED_ACCELERATION		(0.1f / 60)		//�����̉����x			(m/s)
#define EXPLOSIVE_POWER_XZ			(1.0f / 60)		//�����̉��̃p���[		(m/s)
#define EXPLOSIVE_ROTATE			(120 / 60)		//���f���̉�]�̑���	(��/s�j
#define NEXT_MOTION_TIME			(4)				//���̓����܂ł̎���	(s)

CrabRobotKillMotion::CrabRobotKillMotion(CrabRobot* crabRobot):
	m_pCrabRobot(crabRobot),
	m_nextMotionTime()
{
}

CrabRobotKillMotion::~CrabRobotKillMotion()
{
}

void CrabRobotKillMotion::Initialize()
{
	//������
	m_nextMotionTime = 0.0f;

	for (auto& parts : m_pCrabRobot->GetParts())
	{
		parts->Initialize();
	}
}

void CrabRobotKillMotion::Update(const float& elapsedTime)
{
	//�o�ߎ��Ԃ̌v�Z
	m_nextMotionTime += elapsedTime;

	//���Ԍo�߂Ŏ��̃��[�V������
	if (m_nextMotionTime >= NEXT_MOTION_TIME)
	{
		m_pCrabRobot->SetSurvival(false);
	}

	for (auto& parts : m_pCrabRobot->GetParts())
	{
		parts->Explosion(elapsedTime);
	}
}

void CrabRobotKillMotion::Render()
{
	for (auto& parts : m_pCrabRobot->GetParts())
	{
		parts->Render();
	}
}

void CrabRobotKillMotion::Finalize()
{
}

void CrabRobotKillMotion::Motion()
{
}

