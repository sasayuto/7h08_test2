#pragma once
#include <combaseapi.h>
class ICrabRobotState;
class CrabRobot;
class CrabRobotManager;

/// <summary>
/// IStateCrabRobotFactory�C���^�[�t�F�C�X�̃N���X���`����
/// </summary>
interface  IStateCrabRobotFactory
{
	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="coinManager">�R�C���̃A�h���X</param>
	/// <returns>�ʏ�̏�Ԃ̃|�C���^</returns>
	virtual std::unique_ptr<ICrabRobotState> CreateCrabRobotMotion(
		const CrabRobot* crabRobot,
		const CrabRobotManager* crabRobotManager
	) = 0;

	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <returns>�ʏ�̏�Ԃ̃|�C���^</returns>
	virtual std::unique_ptr<ICrabRobotState> CreateCrabRobotKillMotion(
		const CrabRobot* crabRobot
	) = 0;

};

