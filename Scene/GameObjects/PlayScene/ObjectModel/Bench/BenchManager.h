#pragma once
#include"Bench.h"
#include"../MoveObjects/MoveObjectsManager.h"
class Enemy;
class Player;
class Airship;
class BulletManager;
class SandstormEffect;
/// <summary>
/// �I�u�W�F�N�g�̊Ǘ��҂̃N���X���`����
/// </summary>
class BenchManager : public MoveObjectsManager
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="mapLoader">�}�b�v�̃A�h���X</param>
	BenchManager();
};