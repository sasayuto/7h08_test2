#include "pch.h"
#include"TurretCustom_00.h"
#include"TurrretState/StateTurretFactory.h"
using namespace DirectX;

TurretCustom_00::TurretCustom_00(const int& Hp, const int& offensivePower) :
	Turret(Hp, offensivePower),
	m_maxHp(Hp),
	m_OffensivePower(offensivePower)
{

}

TurretCustom_00::~TurretCustom_00()
{
}

void TurretCustom_00::Initialize(
	BulletManager* bulletManager,
	TurretManager* turretManager,
	AirshipManager* airshipManager,
	Floor* floor,
	SandstormManager* sandstormManager
)
{
	Turret::Initialize(bulletManager, turretManager,airshipManager, floor, sandstormManager);

	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	GetCollider()->SetPosition(GetPosition()+DirectX::SimpleMath::Vector3(0,15,0));

	GetCollider()->SetRadius(140);

	//�G�̒ʏ�̓����̃C���X�^���X�𐶐�����
	AddTurrertMotion(StateTurretFactory::CreateTurretMotion(this,turretManager));

	////�G�̎��񂾓����̃C���X�^���X�𐶐�����
	AddTurretKillMotion(StateTurretFactory::CreateTurretKillMotion(this));

	Reset();

	//�����̏�Ԃ��擾
	SetIState(GetTurretMotion());
	GetTurretMotion()->Initialize();
}

void TurretCustom_00::Reset()
{
	GetCollider()->SetPosition(GetPosition());
	SetSurvival(true);
	SetHP(m_maxHp);
	SetReflectionVector(DirectX::SimpleMath::Vector3::Zero);
	SetRotate(DirectX::SimpleMath::Quaternion::Identity);
	SetIState(GetTurretMotion());
	
}
