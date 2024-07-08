#include "pch.h"
#include"EnemyMotion.h"
#include <math.h>
#include<random>
#include"EnemyManager.h"
using namespace DirectX;

const float BULLET_COOL_TIME(1.0f);					//球クールタイム	(s)
const float ENEMY_MAX_SPEED(8.0f / 60);				//前進の最大スピード	(m/s)
const float ENEMY_MAX_DISTANCE(300.0f * 300.0f);	//描画範囲(2乗)		(m)



EnemyMotion::EnemyMotion(Enemy* parent, EnemyManager* enemyManager, Player* player) :
	m_pEnemy(parent),
	m_pEnemyManager(enemyManager),
	m_pPlayer(player)
{

}

EnemyMotion::~EnemyMotion()
{
}

void EnemyMotion::Initialize()
{
	//敵が生きているか
	m_pEnemy->SetSurvival(true);
	m_pEnemy->SetSpeed(ENEMY_MAX_SPEED);
	m_pEnemy->GetCollider()->SetRadius(1.3f);
}

void EnemyMotion::Update(const float& elapsedTime)
{
	//動き
	Motion(elapsedTime);

	//球のクールタイム
	float bulletCoolTime = m_pEnemy->GetBulletCoolTime();

	//球のクールタイムを減らす
	if (bulletCoolTime > 0.0f)
		bulletCoolTime -= elapsedTime;
	else
		bulletCoolTime = 0.0f;

	//クールタイムをセット
	m_pEnemy->SetBulletCoolTime(bulletCoolTime);

	//球を発射
	m_pEnemy->Shot(BULLET_COOL_TIME);

	//パーツの更新
	m_pEnemy->PartsUpdate();

	//HPが０になったら
	if (m_pEnemy->GetHP() <= 0)
	{
		//キルをカウント
		m_pEnemyManager->SetKillCount(m_pEnemyManager->GetKillCount() + 1);
		
		//キルの状態へ
		m_pEnemy->SetIState(m_pEnemy->GetEnemyKillMotion());
	}

}

void EnemyMotion::Render()
{
	//描画
	m_pEnemy->PartsRender();
}

void EnemyMotion::Finalize()
{
}


void EnemyMotion::Motion(const float& elapsedTime)
{
	elapsedTime;
	//位置を取得
	SimpleMath::Vector3 enemyPosition = m_pEnemy->GetPosition();

	//方向を取得
	SimpleMath::Vector3 enemyAngle = m_pEnemy->GetAngle();

	//プレイヤーとの距離を取得
	SimpleMath::Vector3 distance = m_pEnemy->GetPosition() - m_pPlayer->GetPosition();


	//プレイヤーの生存してたら追尾
	if (m_pPlayer->GetSurvival())
	{
		//プレイヤーポジションから角度を求める
		enemyAngle.y = static_cast<float>(atan2(distance.y, distance.z));
		enemyAngle.x = static_cast<float>(atan2(distance.x, distance.z));

		//Y軸を０度から１８０度の回転に変更する
		if ((-1.57f <= enemyAngle.y && enemyAngle.y < 0) || (1.57f >= enemyAngle.y && enemyAngle.y > 0))
		{
			enemyAngle.y *= -1;			//逆回転にする
			enemyAngle.y += XMConvertToRadians(180.0f);		//１８０度回す
		}
	}

	SimpleMath::Quaternion q;
	//飛行機のアニメーション
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, enemyAngle.y + XMConvertToRadians(180.0f));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, enemyAngle.x);

	//回転をセット
	m_pEnemy->SetRotate(q);

	//位置をセット
	m_pEnemy->SetPosition(
		m_pEnemy->GetPosition() + 
		SimpleMath::Vector3::Transform(
			SimpleMath::Vector3(
			0.0f, 
			0.0f, 
			-m_pEnemy->GetSpeed()
			), 
			m_pEnemy->GetRotate()
		)
	);

	//燃料が切れてなかったら
	if (m_pEnemy->GetFuel() >= 0)
	{
		//燃料を減らす
		m_pEnemy->SetFuel(m_pEnemy->GetFuel() - 1);

		//燃料を使った動き
		m_pEnemy->PartsMotion();
	}

	//アングルをセット
	m_pEnemy->SetAngle(enemyAngle);

}
