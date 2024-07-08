#include"pch.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"

#include"Bullet.h"
#include "Bullet_01.h"
using namespace DirectX;

const float SPEED(150.0f / 60);		//���x		(m/s)
const int OFFENSIVE_POWER(10);		//�U����	()
const float SCALE(0.1f);			//�傫��	()

Bullet_01::Bullet_01() :
	Bullet(SPEED, OFFENSIVE_POWER, SCALE)
{
}

Bullet_01::~Bullet_01()
{
}
