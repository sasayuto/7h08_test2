#pragma once
#include "IStateAirshipFactory.h"

class Player;
class Airship;
class IStateAirship;

/// <summary>
/// StateEnemyFactory�̃N���X���`����
/// </summary>
class StateAirshipFactory : public IStateAirshipFactory
{
public:
	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�C�e���̃A�h���X</param>
	/// <param name="coinManager">�R�C���̃A�h���X</param>
	/// <returns>�ʏ�̏�Ԃ̃|�C���^</returns>
	static std::unique_ptr<IStateAirship> CreateAirshipMotion(
		Airship* enemy,
		Player* player
	);

	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�C�e���̃A�h���X</param>
	/// <param name="coinManager">�R�C���̃A�h���X</param>
	/// <returns>�ʏ�̏�Ԃ̃|�C���^</returns>
	static std::unique_ptr<IStateAirship> CreateAirshipMotion_01(
		Airship* enemy,
		Player* player
	);

	///// <summary>
	///// �ʏ�̏�Ԃ𐶐�
	///// </summary>
	///// <param name="parent">�e�̃A�C�e���̃A�h���X</param>
	///// <param name="respawnManager">���X�|�[���n�_�̃A�h���X</param>
	///// <param name="supplyPointManager">�A�C�e���̃A�h���X</param>
	///// <param name="enemyManager">�G�̃A�h���X</param>
	///// <param name="coinManager">�R�C���̃A�h���X</param>
	///// <returns>�ʏ�̏�Ԃ̃|�C���^</returns>
	//static std::unique_ptr<IState> CreateEnemyMotion_01(
	//	Enemy* enemy,
	//	EnemyManager* enemyManager,
	//	Player* player
	//);

	///// <summary>
	///// ���S�̏�Ԃ𐶐�
	///// </summary>
	///// <param name="player">�v���C���[�̃A�h���X</param>
	///// <returns>���S�̏�Ԃ̃|�C���^</returns>
	//static std::unique_ptr<IState> CreateEnemyKillMotion(
	//	Enemy* enemy);
};

