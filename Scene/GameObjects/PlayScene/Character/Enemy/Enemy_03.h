#pragma once
#include"Enemy.h"


/// <summary>
/// �G3�̃N���X���`����
/// </summary>
class Enemy_03 :public Enemy
{
public:
	//�G��HP
	static const unsigned ENEMY_MAX_HP = 10;

	//�G�̔R��
	static const unsigned ENEMY_MAX_FUEL = 1000000;

	//�G�̃p���[
	static const int ENEMY_OFFENSIVE_POWER = 1;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Enemy_03();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Enemy_03();

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="bulletManager">���̊Ǘ��҃A�h���X</param>
	/// <param name="enemyManager">�G�̊Ǘ��҂̃A�h���X</param>
	/// <param name="objectsManager">�I�u�W�F�N�g�̊Ǘ��҂̃A�h���X</param>
	/// <param name="treeManager">�؂̊Ǘ��҂̃A�h���X</param>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	/// <param name="airshipManager">��s�D�̊Ǘ��҂̃A�h���X</param>
	/// <param name="windmillManager">���Ԃ̊Ǘ��҂̃A�h���X</param>
	/// <param name="floor">���̃A�h���X</param>
	/// <param name="sandstormManager">�����̊Ǘ��҂̃A�h���X</param>
	/// <param name="floorManager_01">���̊Ǘ��҂̃A�h���X</param>
	void Initialize(
		BulletManager* bulletManager,
		EnemyManager* enemyManager,
		ObjectsManager* objectsManager,
		Player* player,
		AirshipManager* airshipManager,
		WindmillManager* windmillManager,
		Floor* floor,
		SandstormManager* sandstormManager,
		FloorManager_01* floorManager_01,
		BigBrickWallManager* bigBrickWallManager
	)override;

	/// <summary>
/// ���������Z�b�g
/// </summary>
	void Reset()override;


};
