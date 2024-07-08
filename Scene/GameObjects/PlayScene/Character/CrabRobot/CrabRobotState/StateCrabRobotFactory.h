#pragma once
#include "IStateCrabRobotFactory.h"

class ICrabRobotState;
class CrabRobot;
class CrabRobotManager;

/// <summary>
/// StateCrabRobotFactory�̃N���X���`����
/// </summary>
class StateCrabRobotFactory : public IStateCrabRobotFactory
{
public:
	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="coinManager">�R�C���̃A�h���X</param>
	/// <returns>�ʏ�̏�Ԃ̃|�C���^</returns>
	static std::unique_ptr<ICrabRobotState> CreateCrabRobotMotion(
		CrabRobot* crabRobot,
		CrabRobotManager* crabRobotManager
	);

	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <returns>�ʏ�̏�Ԃ̃|�C���^</returns>
	static std::unique_ptr<ICrabRobotState> CreateCrabRobotKillMotion(
		CrabRobot* crabRobot
	);
};

