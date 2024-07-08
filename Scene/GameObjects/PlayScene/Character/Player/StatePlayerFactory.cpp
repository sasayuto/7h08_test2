#include "pch.h"

#include"StatePlayerFactory.h"

#include"Scene/GameObjects/PlayScene/Character/Player/PlayerMotion.h"
#include"Scene/GameObjects/PlayScene/Character/Player/PlayerKillMotion.h"
#include"Scene/GameObjects/PlayScene/Character/Player/PlayerStopMotion.h"
#include"Scene/GameObjects/PlayScene/Character/Player/PlayerTurbMode.h"
#include"Scene/GameObjects/PlayScene/Character/Player/PlayerAvoidanceMotion.h"


std::unique_ptr<IState> StatePlayerFactory::CreateMotion(
	Player* player,
	BulletManager* bulletManager,
	RespawnManager* respawnManager,
	SupplyPointManager* supplyPointManager,
	EnemyManager* enemyManager,
	CoinManager* coinManager
)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<IState> playerMotion = std::make_unique<PlayerMotion>(player, bulletManager,respawnManager, supplyPointManager, enemyManager, coinManager);

	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(playerMotion);
}

std::unique_ptr<IState> StatePlayerFactory::CreateTurbMode(Player* parent, BulletManager* bulletManager, RespawnManager* respawnManager, SupplyPointManager* supplyPointManager, EnemyManager* enemyManager, CoinManager* coinManager)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<IState> createTurbMode = std::make_unique<PlayerTurbMode>(parent, bulletManager, respawnManager, supplyPointManager, enemyManager, coinManager);

	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(createTurbMode);
}

std::unique_ptr<IState> StatePlayerFactory::CreateAvoidanceMotion(Player* parent, RespawnManager* respawnManager, SupplyPointManager* supplyPointManager, CoinManager* coinManager)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<IState> playerMotion = std::make_unique<PlayerAvoidanceMotion>(parent,  respawnManager, supplyPointManager,  coinManager);

	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(playerMotion);
}

std::unique_ptr<IState> StatePlayerFactory::CreateStopMotion(
	Player* player,
	BulletManager* bulletManager,
	RespawnManager* respawnManager,
	SupplyPointManager* supplyPointManager,
	EnemyManager* enemyManager,
	CoinManager* coinManager
)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<IState> playerMotion = std::make_unique<PlayerStopMotion>(player, bulletManager,respawnManager, supplyPointManager, enemyManager, coinManager);

	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(playerMotion);
}

std::unique_ptr<IState> StatePlayerFactory::CreateKillMotion(Player* parent)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<IState> playerKillMotion = std::make_unique<KillMotion>(parent);

	//�H�̃C���X�^���X��Ԃ�
	return move(playerKillMotion);
}
