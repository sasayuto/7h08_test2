#include "pch.h"
#include"Enemy_01.h"
#include"StateEnemyFactory.h"

using namespace DirectX;

Enemy_01::Enemy_01() :
	Enemy(ENEMY_MAX_HP, ENEMY_MAX_FUEL, ENEMY_OFFENSIVE_POWER)
{

}

Enemy_01::~Enemy_01()
{
}

void Enemy_01::Initialize(
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
	//���N���X�̏�����
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

	//�G�̒ʏ�̓����̃C���X�^���X�𐶐�����
	AddEnemyMotion(StateEnemyFactory::CreateEnemyMotion_01(this, enemyManager, player));

	//�G�̎��񂾓����̃C���X�^���X�𐶐�����
	AddEnemyKillMotion(StateEnemyFactory::CreateEnemyKillMotion(this));

	//�����̏�Ԃ�������
	SetIState(GetEnemyMotion());

	//���Z�b�g����
	Reset();

	//���̃^�C�v���Z�b�g
	SetBulletType(Bullet::BulletType::Type1);
}

void Enemy_01::Reset()
{
	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	GetCollider()->SetPosition(GetPosition());
	SetSurvival(true);
	SetFuel(ENEMY_MAX_FUEL);
	SetHP(ENEMY_MAX_HP);
	SetBulletCoolTime(0.0f);
	SetReflectionVector(DirectX::SimpleMath::Vector3::Zero);
	SetGravity(0.0f);
	SetAngle(DirectX::SimpleMath::Vector3::Zero);
	SetRotate(DirectX::SimpleMath::Quaternion::Identity);
	SetVelcity(DirectX::SimpleMath::Vector3::Zero);
	SetIState(GetEnemyMotion());
}

