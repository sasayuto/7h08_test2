#include "pch.h"
#include"CrabRobotKillMotion.h"
#include<random>

using namespace DirectX;

#define FALL_SPEED_ACCELERATION		(0.1f / 60)		//落下の加速度			(m/s)
#define EXPLOSIVE_POWER_XZ			(1.0f / 60)		//爆発の横のパワー		(m/s)
#define EXPLOSIVE_ROTATE			(120 / 60)		//モデルの回転の速さ	(°/s）
#define NEXT_MOTION_TIME			(4)				//次の動きまでの時間	(s)

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
	//初期化
	m_nextMotionTime = 0.0f;

	for (auto& parts : m_pCrabRobot->GetParts())
	{
		parts->Initialize();
	}
}

void CrabRobotKillMotion::Update(const float& elapsedTime)
{
	//経過時間の計算
	m_nextMotionTime += elapsedTime;

	//時間経過で次のモーションへ
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

