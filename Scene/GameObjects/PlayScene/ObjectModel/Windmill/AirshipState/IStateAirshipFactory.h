#pragma once
#include <combaseapi.h>
class Player;
class Airship;
class IStateAirship;

/// <summary>
/// IStateEnemyFactory�C���^�[�t�F�C�X�̃N���X���`����
/// </summary>
interface  IStateAirshipFactory
{
	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="coinManager">�R�C���̃A�h���X</param>
	/// <returns>�ʏ�̏�Ԃ̃|�C���^</returns>
	virtual std::unique_ptr<IStateAirship> CreateAirshipMotion(
		Airship* parent,
		Player* respawnManager
	) = 0;
	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="coinManager">�R�C���̃A�h���X</param>
	/// <returns>�ʏ�̏�Ԃ̃|�C���^</returns>
	virtual std::unique_ptr<IStateAirship> CreateAirshipMotion_01(
		Airship* parent,
		Player* respawnManager
	) = 0;

	///// <summary>
	///// ���S�̏�Ԃ𐶐�
	///// </summary>
	///// <param name="parent">�G�̃A�h���X</param>
	///// <returns>���S�̏�Ԃ̃|�C���^</returns>
	//virtual std::unique_ptr<IState> CreateEnemyKillMotion(
	//	Enemy* parent
	//) = 0;
};

