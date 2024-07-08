#include"pch.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"

#include"Bullet.h"
#include "Bullet_02.h"
using namespace DirectX;

static const float SPEED(200 / 60);		//ë¨ìx		(m/s)
static const int OFFENSIVE_POWER(200);	//çUåÇóÕ	()
static const float SCALE(1);			//ëÂÇ´Ç≥	()

Bullet_02::Bullet_02() :
	Bullet(SPEED, OFFENSIVE_POWER, SCALE)
{
}

Bullet_02::~Bullet_02()
{
}
