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

	//当たり判定に位置と半径をセット
	GetCollider()->SetPosition(GetPosition()+DirectX::SimpleMath::Vector3(0,15,0));

	GetCollider()->SetRadius(140);

	//敵の通常の動きのインスタンスを生成する
	AddTurrertMotion(StateCrabRobotFactory::CreateCrabRobotMotion(this, crabRobotManager));

	////敵の死んだ動きのインスタンスを生成する
	AddTurretKillMotion(StateCrabRobotFactory::CreateCrabRobotKillMotion(this));

	Reset();

	//動きの状態を取得
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
