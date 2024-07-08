#pragma once
#include"Enemy.h"


/// <summary>
/// �G�J�X�^���̃N���X���`����
/// </summary>
class EnemyCustom_00 :public Enemy
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="Hp">�G��HP</param>
	/// <param name="Fuel">�G�̔R��</param>
	/// <param name="offensivePower">�G�̃p���[</param>
	EnemyCustom_00(const int& Hp, const int& Fuel, const int& offensivePower);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyCustom_00();

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

private:
	int m_maxHp;

	int m_maxFuel;

	int m_OffensivePower;
};
