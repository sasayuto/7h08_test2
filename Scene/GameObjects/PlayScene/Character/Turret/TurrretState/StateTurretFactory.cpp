#include "pch.h"

#include"StateTurretFactory.h"
#include"TurretKillMotion.h"
#include"TurretMotion_01.h"
std::unique_ptr<ITurretState> StateTurretFactory::CreateTurretMotion(Turret* parent, TurretManager* turretManager)
{
	//羽のインスタンスを生成する
	std::unique_ptr<ITurretState> turretMotion_01 = std::make_unique<TurretMotion_01>(parent, turretManager);

	//羽のインスタンスを返す
	return move(turretMotion_01);
}

std::unique_ptr<ITurretState> StateTurretFactory::CreateTurretKillMotion(Turret* parent)
{
	//羽のインスタンスを生成する
	std::unique_ptr<ITurretState> turretMotionKill = std::make_unique<TurretKillMotion>(parent);

	//羽のインスタンスを返す
	return move(turretMotionKill);
}
