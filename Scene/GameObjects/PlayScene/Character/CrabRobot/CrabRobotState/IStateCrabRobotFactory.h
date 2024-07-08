#pragma once
#include <combaseapi.h>
class ICrabRobotState;
class CrabRobot;
class CrabRobotManager;

/// <summary>
/// IStateCrabRobotFactoryインターフェイスのクラスを定義する
/// </summary>
interface  IStateCrabRobotFactory
{
	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="coinManager">コインのアドレス</param>
	/// <returns>通常の状態のポインタ</returns>
	virtual std::unique_ptr<ICrabRobotState> CreateCrabRobotMotion(
		const CrabRobot* crabRobot,
		const CrabRobotManager* crabRobotManager
	) = 0;

	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <returns>通常の状態のポインタ</returns>
	virtual std::unique_ptr<ICrabRobotState> CreateCrabRobotKillMotion(
		const CrabRobot* crabRobot
	) = 0;

};

