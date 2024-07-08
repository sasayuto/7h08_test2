#include "pch.h"

#include"StateCrabRobotFactory.h"

#include"CrabRobotMotion_01.h"
#include"CrabRobotKillMotion.h"
std::unique_ptr<ICrabRobotState> StateCrabRobotFactory::CreateCrabRobotMotion(CrabRobot* crabRobot, CrabRobotManager* crabRobotManager)
{
	//羽のインスタンスを生成する
	std::unique_ptr<ICrabRobotState> turretMotion_01 = std::make_unique<CrabRobotMotion_01>(crabRobot, crabRobotManager);

	//羽のインスタンスを返す
	return move(turretMotion_01);
}

std::unique_ptr<ICrabRobotState> StateCrabRobotFactory::CreateCrabRobotKillMotion(CrabRobot* crabRobot)
{
	//羽のインスタンスを生成する
	std::unique_ptr<ICrabRobotState> turretMotion_01 = std::make_unique<CrabRobotKillMotion>(crabRobot);

	//羽のインスタンスを返す
	return move(turretMotion_01);
}
