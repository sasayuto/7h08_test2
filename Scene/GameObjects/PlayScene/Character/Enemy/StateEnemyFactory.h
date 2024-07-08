#pragma once
#include "IStateEnemyFactory.h"

class EnemyManager;
class Player;
class Enemy;
class IState;

/// <summary>
/// StateEnemyFactory�̃N���X���`����
/// </summary>
class StateEnemyFactory : public IStateEnemyFactory
{
public:
	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�G�̃A�h���X</param>
	/// <param name="supplyPointManager">�G�̊Ǘ��҂̃A�h���X</param>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	/// <returns>�ʏ�̏�Ԃ̃|�C���^</returns>
	static std::unique_ptr<IState> CreateEnemyMotion(
		Enemy* enemy,
		EnemyManager* enemyManager,
		Player* player
	);

	/// <summary>
	/// �ʏ�̏�ԂP�𐶐�
	/// </summary>
	/// <param name="parent">�G�̃A�h���X</param>
	/// <param name="supplyPointManager">�G�̊Ǘ��҂̃A�h���X</param>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	/// <returns>�ʏ�̏�ԂP�̃|�C���^</returns>
	static std::unique_ptr<IState> CreateEnemyMotion_01(
		Enemy* enemy,
		EnemyManager* enemyManager,
		Player* player
	);

	/// <summary>
	/// �ʏ�̏�ԂQ�𐶐�
	/// </summary>
	/// <param name="parent">�G�̃A�h���X</param>
	/// <param name="supplyPointManager">�G�̊Ǘ��҂̃A�h���X</param>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	/// <returns>�ʏ�̏�ԂQ�̃|�C���^</returns>
	static std::unique_ptr<IState> CreateEnemyMotion_02(
		Enemy* enemy,
		EnemyManager* enemyManager,
		Player* player
	);

	/// <summary>
	/// ���S�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	/// <returns>���S�̏�Ԃ̃|�C���^</returns>
	static std::unique_ptr<IState> CreateEnemyKillMotion(
		Enemy* enemy);
};

