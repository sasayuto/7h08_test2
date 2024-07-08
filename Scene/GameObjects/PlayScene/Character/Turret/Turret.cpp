#include "pch.h"
#include"Turret.h"
#include <math.h>
#include<random>

#include"Scene/GameObjects/PlayScene/Character/Airship/AirshipManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Windmill/WindmillManager.h"
#include"Scene/GameObjects/PlayScene/Sandstorm/SandstormManager.h"
#include"TurrretParts/TurretPartFactory.h"


using namespace DirectX;

Turret::Turret(const int& Hp,const int& offensivePower) :
	m_survival(false),
	m_pCurrentState(nullptr),
	m_turretKillMotion(nullptr),
	m_turretMotion(nullptr),
	m_position(SimpleMath::Vector3::Zero),
	m_HP(Hp),
	m_offensivePower(offensivePower),
	m_pBulletManager(nullptr),
	m_reflectionVector(DirectX::SimpleMath::Vector3::Zero),
	m_rotate(SimpleMath::Quaternion::Identity)
{
}

Turret::~Turret()
{
}

void Turret::Initialize(
	BulletManager* bulletManager,
	TurretManager* turretManager,
	AirshipManager* airshipManager,
	Floor* floor,
	SandstormManager* sandstormManager
)
{
	turretManager;
	//�����蔻��𐶐�
	m_collider = std::make_unique<Collider::Sphere>();

	m_pBulletManager = bulletManager;

	m_pAirshipManager = airshipManager;

	m_pFloor = floor;

	m_pSandstormManager = sandstormManager;

	// �v���C���[�Ƀv���y����ǉ�����
	AddParts(TurretPartFactory::CreateTurretBase(m_pBulletManager,nullptr, m_position, m_rotate));
}

void Turret::Update(const float& elapsedTime)
{
	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	m_collider->SetPosition(m_position);

	//�O���Ă��悢
	//�y���̂��߃v���C���[�̎��E���A�P�O�O���[�g���ȓ��Ȃ瓖���蔻����Ƃ�
		//���Ƃ̓����蔻��
		if (m_pBulletManager)
			m_pBulletManager->CheckHitDamegeObjects(this, Bullet::BulletParent::EnemyBullet);

		//if (m_pObjectsManager)
		//	m_pObjectsManager->CheckHitTurret(this);

		//if(m_pTreeManager)
		//	m_pTreeManager->CheckHitTurret(this);

		//if (m_pAirshipManager)
		//	m_pAirshipManager->CheckHitTurret(this);

		//if (m_pWindmillManager)
		//	m_pWindmillManager->CheckHitTurret(this);

		//if (m_pFloor)
		//	m_pFloor->CheckHitTurret(this);

		//if (m_pSandstormManager)
		//	m_pSandstormManager->CheckHitTurret(this);
	
	//���݂̏�Ԃ̍X�V
	m_pCurrentState->Update(elapsedTime);
}

void Turret::Render()
{
	m_pCurrentState->Render();
}

void Turret::Finalize()
{
	m_pCurrentState->Finalize();
}

void Turret::Damage(const int& damage)
{
	SetHP(GetHP() - damage);
}

void Turret::SetpositionRandam(const float& min,const float& max)
{
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> distance(min, max);

	float x = static_cast<float>(distance(engine));
	float z = static_cast<float>(distance(engine));

	m_position = SimpleMath::Vector3(x, 0.0f, z);
	m_rotate = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, x);
}

void Turret::Reset()
{
}

void Turret::PartsRender()
{
	for (auto& part : m_parts)
	{
		//�p�[�c���X�V����
		part->Render();
	}
}
