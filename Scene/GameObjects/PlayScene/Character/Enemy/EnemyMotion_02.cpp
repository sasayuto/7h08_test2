#include "pch.h"
#include"EnemyMotion_02.h"
#include <math.h>
#include<random>
#include"EnemyManager.h"
using namespace DirectX;

#define BULLET_COOL_TIME		(1.0f)		//球クールタイム	(s)
#define ENEMY_MAX_SPEED			(8.0f / 60)	//前進の最大スピード	(m/s)
#define ENEMY_MAX_DISTANCE		(300.0f*300.0f)	//描画範囲(2乗)		(m)



EnemyMotion_02::EnemyMotion_02(Enemy* parent, EnemyManager* enemyManager, Player* player) :
	m_pEnemy(parent),
	m_pEnemyManager(enemyManager),
	m_pPlayer(player),
	m_nowTimer()
{

}

EnemyMotion_02::~EnemyMotion_02()
{
}

void EnemyMotion_02::Initialize()
{
	//敵が生きているか
	m_pEnemy->SetSpeed(ENEMY_MAX_SPEED);
	m_pEnemy->SetAngle(DirectX::SimpleMath::Vector3(0.4f,0,0));
	m_pEnemy->GetCollider()->SetRadius(1.3f);
	m_nowTimer = 0;
}

void EnemyMotion_02::Update(const float& elapsedTime)
{
	m_nowTimer += elapsedTime;
	Motion(elapsedTime);

	//球の
	float bulletCoolTime = m_pEnemy->GetBulletCoolTime();

	//球のクールタイム
	if (bulletCoolTime > 0.0f)
		bulletCoolTime -= elapsedTime;
	else
		bulletCoolTime = 0.0f;

	m_pEnemy->SetBulletCoolTime(bulletCoolTime);



	//パーツの更新
	m_pEnemy->PartsUpdate();
	if (m_pEnemy->GetHP() <= 0)
	{
		if (m_pEnemyManager)
			m_pEnemyManager->SetKillCount(m_pEnemyManager->GetKillCount() + 1);
		m_pEnemy->SetIState(m_pEnemy->GetEnemyKillMotion());
	}

}

void EnemyMotion_02::Render()
{
	m_pEnemy->PartsRender();
}

void EnemyMotion_02::Finalize()
{
}


void EnemyMotion_02::Motion(const float& elapsedTime)
{
	elapsedTime;
	SimpleMath::Vector3 position = m_pEnemy->GetPosition();

	if (m_nowTimer >= 5)
	{
		m_pEnemy->SetAngle(DirectX::SimpleMath::Vector3(-0.3f, -1.0f, -1));
	}
	if (m_nowTimer >= 10)
	{
		m_pEnemy->SetAngle(DirectX::SimpleMath::Vector3(-0.4f, -1.0f, 0));
	}
	if (m_nowTimer >= 16)
	{
		m_pEnemy->SetAngle(DirectX::SimpleMath::Vector3(-0.4f, -1.0f, 0.7f));
	}
	if (m_nowTimer >= 22.5f)
	{
		m_pEnemy->SetAngle(DirectX::SimpleMath::Vector3(0, 0.0f, 0));
	}
	if (m_nowTimer >= 25)
	{
		m_pEnemy->SetAngle(DirectX::SimpleMath::Vector3(0, 0.0f, 0));
	}

	SimpleMath::Quaternion q;
	//飛行機のアニメーション
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(
		SimpleMath::Vector3::UnitX, 
		XMConvertToRadians(m_pEnemy->GetAngle().y)
	);
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(
		SimpleMath::Vector3::UnitY,
		XMConvertToRadians(m_pEnemy->GetAngle().x)
	);
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(
		SimpleMath::Vector3::UnitZ,
		XMConvertToRadians(m_pEnemy->GetAngle().z)
	);

	m_pEnemy->SetRotate(m_pEnemy->GetRotate() * q);

	position += SimpleMath::Vector3::Transform(
		SimpleMath::Vector3(0.0f, 0.0f, -m_pEnemy->GetSpeed())
		, m_pEnemy->GetRotate()
	);

	m_pEnemy->SetPosition(position);

	if (m_pEnemy->GetFuel() >= 0)
	{
		m_pEnemy->SetFuel(m_pEnemy->GetFuel() - 1);

		m_pEnemy->PartsMotion();
	}
}
