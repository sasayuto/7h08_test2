#include "pch.h"
#include"Enemy.h"
#include"StateEnemyFactory.h"
#include <math.h>
#include<random>

#include"Scene/GameObjects/PlayScene/Character/Airship/AirshipManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Windmill/WindmillManager.h"
#include"Scene/GameObjects/PlayScene/Sandstorm/SandstormManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Objects/Walls/BigBrickWall/BigBrickWallManager.h"
#include"../Player/PlayerPartFactory.h"


using namespace DirectX;

Enemy::Enemy(const int& Hp, const int& Fuel, const int& offensivePower) :
	m_survival(false),
	m_pCurrentState(nullptr),
	m_enemyKillMotion(nullptr),
	m_enemyMotion(nullptr),
	m_position(SimpleMath::Vector3::Zero),
	m_velcity(SimpleMath::Vector3::Zero),
	m_rotate(SimpleMath::Quaternion::Identity),
	m_bulletCoolTime(),
	m_HP(Hp),
	m_fuel(Fuel),
	m_offensivePower(offensivePower),
	m_speed(),
	m_angle(SimpleMath::Vector3::Zero),
	m_bulletParent(Bullet::BulletParent::None),
	m_bulletType(Bullet::BulletType::None),
	m_pBulletManager(nullptr),
	m_gravity(),
	m_reflectionVector(DirectX::SimpleMath::Vector3::Zero)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize(
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
	player;
	enemyManager;
	// �v���C���[�Ƀv���y����ǉ�����
	AddParts(PlayerPartFactory::CreatePlayerBody(nullptr, m_position, m_rotate));

	//�����蔻��𐶐�
	m_collider = std::make_unique<Collider::Sphere>();

	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	m_collider->SetPosition(m_position);

	//���a���Z�b�g
	m_collider->SetRadius(1);

	//�ǂ̊Ǘ��҂̃|�C���^���擾
	m_pBigBrickWallManager = bigBrickWallManager;

	//���̊Ǘ��҂̃|�C���^���擾
	m_pFloorManager_01 = floorManager_01;

	//���̊Ǘ��҂̃|�C���^���擾
	m_pBulletManager = bulletManager;

	//�I�u�W�F�N�g�̊Ǘ��҂̃|�C���^���擾
	m_pObjectsManager = objectsManager;

	//��s�D�̊Ǘ��҂̃|�C���^���擾
	m_pAirshipManager = airshipManager;

	//���Ԃ̊Ǘ��҂̃|�C���^���擾
	m_pWindmillManager = windmillManager;

	//���̂̃|�C���^���擾
	m_pFloor = floor;

	//�����̊Ǘ��҂̃|�C���^���擾
	m_pSandstormManager = sandstormManager;

	//�G�������Ă���
	SetSurvival(true);

	//���ۗ̕L�҂��Z�b�g
	SetBulletParent(Bullet::BulletParent::EnemyBullet);
}

void Enemy::Update(const float& elapsedTime)
{
	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	m_collider->SetPosition(m_position);

	//�O���Ă��悢
	//�y���̂��߃v���C���[�̎��E���A�P�O�O���[�g���ȓ��Ȃ瓖���蔻����Ƃ�
	if (!Draw::GetInstance()->UpdateDistance(m_position, 100))
	{
		//���Ƃ̓����蔻��
		m_pBulletManager->CheckHitDamegeObjects(this, Bullet::BulletParent::EnemyBullet);

		if (m_pObjectsManager)
			m_pObjectsManager->CheckHitEnemy(this);

		if (m_pAirshipManager)
			m_pAirshipManager->CheckHitEnemy(this);

		if (m_pWindmillManager)
			m_pWindmillManager->CheckHitEnemy(this);

		if (m_pFloor)
			m_pFloor->CheckHitEnemy(this);

		if (m_pSandstormManager)
			m_pSandstormManager->CheckHitEnemy(this);

		if (m_pFloorManager_01)
			m_pFloorManager_01->CheckHitEnemy(this);

		if (m_pBigBrickWallManager)
			m_pBigBrickWallManager->CheckHitEnemy(this);
	}
	//���݂̏�Ԃ̍X�V
	m_pCurrentState->Update(elapsedTime);
}

void Enemy::Render()
{
	//���݂̏�Ԃ̕`��
	m_pCurrentState->Render();
}

void Enemy::RenderShadowTex()
{
	for (auto& parts : m_parts)
	{
		// �p�[�c���X�V����
		parts->RenderShadowTex();
	}
}

void Enemy::Finalize()
{
	//���݂̏�Ԃ̌�n��
	m_pCurrentState->Finalize();
}

void Enemy::Damage(const int& damage)
{
	//�_���[�W����
	SetHP(GetHP() - damage);
}

void Enemy::SetpositionRandam(const float& min,const float& max)
{
	//����
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> distance(min, max);

	float x = static_cast<float>(distance(engine));
	float y = fabs(static_cast<float>(distance(engine)));
	float z = static_cast<float>(distance(engine));

	m_position = SimpleMath::Vector3(x, y, z);

}

void Enemy::Reset()
{
}

void Enemy::Shot(const float& maxBulletCoolTime)
{
	//���̃N�[���^�C����
	if (m_bulletCoolTime == 0.0f)
	{
		//������
		m_pBulletManager->Shot(m_bulletType, m_bulletParent, m_position, m_rotate);
	
		//�N�[���^�C�����Z�b�g
		m_bulletCoolTime = maxBulletCoolTime;
	}
}

void Enemy::PartsInitialize()
{
	//�p�[�c�̏�����
	for (auto& parts : m_parts)
	{
		// �p�[�c��������
		parts->Initialize(m_reflectionVector);
	}
}

void Enemy::PartsUpdate()
{
	//�p�[�c�̍X�V
	for (auto& parts : m_parts)
	{
		// �p�[�c���X�V����
		parts->Update(m_position, m_rotate);
	}
}

void Enemy::PartsExplosion()
{
	//�p�[�c�̔�������
	for (auto& parts : m_parts)
	{
		// �p�[�c���X�V����
		parts->Explosion();
	}
}

void Enemy::PartsMotion()
{
	//�p�[�c�̔R���ɂ�����铮��
	for (auto& parts : m_parts)
	{
		// �p�[�c���X�V����
		parts->Speed();
	}
}

void Enemy::PartsCollision()
{
	//for (auto& playerPart : m_PlayerPropellerParts)
	//{
	//	// �p�[�c���X�V����
	//	playerPart->Collision();
	//}

}

void Enemy::PartsRender()
{
	//�p�[�c�̕`��
	for (auto& part : m_parts)
	{
		//�p�[�c���X�V����
		part->Render();
	}
}
