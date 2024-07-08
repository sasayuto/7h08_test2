#include"pch.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"

#include"Bullet.h"
#include "Bullet_01.h"
using namespace DirectX;

const float SPEED(150.0f / 60);		//ë¨ìx		(m/s)
const int OFFENSIVE_POWER(10);		//çUåÇóÕ	()
const float SCALE(0.1f);			//ëÂÇ´Ç≥	()

Bullet_01::Bullet_01() :
	Bullet(SPEED, OFFENSIVE_POWER, SCALE)
{
}

Bullet_01::~Bullet_01()
{
}
