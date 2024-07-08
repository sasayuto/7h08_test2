#include "pch.h"
#include"TurretMotion_01.h"
#include <math.h>
#include<random>
#include"../TurretManager.h"
using namespace DirectX;

#define BULLET_COOL_TIME		(1.0f)		//���N�[���^�C��	(s)
#define ENEMY_MAX_SPEED			(8.0f / 60)	//�O�i�̍ő�X�s�[�h	(m/s)
#define ENEMY_MAX_DISTANCE		(300.0f*300.0f)	//�`��͈�(2��)		(m)

TurretMotion_01::TurretMotion_01(Turret* turret,TurretManager* turretManager) :
m_pTurret(turret),
m_pTurretManager(turretManager)
{

}

TurretMotion_01::~TurretMotion_01()
{
}

void TurretMotion_01::Initialize()
{
	for (auto& parts : m_pTurret->GetParts())
	{
		parts->Initialize();
	}
}

void TurretMotion_01::Update(const float& elapsedTime)
{
	Motion();

	for (auto& parts : m_pTurret->GetParts())
	{
		parts->Update(elapsedTime,m_pTurret->GetPosition(),m_pTurret->GetRotate());
	}
	//�p�[�c�������Ă��邩
	bool PartsSurvival = false;
	for (auto& parts : m_pTurret->GetParts())
	{
		if (parts->GetSurvival())
		{
			parts->Update(elapsedTime, m_pTurret->GetPosition(), m_pTurret->GetRotate());
			PartsSurvival = true;
		}
		else
			parts->Explosion(elapsedTime);
	}
	//�p�[�c�����ׂĎ��񂾂�L����Ԃ�
	if (!PartsSurvival) 
	{
		if (m_pTurretManager)
			m_pTurretManager->SetKillCount(m_pTurretManager->GetKillCount() + 1);
		m_pTurret->SetIState(m_pTurret->GetTurretKillMotion());
	}

	if (m_pTurret->GetHP() <= 0)
	{
		if (m_pTurretManager)
			m_pTurretManager->SetKillCount(m_pTurretManager->GetKillCount() + 1);
		m_pTurret->SetIState(m_pTurret->GetTurretKillMotion());
	}

}

void TurretMotion_01::Render()
{
	for (auto& parts : m_pTurret->GetParts())
	{
		parts->Render();
	}
}

void TurretMotion_01::Finalize()
{
}

void TurretMotion_01::Motion()
{
}
