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

	//当たり判定に位置と半径をセット
	GetCollider()->SetPosition(GetPosition()+DirectX::SimpleMath::Vector3(0,15,0));

	GetCollider()->SetRadius(140);

	//敵の通常の動きのインスタンスを生成する
	AddTurrertMotion(StateTurretFactory::CreateTurretMotion(this,turretManager));

	////敵の死んだ動きのインスタンスを生成する
	AddTurretKillMotion(StateTurretFactory::CreateTurretKillMotion(this));

	Reset();

	//動きの状態を取得
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
