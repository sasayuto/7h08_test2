#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"../Objects.h"
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"
#include"../MoveObjects/MoveObjects.h"
#include"BenchParts/IBenchComponent.h"
class Player;
class BenchManager;
/// <summary>
/// �I�u�W�F�N�g�̃N���X���`����
/// </summary>
class Bench :public MoveObjects
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Bench();
};
