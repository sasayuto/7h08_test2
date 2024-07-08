#pragma once
#include "IStateCrabRobotFactory.h"

class ICrabRobotState;
class CrabRobot;
class CrabRobotManager;

/// <summary>
/// StateCrabRobotFactoryのクラスを定義する
/// </summary>
class StateCrabRobotFactory : public IStateCrabRobotFactory
{
public:
	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="coinManager">コインのアドレス</param>
	/// <returns>通常の状態のポインタ</returns>
	static std::unique_ptr<ICrabRobotState> CreateCrabRobotMotion(
		CrabRobot* crabRobot,
		CrabRobotManager* crabRobotManager
	);

	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <returns>通常の状態のポインタ</returns>
	static std::unique_ptr<ICrabRobotState> CreateCrabRobotKillMotion(
		CrabRobot* crabRobot
	);
};

