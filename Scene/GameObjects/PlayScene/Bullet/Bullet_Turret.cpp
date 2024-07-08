#include"pch.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"

#include"Bullet.h"
#include "Bullet_Turret.h"

const float Bullet_Turret::FALL_SPEED_ACCELERATION(0.82f/ 60.0f);	//落下の加速度			(m/s)

using namespace DirectX;

static const float SPEED(100.0f / 60);		//速度		(m/s)
static const int OFFENSIVE_POWER(2000);		//攻撃力	()
static const float SCALE(5.1f);				//大きさ	()

Bullet_Turret::Bullet_Turret() :
	Bullet(SPEED, OFFENSIVE_POWER, SCALE),
	m_gravity(0)
{
}

Bullet_Turret::~Bullet_Turret()
{
}
void Bullet_Turret::Update()
{
	DirectX::SimpleMath::Vector3 position = GetPosition();
	//発射されているか
	m_gravity += FALL_SPEED_ACCELERATION;
	//球の種類によって更新を分ける
	//減速度計算

	//前方に調整し減速
	SimpleMath::Vector3 move = SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.0f, -GetSpeed()), GetRotate());
	position += move;
	position.y -= m_gravity;

	//当たり判定に位置と半径をセット
	GetCollider()->SetPosition(position);

	//ボールの移動
	SetPosition(position);

}
