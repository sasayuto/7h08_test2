#include "pch.h"
#include"PlayerKillMotion.h"
#include<random>

using namespace DirectX;

const float KillMotion::FALL_SPEED_ACCELERATION	(0.03f / 60);	//落下の加速度			(m/s)
const float KillMotion::EXPLOSIVE_POWER_XZ		(1.0f / 60);	//爆発の横のパワー		(m/s)
const float KillMotion::EXPLOSIVE_A				(2.0f / 60);	//爆発の横のパワー		(m/s)
const float KillMotion::EXPLOSIVE_ROTATE		(120 / 60);		//モデルの回転の速さ	(°/s）
const float KillMotion::NEXT_MOTION_TIME		(3);			//次の状態までの時間	(s)

KillMotion::KillMotion(Player* parent):
	m_pPlayer(parent),
	m_nextMotionTime()
{
}

KillMotion::~KillMotion()
{
}

void KillMotion::Initialize()
{
	//初期化
	m_nextMotionTime = 0.0f;
	//m_pPlayer->SetRotate(SimpleMath::Quaternion::Identity);

	//プレイヤーを生存をなくす
	m_pPlayer->SetSurvival(false);

	m_pPlayer->PartsInitialize();

	//プレイヤーの状態によって半径が変わるのでセット
	m_pPlayer->GetCollider()->SetRadius(20);

}

void KillMotion::Update(const float& elapsedTime)
{
	//経過時間の計算
	m_nextMotionTime += elapsedTime;

	m_pPlayer->PartsExplosion();

	//仮でボディーの位置にしとく（カメラが動かないため）
	m_pPlayer->SetPosition(m_pPlayer->GetParts()[0]->GetPosition());

	//時間経過で次のモーションへ
	if (m_nextMotionTime >= NEXT_MOTION_TIME)
	{
		//キルの状態から戻るときはリセットを呼ぶ！
		m_pPlayer->Reset();
		m_pPlayer->SetIState(m_pPlayer->GetMotion());
	}

	if (m_pPlayer->GetFuel() >= 0)
	{
		//仮の煙のエフェクトの更新
		m_pPlayer->GetPlayerEffect()->Update(elapsedTime,
			m_pPlayer->GetPosition(),
			m_pPlayer->GetParts()[0]->GetRotate(),
			m_pPlayer->GetHP()
		);
	}

}

void KillMotion::Render()
{
	m_pPlayer->PartsRender();
	m_pPlayer->GetPlayerEffect()->Render();
	m_pPlayer->GetBloodEffect()->Render();
}

void KillMotion::Finalize()
{
}

void KillMotion::Motion(const float& elapsedTime)
{
	elapsedTime;
}

