#include "pch.h"
#include"AirshipMotion.h"
#include <math.h>
#include<random>
using namespace DirectX;

#define BULLET_COOL_TIME		(1.0f)		//球クールタイム	(s)
#define ENEMY_MAX_SPEED			(8.0f / 60)	//前進の最大スピード	(m/s)
#define ENEMY_MAX_DISTANCE		(300.0f*300.0f)	//描画範囲(2乗)		(m)



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
	//敵が生きているか
	m_pAirship->Reset();
	m_pAirship->SetSurvival(true);
	m_pAirship->SetSpeed(ENEMY_MAX_SPEED);
}

void AirshipMotion::Update(const float& elapsedTime)
{
	Motion();

	//球の
	float bulletCoolTime = m_pAirship->GetBulletCoolTime();
	//球のクールタイム
	if (bulletCoolTime > 0.0f)
		bulletCoolTime -= elapsedTime;
	else
		bulletCoolTime = 0.0f;

	m_pAirship->SetBulletCoolTime(bulletCoolTime);

	m_pAirship->Shot(BULLET_COOL_TIME);

	//パーツの更新
	m_pAirship->PartsUpdate();

	////HPが０になったら
	//if (m_pAirship->GetHP() <= 0)
	//{
	//	
	//	//キルの状態へ
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

	//デスポーン距離
	if (distance.LengthSquared() >= ENEMY_MAX_DISTANCE)
	{
		m_pAirship->SetSurvival(false);
		return;
	}

	//プレイヤーのHPがなくなったら追尾しない
	if (m_pPlayer->GetHP() > 0)
	{
		//プレイヤーポジションから角度を求める
		enemyAngle.y = static_cast<float>(atan2(distance.y, distance.z));
		enemyAngle.x = static_cast<float>(atan2(distance.x, distance.z));
	}
	//Y軸を０度から１８０度の回転に変更する
	if (( - 1.57f <= enemyAngle.y && enemyAngle.y < 0)|| (1.57f >= enemyAngle.y && enemyAngle.y > 0))
	{
		enemyAngle.y *= -1;			//逆回転にする
		enemyAngle.y += XMConvertToRadians(180.0f);		//１８０度回す
	}

	SimpleMath::Quaternion q;
	//飛行機のアニメーション
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
