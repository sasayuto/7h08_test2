#include "pch.h"
#include"AirshipMotion_01.h"
#include <math.h>
#include<random>
using namespace DirectX;

#define BULLET_COOL_TIME		(1.0f)		//球クールタイム	(s)
#define ENEMY_MAX_SPEED			(8.0f / 60)	//前進の最大スピード	(m/s)
#define ENEMY_MAX_DISTANCE		(1000.0f*1000.0f)	//描画範囲(2乗)		(m)



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
	//敵が生きているか
	m_pAirship->SetSpeed(ENEMY_MAX_SPEED);
	m_pAirship->SetAngle(DirectX::SimpleMath::Vector3(0.1f,0,0));
}

void AirshipMotion_01::Update(const float& elapsedTime)
{
	Motion();

	//球の
	float bulletCoolTime = m_pAirship->GetBulletCoolTime();

	//球のクールタイム
	if (bulletCoolTime > 0.0f)
		bulletCoolTime -= elapsedTime;
	else
		bulletCoolTime = 0.0f;

	//球を発射
	m_pAirship->SetBulletCoolTime(bulletCoolTime);

	//m_pAirship->Shot(BULLET_COOL_TIME);


	//パーツの更新
	m_pAirship->PartsUpdate();
	if (m_pAirship->GetHP() <= 0)
	{
		//HPがなかったら死亡
		m_pAirship->SetSurvival(false);
		//m_pAirship->SetIState(m_pAirship->GetEnemyKillMotion());
	}

}

void AirshipMotion_01::Render()
{
	//描画
	m_pAirship->PartsRender();
}

void AirshipMotion_01::Finalize()
{
}


void AirshipMotion_01::Motion()
{
	//位置を取得
	SimpleMath::Vector3 position = m_pAirship->GetPosition();

	//プレイヤーとの距離を取得
	SimpleMath::Vector3 distance = m_pAirship->GetPosition() - m_pPlayer->GetPosition();

	//デスポーン距離
	if (distance.LengthSquared() >= ENEMY_MAX_DISTANCE)
	{
		m_pAirship->SetSurvival(false);
		return;
	}

	//飛行船の回転
	SimpleMath::Quaternion q;
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(
		SimpleMath::Vector3::UnitY,
		XMConvertToRadians(m_pAirship->GetAngle().x)
	);

	//回転をセット
	m_pAirship->SetRotate(m_pAirship->GetRotate() * q);

	//位置を計算
	position += SimpleMath::Vector3::Transform(
		SimpleMath::Vector3(0.0f, 0.0f, -m_pAirship->GetSpeed())
		, m_pAirship->GetRotate()
	);

	//位置をセット
	m_pAirship->SetPosition(position);

	//燃料を消費
	m_pAirship->SetFuel(m_pAirship->GetFuel() - 1);

	//パーツの更新
	m_pAirship->PartsMotion();
}
