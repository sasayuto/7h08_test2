#pragma once
#include "IState.h"
#include "IStatePlayerFactory.h"

class RespawnManager;
class SupplyPointManager;
class EnemyManager;
class CoinManager;
class Player;

/// <summary>
/// StatePlayerFactory�̃N���X���`����
/// </summary>
class StatePlayerFactory : public IStatePlayerFactory
{
public:
	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="respawnManager">���̊Ǘ��҂̃A�h���X</param>
	/// <param name="respawnManager">���X�|�[���n�_�̊Ǘ��҂̃A�h���X</param>
	/// <param name="supplyPointManager">�A�C�e���̊Ǘ��҂̃A�h���X</param>
	/// <param name="enemyManager">�G�̊Ǘ��҂̃A�h���X</param>
	/// <param name="coinManager">�R�C���̊Ǘ��҂̃A�h���X</param>
	/// <returns>�ʏ�̏�Ԃ̃|�C���^</returns>
	static std::unique_ptr<IState> CreateMotion(
		Player* player,
		BulletManager* bulletManager,
		RespawnManager* respawnManager,
		SupplyPointManager* supplyPointManager,
		EnemyManager* enemyManager,
		CoinManager* coinManager
	);

	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="respawnManager">���̊Ǘ��҂̃A�h���X</param>
	/// <param name="respawnManager">���X�|�[���n�_�̊Ǘ��҂��A�h���X</param>
	/// <param name="supplyPointManager">�A�C�e���̊Ǘ��҂̃A�h���X</param>
	/// <param name="enemyManager">�G�̊Ǘ��҂̃A�h���X</param>
	/// <param name="coinManager">�R�C���̊Ǘ��҂̃A�h���X</param>
	/// <returns>�ʏ�̏�Ԃ̃|�C���^</returns>
	static std::unique_ptr<IState> CreateTurbMode(
		Player* parent,
		BulletManager* bulletManager,
		RespawnManager* respawnManager,
		SupplyPointManager* supplyPointManager,
		EnemyManager* enemyManager,
		CoinManager* coinManager
	);

	/// <summary>
	/// ����̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="respawnManager">���X�|�[���n�_�̊Ǘ��҂��A�h���X</param>
	/// <param name="supplyPointManager">�A�C�e���̊Ǘ��҂̃A�h���X</param>
	/// <param name="coinManager">�R�C���̊Ǘ��҂̃A�h���X</param>
	/// <returns>����̏�Ԃ̃|�C���^</returns>
	static std::unique_ptr<IState> CreateAvoidanceMotion(
		Player* parent,
		RespawnManager* respawnManager,
		SupplyPointManager* supplyPointManager,
		CoinManager* coinManager
	);

	/// <summary>
	/// �X�g�b�v�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="respawnManager">���̊Ǘ��҂̃A�h���X</param>
	/// <param name="respawnManager">���X�|�[���n�_�̊Ǘ��҂̃A�h���X</param>
	/// <param name="supplyPointManager">�A�C�e���̊Ǘ��҂̃A�h���X</param>
	/// <param name="enemyManager">�G�̊Ǘ��҂̃A�h���X</param>
	/// <param name="coinManager">�R�C���̊Ǘ��҂̃A�h���X</param>
	/// <returns>�X�b�g�v�̏�Ԃ̃|�C���^</returns>
	static std::unique_ptr<IState> CreateStopMotion(
		Player* player,
		BulletManager* bulletManager,
		RespawnManager* respawnManager,
		SupplyPointManager* supplyPointManager,
		EnemyManager* enemyManager,
		CoinManager* coinManager
	);

	///// <summary>
	///// ����̏�Ԃ𐶐�
	///// </summary>
	///// <param name="parent">�e�̃A�h���X</param>
	///// <param name="respawnManager">���X�|�[���n�_�̃A�h���X</param>
	///// <param name="supplyPointManager">�A�C�e���̃A�h���X</param>
	///// <param name="enemyManager">�G�̃A�h���X</param>
	///// <param name="coinManager">�R�C���̃A�h���X</param>
	///// <returns>����̏�Ԃ̃|�C���^</returns>
	//static std::unique_ptr<IState> CreateStopMotion(
	//	Player* player,
	//	RespawnManager* respawnManager,
	//	SupplyPointManager* supplyPointManager,
	//	EnemyManager* enemyManager,
	//	CoinManager* coinManager
	//);

	/// <summary>
	/// ���S�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="player">�e�̃A�h���X</param>
	/// <returns>���S�̏�Ԃ̃|�C���^</returns>
	static std::unique_ptr<IState> CreateKillMotion(
		Player* parent);
};

