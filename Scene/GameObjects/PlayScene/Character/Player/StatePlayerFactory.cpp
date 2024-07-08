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
	//プロペラのインスタンスを生成する
	std::unique_ptr<IState> playerMotion = std::make_unique<PlayerMotion>(player, bulletManager,respawnManager, supplyPointManager, enemyManager, coinManager);

	//プロペラののインスタンスを返す
	return move(playerMotion);
}

std::unique_ptr<IState> StatePlayerFactory::CreateTurbMode(Player* parent, BulletManager* bulletManager, RespawnManager* respawnManager, SupplyPointManager* supplyPointManager, EnemyManager* enemyManager, CoinManager* coinManager)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<IState> createTurbMode = std::make_unique<PlayerTurbMode>(parent, bulletManager, respawnManager, supplyPointManager, enemyManager, coinManager);

	//プロペラののインスタンスを返す
	return move(createTurbMode);
}

std::unique_ptr<IState> StatePlayerFactory::CreateAvoidanceMotion(Player* parent, RespawnManager* respawnManager, SupplyPointManager* supplyPointManager, CoinManager* coinManager)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<IState> playerMotion = std::make_unique<PlayerAvoidanceMotion>(parent,  respawnManager, supplyPointManager,  coinManager);

	//プロペラののインスタンスを返す
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
	//プロペラのインスタンスを生成する
	std::unique_ptr<IState> playerMotion = std::make_unique<PlayerStopMotion>(player, bulletManager,respawnManager, supplyPointManager, enemyManager, coinManager);

	//プロペラののインスタンスを返す
	return move(playerMotion);
}

std::unique_ptr<IState> StatePlayerFactory::CreateKillMotion(Player* parent)
{
	//羽のインスタンスを生成する
	std::unique_ptr<IState> playerKillMotion = std::make_unique<KillMotion>(parent);

	//羽のインスタンスを返す
	return move(playerKillMotion);
}
