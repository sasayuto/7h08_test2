#include "pch.h"
#include"CrabRobot.h"
#include <math.h>
#include<random>
#include"CrabRobotParts/CrabRobotPartFactory.h"

#include"Scene/GameObjects/PlayScene/Character/Airship/AirshipManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Windmill/WindmillManager.h"
#include"Scene/GameObjects/PlayScene/Sandstorm/SandstormManager.h"


using namespace DirectX;

CrabRobot::CrabRobot(const int& Hp,const int& offensivePower) :
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

CrabRobot::~CrabRobot()
{
}

void CrabRobot::Initialize(
	BulletManager* bulletManager,
	CrabRobotManager* crabRobotManager,
	AirshipManager* airshipManager,
	Floor* floor,
	SandstormManager* sandstormManager
)
{
	crabRobotManager;
	//当たり判定を生成
	m_collider = std::make_unique<Collider::Sphere>();

	m_pBulletManager = bulletManager;

	m_pAirshipManager = airshipManager;

	m_pFloor = floor;

	m_pSandstormManager = sandstormManager;

	// プレイヤーにプロペラを追加する
	AddParts(CrabRobotPartFactory::CreateCrabRobotHead(nullptr, m_position, m_rotate));
}

void CrabRobot::Update(const float& elapsedTime)
{
	//当たり判定に位置と半径をセット
	m_collider->SetPosition(m_position);

	//外してもよい
	//軽減のためプレイヤーの視界内、１００メートル以内なら当たり判定をとる
		//球との当たり判定
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
	
	//現在の状態の更新
	m_pCurrentState->Update(elapsedTime);
}

void CrabRobot::Render()
{
	m_pCurrentState->Render();
}

void CrabRobot::Finalize()
{
	m_pCurrentState->Finalize();
}

void CrabRobot::Damage(const int& damage)
{
	SetHP(GetHP() - damage);
}

void CrabRobot::SetpositionRandam(const float& min,const float& max)
{
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> distance(min, max);

	float x = static_cast<float>(distance(engine));
	float z = static_cast<float>(distance(engine));

	m_position = SimpleMath::Vector3(x, 0.0f, z);
	m_rotate = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, x);
}

void CrabRobot::Reset()
{
}

void CrabRobot::PartsRender()
{
	for (auto& part : m_parts)
	{
		//パーツを更新する
		part->Render();
	}
}
