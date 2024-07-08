#include"pch.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"

#include"Bullet.h"
#include "Bullet_Turret.h"

const float Bullet_Turret::FALL_SPEED_ACCELERATION(0.82f/ 60.0f);	//�����̉����x			(m/s)

using namespace DirectX;

static const float SPEED(100.0f / 60);		//���x		(m/s)
static const int OFFENSIVE_POWER(2000);		//�U����	()
static const float SCALE(5.1f);				//�傫��	()

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
	//���˂���Ă��邩
	m_gravity += FALL_SPEED_ACCELERATION;
	//���̎�ނɂ���čX�V�𕪂���
	//�����x�v�Z

	//�O���ɒ���������
	SimpleMath::Vector3 move = SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.0f, -GetSpeed()), GetRotate());
	position += move;
	position.y -= m_gravity;

	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	GetCollider()->SetPosition(position);

	//�{�[���̈ړ�
	SetPosition(position);

}
