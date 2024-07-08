#include"pch.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"

#include"Bullet.h"
#include "Bullet_02.h"
using namespace DirectX;

static const float SPEED(200 / 60);		//���x		(m/s)
static const int OFFENSIVE_POWER(200);	//�U����	()
static const float SCALE(1);			//�傫��	()

Bullet_02::Bullet_02() :
	Bullet(SPEED, OFFENSIVE_POWER, SCALE)
{
}

Bullet_02::~Bullet_02()
{
}
