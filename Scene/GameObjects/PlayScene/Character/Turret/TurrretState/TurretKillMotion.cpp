#include "pch.h"
#include"TurretKillMotion.h"
#include<random>

using namespace DirectX;

#define FALL_SPEED_ACCELERATION		(0.1f / 60)		//落下の加速度			(m/s)
#define EXPLOSIVE_POWER_XZ			(1.0f / 60)		//爆発の横のパワー		(m/s)
#define EXPLOSIVE_ROTATE			(120 / 60)		//モデルの回転の速さ	(°/s）
#define NEXT_MOTION_TIME			(4)				//次の動きまでの時間	(s)

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
	//初期化
	m_nextMotionTime = 0.0f;

	for (auto& parts : m_pTurret->GetParts())
	{
		parts->Initialize();
	}
}

void TurretKillMotion::Update(const float& elapsedTime)
{
	//経過時間の計算
	m_nextMotionTime += elapsedTime;

	//時間経過で次のモーションへ
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

