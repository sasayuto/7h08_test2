#include "pch.h"
#include"Airship.h"
#include <math.h>
#include<random>
#include"AirshipParts/AirshipPartFactory.h"
#include"AirshipParts/AirshipBody.h"

using namespace DirectX;
Airship::Airship(const int& Hp, const int& Fuel, const int& offensivePower) :
	m_survival(false),
	//m_pCurrentState(nullptr),
	//m_AirshipKillMotion(nullptr),
	//m_AirshipMotion(nullptr),
	m_position(SimpleMath::Vector3::Zero),
	m_velcity(SimpleMath::Vector3::Zero),
	m_rotate(SimpleMath::Quaternion::Identity),
	m_bulletCoolTime(),
	m_HP(Hp),
	m_fuel(Fuel),
	m_offensivePower(offensivePower),
	m_speed(),
	m_angle(SimpleMath::Vector3::Zero),
	//m_bulletParent(Bullet::BulletParent::None),
	//m_bulletType(Bullet::BulletType::None),
	m_pBulletManager(nullptr),
	m_gravity()
{
}

Airship::~Airship()
{
}

void Airship::Initialize(
	BulletManager* bulletManager,
	ObjectsManager* objectsManager,
	Player* player
)
{
	player;
	//// プレイヤーにプロペラを追加する
	AddParts(AirshipPartFactory::CreateAirshipBody(nullptr, m_position, m_rotate));

	//大まかな当たり判定を生成
	m_roughCollider = std::make_unique<Collider::Sphere>();

	//対角線の半分
	m_roughCollider->SetRadius(1000);
	m_roughCollider->SetPosition(GetPosition());

	//球のポインタを取得
	m_pBulletManager = bulletManager;

	//オブジェクトのポインタを取得
	m_pObjectsManager = objectsManager;

	//敵が生きているか
	SetSurvival(true);
}

void Airship::Update(const float& elapsedTime)
{
	//当たり判定に位置と半径をセット
	m_roughCollider->SetPosition(m_position);

	////当たり判定
	//if (m_pObjectsManager)
	//	m_pObjectsManager->CheckHitAirship(this);

	//if (m_pTreeManager)
	//	m_pTreeManager->CheckHitAirship(this);

	if (m_pBulletManager)
		m_pBulletManager->CheckHitDamegeObjects(this,Bullet::BulletParent::EnemyBullet);

	//現在の状態の更新
	m_pCurrentState->Update(elapsedTime);
}

void Airship::Render()
{
	//現在の状態の描画
	m_pCurrentState->Render();
	//Draw::GetInstance()->TestSphereModel(m_roughCollider->GetRadius(), m_roughCollider->GetPosition(), m_rotate);
}

void Airship::RenderShadowTex()
{
	for (auto& parts : m_parts)
	{
		// パーツを更新する
		parts->RenderShadowTex();
	}
}

void Airship::Finalize()
{
	//現在の状態の後始末
	m_pCurrentState->Finalize();
}

void Airship::Damage(const int& damage)
{
	//ダメージ処理
	SetHP(GetHP() - damage);
}

void Airship::SetpositionRandam(const float& min,const float& max)
{
	//ランダムな数値
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> distance(min, max);

	float x = static_cast<float>(distance(engine));
	float z = static_cast<float>(distance(engine));

	m_position = SimpleMath::Vector3(x, 200, z);
}

void Airship::Reset()
{
}

void Airship::Shot(const float& maxBulletCoolTime)
{
	//クールタイムか
	if (m_bulletCoolTime == 0.0f)
	{
		//球を打つ
		m_pBulletManager->Shot(Bullet::BulletType::Type1, Bullet::BulletParent::EnemyBullet, m_position, m_rotate);
		
		//クールタイムをセット
		m_bulletCoolTime = maxBulletCoolTime;
	}
}

void Airship::PartsInitialize()
{
	//パーツの初期化
	for (auto& parts : m_parts)
	{
		// パーツを初期化
		parts->Initialize();
	}

}

void Airship::PartsUpdate()
{
	//パーツの更新
	for (auto& parts : m_parts)
	{
		// パーツを更新する
		parts->Update(m_position, m_rotate);
	}
}

void Airship::PartsExplosion()
{
	//パーツの爆発
	for (auto& parts : m_parts)
	{
		// パーツを更新する
		parts->Explosion();
	}
}

void Airship::PartsMotion()
{
	//マーツの燃料にかかわる動き
	for (auto& parts : m_parts)
	{
		// パーツを更新する
		parts->Speed();
	}
}

void Airship::PartsCollision()
{
	//for (auto& playerPart : m_PlayerPropellerParts)
	//{
	//	// パーツを更新する
	//	playerPart->Collision();
	//}

}

void Airship::PartsRender()
{
	//パーツの描画
	for (auto& part : m_parts)
	{
		//パーツを更新する
		part->Render();
	}
}
