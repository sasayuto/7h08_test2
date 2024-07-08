#include "pch.h"
#include"AirshipCustom_00.h"
#include"AirshipState/StateAirshipFactory.h"
using namespace DirectX;

AirshipCustom_00::AirshipCustom_00(const int& Hp, const int& Fuel, const int& offensivePower) :
	Airship(Hp, Fuel, offensivePower),
	m_maxFuel(),
	m_maxHp(Hp),
	m_OffensivePower(offensivePower)
{

}

AirshipCustom_00::~AirshipCustom_00()
{
}

void AirshipCustom_00::Initialize(
	BulletManager* bulletManager,
	ObjectsManager* objectsManager,
	Player* player
)
{
	//���N���X�̏�����
	Airship::Initialize(bulletManager, objectsManager, player);

	//�G�̒ʏ�̓����̃C���X�^���X�𐶐�����
	AddEnemyMotion(StateAirshipFactory::CreateAirshipMotion_01(this, player));

	////�G�̎��񂾓����̃C���X�^���X�𐶐�����
	//AddEnemyKillMotion(StateAirshipFactory::CreateEnemyKillMotion(this));

	//�����̏�Ԃ��擾
	SetIState(GetEnemyMotion());
	Reset();

}

void AirshipCustom_00::Reset()
{
	//������
	SetFuel(m_maxFuel);
	SetHP(m_maxHp);
	GetCollider()->SetPosition(GetPosition());
	SetSurvival(true);
	SetBulletCoolTime(0.0f);
	SetGravity(0.0f);
	SetAngle(DirectX::SimpleMath::Vector3::Zero);
	SetRotate(DirectX::SimpleMath::Quaternion::Identity);
	SetVelcity(DirectX::SimpleMath::Vector3::Zero);
	SetIState(GetEnemyMotion());
}
