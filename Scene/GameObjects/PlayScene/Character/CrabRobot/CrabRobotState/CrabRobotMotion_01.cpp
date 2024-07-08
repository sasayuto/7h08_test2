#include "pch.h"
#include"CrabRobotMotion_01.h"
#include <math.h>
#include<random>
#include"../CrabRobotManager.h"
#include"../CrabRobot.h"
using namespace DirectX;

#define BULLET_COOL_TIME		(1.0f)		//���N�[���^�C��	(s)
#define ENEMY_MAX_SPEED			(8.0f / 60)	//�O�i�̍ő�X�s�[�h	(m/s)
#define ENEMY_MAX_DISTANCE		(300.0f*300.0f)	//�`��͈�(2��)		(m)

CrabRobotMotion_01::CrabRobotMotion_01(CrabRobot* crabRobot, CrabRobotManager* crabRobotManager):
	m_pCrabRobot(crabRobot),
	m_pCrabRobotManager(crabRobotManager)
{
}

CrabRobotMotion_01::~CrabRobotMotion_01()
{
}

void CrabRobotMotion_01::Initialize()
{
	for (auto& parts : m_pCrabRobot->GetParts())
	{
		parts->Initialize();
	}
}

void CrabRobotMotion_01::Update(const float& elapsedTime)
{
	Motion();

	for (auto& parts : m_pCrabRobot->GetParts())
	{
		parts->Update(elapsedTime,m_pCrabRobot->GetPosition(),m_pCrabRobot->GetRotate());
	}
	//�p�[�c�������Ă��邩
	bool PartsSurvival = false;
	for (auto& parts : m_pCrabRobot->GetParts())
	{
		if (parts->GetSurvival())
		{
			parts->Update(elapsedTime, m_pCrabRobot->GetPosition(), m_pCrabRobot->GetRotate());
			PartsSurvival = true;
		}
		else
			parts->Explosion(elapsedTime);
	}
	//�p�[�c�����ׂĎ��񂾂�L����Ԃ�
	if (!PartsSurvival) 
	{
		if (m_pCrabRobotManager)
			m_pCrabRobotManager->SetKillCount(m_pCrabRobotManager->GetKillCount() + 1);
		m_pCrabRobot->SetIState(m_pCrabRobot->GetTurretKillMotion());
	}

	if (m_pCrabRobot->GetHP() <= 0)
	{
		if (m_pCrabRobotManager)
			m_pCrabRobotManager->SetKillCount(m_pCrabRobotManager->GetKillCount() + 1);
		m_pCrabRobot->SetIState(m_pCrabRobot->GetTurretKillMotion());
	}

}

void CrabRobotMotion_01::Render()
{
	for (auto& parts : m_pCrabRobot->GetParts())
	{
		parts->Render();
	}
}

void CrabRobotMotion_01::Finalize()
{
}

void CrabRobotMotion_01::Motion()
{
}
