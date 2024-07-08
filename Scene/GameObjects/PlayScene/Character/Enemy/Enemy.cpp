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
	// プレイヤーにプロペラを追加する
	AddParts(PlayerPartFactory::CreatePlayerBody(nullptr, m_position, m_rotate));

	//当たり判定を生成
	m_collider = std::make_unique<Collider::Sphere>();

	//当たり判定に位置と半径をセット
	m_collider->SetPosition(m_position);

	//半径をセット
	m_collider->SetRadius(1);

	//壁の管理者のポインタを取得
	m_pBigBrickWallManager = bigBrickWallManager;

	//床の管理者のポインタを取得
	m_pFloorManager_01 = floorManager_01;

	//球の管理者のポインタを取得
	m_pBulletManager = bulletManager;

	//オブジェクトの管理者のポインタを取得
	m_pObjectsManager = objectsManager;

	//飛行船の管理者のポインタを取得
	m_pAirshipManager = airshipManager;

	//風車の管理者のポインタを取得
	m_pWindmillManager = windmillManager;

	//床ののポインタを取得
	m_pFloor = floor;

	//砂嵐の管理者のポインタを取得
	m_pSandstormManager = sandstormManager;

	//敵が生きている
	SetSurvival(true);

	//球の保有者をセット
	SetBulletParent(Bullet::BulletParent::EnemyBullet);
}

void Enemy::Update(const float& elapsedTime)
{
	//当たり判定に位置と半径をセット
	m_collider->SetPosition(m_position);

	//外してもよい
	//軽減のためプレイヤーの視界内、１００メートル以内なら当たり判定をとる
	if (!Draw::GetInstance()->UpdateDistance(m_position, 100))
	{
		//球との当たり判定
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
	//現在の状態の更新
	m_pCurrentState->Update(elapsedTime);
}

void Enemy::Render()
{
	//現在の状態の描画
	m_pCurrentState->Render();
}

void Enemy::RenderShadowTex()
{
	for (auto& parts : m_parts)
	{
		// パーツを更新する
		parts->RenderShadowTex();
	}
}

void Enemy::Finalize()
{
	//現在の状態の後始末
	m_pCurrentState->Finalize();
}

void Enemy::Damage(const int& damage)
{
	//ダメージ処理
	SetHP(GetHP() - damage);
}

void Enemy::SetpositionRandam(const float& min,const float& max)
{
	//乱数
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
	//球のクールタイムか
	if (m_bulletCoolTime == 0.0f)
	{
		//球発射
		m_pBulletManager->Shot(m_bulletType, m_bulletParent, m_position, m_rotate);
	
		//クールタイムをセット
		m_bulletCoolTime = maxBulletCoolTime;
	}
}

void Enemy::PartsInitialize()
{
	//パーツの初期化
	for (auto& parts : m_parts)
	{
		// パーツを初期化
		parts->Initialize(m_reflectionVector);
	}
}

void Enemy::PartsUpdate()
{
	//パーツの更新
	for (auto& parts : m_parts)
	{
		// パーツを更新する
		parts->Update(m_position, m_rotate);
	}
}

void Enemy::PartsExplosion()
{
	//パーツの爆発処理
	for (auto& parts : m_parts)
	{
		// パーツを更新する
		parts->Explosion();
	}
}

void Enemy::PartsMotion()
{
	//パーツの燃料にかかわる動き
	for (auto& parts : m_parts)
	{
		// パーツを更新する
		parts->Speed();
	}
}

void Enemy::PartsCollision()
{
	//for (auto& playerPart : m_PlayerPropellerParts)
	//{
	//	// パーツを更新する
	//	playerPart->Collision();
	//}

}

void Enemy::PartsRender()
{
	//パーツの描画
	for (auto& part : m_parts)
	{
		//パーツを更新する
		part->Render();
	}
}
