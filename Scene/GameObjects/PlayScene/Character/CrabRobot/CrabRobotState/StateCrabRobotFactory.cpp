#include "pch.h"

#include"StateCrabRobotFactory.h"

#include"CrabRobotMotion_01.h"
#include"CrabRobotKillMotion.h"
std::unique_ptr<ICrabRobotState> StateCrabRobotFactory::CreateCrabRobotMotion(CrabRobot* crabRobot, CrabRobotManager* crabRobotManager)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<ICrabRobotState> turretMotion_01 = std::make_unique<CrabRobotMotion_01>(crabRobot, crabRobotManager);

	//�H�̃C���X�^���X��Ԃ�
	return move(turretMotion_01);
}

std::unique_ptr<ICrabRobotState> StateCrabRobotFactory::CreateCrabRobotKillMotion(CrabRobot* crabRobot)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<ICrabRobotState> turretMotion_01 = std::make_unique<CrabRobotKillMotion>(crabRobot);

	//�H�̃C���X�^���X��Ԃ�
	return move(turretMotion_01);
}
