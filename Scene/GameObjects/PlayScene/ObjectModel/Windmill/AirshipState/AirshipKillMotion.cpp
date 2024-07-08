#include "pch.h"
#include"EnemyKillMotion.h"
#include<random>

using namespace DirectX;

#define FALL_SPEED_ACCELERATION		(0.1f / 60)		//落下の加速度			(m/s)
#define EXPLOSIVE_POWER_XZ			(1.0f / 60)		//爆発の横のパワー		(m/s)
#define EXPLOSIVE_ROTATE			(120 / 60)		//モデルの回転の速さ	(°/s）
#define NEXT_MOTION_TIME			(9)				//次の動きまでの時間	(s)

EnemyKillMotion::EnemyKillMotion(Enemy* parent):
	m_pEnemy(parent),
	m_nextMotionTime()
{
}

EnemyKillMotion::~EnemyKillMotion()
{
}

void EnemyKillMotion::Initialize()
{
	//初期化
	m_nextMotionTime = 0.0f;

	//360度ランダムな方向を取得
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> angle(0, 6.28f);
	float explosionAngleX = static_cast<float>(angle(engine));

	//爆発力をランダムにする
  	std::uniform_real_distribution<> power(5, 10);
	float explosionPower = static_cast<float>(power(engine)) / 60;
	//爆発力を重力に付ける
	m_pEnemy->SetGravity(-explosionPower);

	//ランダムな方向
	m_killrotate *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, explosionAngleX);
	m_pEnemy->PartsInitialize();
}

void EnemyKillMotion::Update(const float& elapsedTime)
{
	//時間経過で次のモーションへ
	if (m_nextMotionTime >= NEXT_MOTION_TIME)
	{
		m_pEnemy->SetSurvival(false);
	}

	//経過時間の計算
	m_nextMotionTime += elapsedTime;

	m_pEnemy->PartsExplosion();
	Motion();
}

void EnemyKillMotion::Render()
{
	m_pEnemy->PartsRender();
}

void EnemyKillMotion::Finalize()
{
}

void EnemyKillMotion::Motion()
{
	//破壊される方向に飛ばす
	SimpleMath::Vector3 position = SimpleMath::Vector3::Transform(SimpleMath::Vector3(0, 0, EXPLOSIVE_POWER_XZ), m_killrotate)
		+ m_pEnemy->GetPosition();
	//重力をつける
	m_pEnemy->SetGravity(m_pEnemy->GetGravity() + FALL_SPEED_ACCELERATION);

	//キル座標に重力をつける
	position.y -= m_pEnemy->GetGravity();

	SimpleMath::Quaternion q = SimpleMath::Quaternion::Identity;
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, XMConvertToRadians(EXPLOSIVE_ROTATE));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(EXPLOSIVE_ROTATE));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, XMConvertToRadians(EXPLOSIVE_ROTATE));

	m_pEnemy->SetRotate(q* m_pEnemy->GetRotate());
	m_pEnemy->SetPosition(position);
}

