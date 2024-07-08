#include "pch.h"

#include"StateTurretFactory.h"
#include"TurretKillMotion.h"
#include"TurretMotion_01.h"
std::unique_ptr<ITurretState> StateTurretFactory::CreateTurretMotion(Turret* parent, TurretManager* turretManager)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<ITurretState> turretMotion_01 = std::make_unique<TurretMotion_01>(parent, turretManager);

	//�H�̃C���X�^���X��Ԃ�
	return move(turretMotion_01);
}

std::unique_ptr<ITurretState> StateTurretFactory::CreateTurretKillMotion(Turret* parent)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<ITurretState> turretMotionKill = std::make_unique<TurretKillMotion>(parent);

	//�H�̃C���X�^���X��Ԃ�
	return move(turretMotionKill);
}
