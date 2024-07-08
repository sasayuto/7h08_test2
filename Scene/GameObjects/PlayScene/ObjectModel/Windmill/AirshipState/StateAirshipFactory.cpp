#include "pch.h"

#include"StateAirshipFactory.h"

#include"AirshipMotion.h"
#include"AirshipMotion_01.h"

std::unique_ptr<IStateAirship> StateAirshipFactory::CreateAirshipMotion(
	Airship* enemy,
	Player* player
)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<IStateAirship> enemyMotion = std::make_unique<AirshipMotion>(enemy, player);

	//�H�̃C���X�^���X��Ԃ�
	return move(enemyMotion);
}

std::unique_ptr<IStateAirship> StateAirshipFactory::CreateAirshipMotion_01(
	Airship* enemy,
	Player* player
)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<IStateAirship> enemyMotion = std::make_unique<AirshipMotion_01>(enemy, player);

	//�H�̃C���X�^���X��Ԃ�
	return move(enemyMotion);
}

