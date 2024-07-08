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
	//基底クラスの初期化
	Airship::Initialize(bulletManager, objectsManager, player);

	//敵の通常の動きのインスタンスを生成する
	AddEnemyMotion(StateAirshipFactory::CreateAirshipMotion_01(this, player));

	////敵の死んだ動きのインスタンスを生成する
	//AddEnemyKillMotion(StateAirshipFactory::CreateEnemyKillMotion(this));

	//動きの状態を取得
	SetIState(GetEnemyMotion());
	Reset();

}

void AirshipCustom_00::Reset()
{
	//初期化
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
