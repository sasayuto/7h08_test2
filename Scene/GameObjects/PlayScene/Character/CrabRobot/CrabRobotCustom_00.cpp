#include "pch.h"
#include"CrabRobotCustom_00.h"
#include"CrabRobotState/StateCrabRobotFactory.h"
using namespace DirectX;

CrabRobotCustom_00::CrabRobotCustom_00(const int& Hp, const int& offensivePower) :
	CrabRobot(Hp, offensivePower),
	m_maxHp(Hp),
	m_OffensivePower(offensivePower)
{

}

CrabRobotCustom_00::~CrabRobotCustom_00()
{
}

void CrabRobotCustom_00::Initialize(
	BulletManager* bulletManager,
	CrabRobotManager* crabRobotManager,
	AirshipManager* airshipManager,
	Floor* floor,
	SandstormManager* sandstormManager
)
{
	CrabRobot::Initialize(bulletManager, crabRobotManager,airshipManager, floor, sandstormManager);

	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	GetCollider()->SetPosition(GetPosition()+DirectX::SimpleMath::Vector3(0,15,0));

	GetCollider()->SetRadius(140);

	//�G�̒ʏ�̓����̃C���X�^���X�𐶐�����
	AddTurrertMotion(StateCrabRobotFactory::CreateCrabRobotMotion(this, crabRobotManager));

	////�G�̎��񂾓����̃C���X�^���X�𐶐�����
	AddTurretKillMotion(StateCrabRobotFactory::CreateCrabRobotKillMotion(this));

	Reset();

	//�����̏�Ԃ��擾
	SetIState(GetTurretMotion());
	GetTurretMotion()->Initialize();
}

void CrabRobotCustom_00::Reset()
{
	GetCollider()->SetPosition(GetPosition());
	SetSurvival(true);
	SetHP(m_maxHp);
	SetReflectionVector(DirectX::SimpleMath::Vector3::Zero);
	SetRotate(DirectX::SimpleMath::Quaternion::Identity);
	SetIState(GetTurretMotion());
	
}
