#include "pch.h"
#include"EnemyCustom_00.h"
#include"StateEnemyFactory.h"

using namespace DirectX;

EnemyCustom_00::EnemyCustom_00(const int& Hp, const int& Fuel, const int& offensivePower) :
	Enemy(Hp, Fuel, offensivePower),
	m_maxFuel(Fuel),
	m_maxHp(Hp),
	m_OffensivePower(offensivePower)
{

}

EnemyCustom_00::~EnemyCustom_00()
{
}

void EnemyCustom_00::Initialize(
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
	AddEnemyMotion(StateEnemyFactory::CreateEnemyMotion(this, enemyManager, player));

	//�G�̎��񂾓����̃C���X�^���X�𐶐�����
	AddEnemyKillMotion(StateEnemyFactory::CreateEnemyKillMotion(this));

	//�����̏�Ԃ��擾
	SetIState(GetEnemyMotion());

	//���Z�b�g����
	Reset();

	//���̃^�C�v���Z�b�g
	SetBulletType(Bullet::BulletType::Type1);
}

void EnemyCustom_00::Reset()
{
	GetCollider()->SetPosition(GetPosition());
	SetSurvival(true);
	SetFuel(m_maxFuel);
	SetHP(m_maxHp);
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
