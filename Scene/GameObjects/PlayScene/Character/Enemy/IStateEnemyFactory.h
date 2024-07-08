#pragma once
#include <combaseapi.h>
class EnemyManager;
class Player;
class Enemy;
class IState;

/// <summary>
/// IStateEnemyFactory�C���^�[�t�F�C�X�̃N���X���`����
/// </summary>
interface  IStateEnemyFactory
{
	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�G�̃A�h���X</param>
	/// <param name="supplyPointManager">�G�̊Ǘ��҂̃A�h���X</param>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	/// <returns>�ʏ�̏�Ԃ̃|�C���^</returns>
	virtual std::unique_ptr<IState> CreateEnemyMotion(
		Enemy* parent,
		EnemyManager* supplyPointManager,
		Player* respawnManager
	) = 0;

	/// <summary>
	///  �ʏ�̏�ԂP�𐶐�
	/// </summary>
	/// <param name="parent">�G�̃A�h���X</param>
	/// <param name="supplyPointManager">�G�̊Ǘ��҂̃A�h���X</param>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	/// <returns>�ʏ�̏�ԂP�̃|�C���^</returns>
	virtual std::unique_ptr<IState> CreateEnemyMotion_01(
		Enemy* parent,
		EnemyManager* supplyPointManager,
		Player* player
	) = 0;

	/// <summary>
	/// �ʏ�̏�ԂQ�𐶐�
	/// </summary>
	/// <param name="parent">�G�̃A�h���X</param>
	/// <param name="supplyPointManager">�G�̊Ǘ��҂̃A�h���X</param>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	/// <returns>�ʏ�̏�ԂQ�̃|�C���^</returns>
	virtual std::unique_ptr<IState> CreateEnemyMotion_02(
		Enemy* parent,
		EnemyManager* supplyPointManager,
		Player* respawnManager
	) = 0;

	/// <summary>
	/// ���S�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�G�̃A�h���X</param>
	/// <returns>���S�̏�Ԃ̃|�C���^</returns>
	virtual std::unique_ptr<IState> CreateEnemyKillMotion(
		Enemy* parent
	) = 0;
};

