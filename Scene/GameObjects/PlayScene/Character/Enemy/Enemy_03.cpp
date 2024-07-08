#include "pch.h"
#include"Enemy_03.h"
#include"StateEnemyFactory.h"

using namespace DirectX;

Enemy_03::Enemy_03() :
	Enemy(ENEMY_MAX_HP, ENEMY_MAX_FUEL, ENEMY_OFFENSIVE_POWER)
{

}

Enemy_03::~Enemy_03()
{
}

void Enemy_03::Initialize(
	BulletManager* bulletManager,
	EnemyManager* enemyManager,
	ObjectsManager* objectsManager,
	Player* player,
	AirshipManager* airshipManager,
	WindmillManager* windmillManager,
	Floor* floor,
	SandstormManager* sandstormManager,
	FloorManager_01* floorManager_01,
	BigBrickWallManager* bigBrickWallManager
)
{
	//基底クラスの初期化
	Enemy::Initialize(
		bulletManager,
		enemyManager,
		objectsManager,
		player,
		airshipManager,
		windmillManager,
		floor,
		sandstormManager,
		floorManager_01,
		bigBrickWallManager
	);

	//敵の通常の動きのインスタンスを生成する
	AddEnemyMotion(StateEnemyFactory::CreateEnemyMotion_02(this, enemyManager, player));

	//敵の死んだ動きのインスタンスを生成する
	AddEnemyKillMotion(StateEnemyFactory::CreateEnemyKillMotion(this));

	//動きの状態を取得
	SetIState(GetEnemyMotion());

	//リセットする
	Reset();

	//球のタイプをセット
	SetBulletType(Bullet::BulletType::Type1);
}

void Enemy_03::Reset()
{
	//当たり判定に位置と半径をセット
	GetCollider()->SetPosition(GetPosition());
	SetSurvival(true);
	SetFuel(ENEMY_MAX_FUEL);
	SetHP(ENEMY_MAX_HP);
	SetBulletCoolTime(0.0f);
	SetReflectionVector(DirectX::SimpleMath::Vector3::Zero);
	SetGravity(0.0f);
	SetAngle(DirectX::SimpleMath::Vector3::Zero);
	SetRotate(DirectX::SimpleMath::Quaternion::Identity);
	SetSpeed(0);
	SetVelcity(DirectX::SimpleMath::Vector3::Zero);
	//
	SetIState(GetEnemyMotion());
}
