#include "pch.h"

#include"StateEnemyFactory.h"

#include"Scene/GameObjects/PlayScene/Character/Enemy/EnemyKillMotion.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/EnemyMotion_01.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/EnemyMotion_02.h"


std::unique_ptr<IState> StateEnemyFactory::CreateEnemyMotion(
	Enemy* enemy,
	EnemyManager* enemyManager,
	Player* player
)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<IState> enemyMotion = std::make_unique<EnemyMotion>(enemy, enemyManager, player);

	//������
	enemyMotion->Initialize();

	//�H�̃C���X�^���X��Ԃ�
	return move(enemyMotion);
}

std::unique_ptr<IState> StateEnemyFactory::CreateEnemyMotion_01(
	Enemy* enemy,
	EnemyManager* enemyManager,
	Player* player
)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<IState> enemyMotion = std::make_unique<EnemyMotion_01>(enemy, enemyManager, player);

	//������
	enemyMotion->Initialize();

	//�H�̃C���X�^���X��Ԃ�
	return move(enemyMotion);
}

std::unique_ptr<IState> StateEnemyFactory::CreateEnemyMotion_02(
	Enemy* enemy,
	EnemyManager* enemyManager,
	Player* player
)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<IState> enemyMotion = std::make_unique<EnemyMotion_02>(enemy, enemyManager, player);

	//������
	enemyMotion->Initialize();

	//�H�̃C���X�^���X��Ԃ�
	return move(enemyMotion);
}

std::unique_ptr<IState> StateEnemyFactory::CreateEnemyKillMotion(Enemy* enemy)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<IState> enemyKillMotion = std::make_unique<EnemyKillMotion>(enemy);

	//������
	enemyKillMotion->Initialize();

	//�H�̃C���X�^���X��Ԃ�
	return move(enemyKillMotion);
}
