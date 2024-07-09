#include "pch.h"
#include"Player.h"
#include <math.h>

#include"PlayerPartFactory.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/AirshipManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Windmill/WindmillManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Objects/Walls/BigBrickWall/BigBrickWallManager.h"
#include"Scene/GameObjects/PlayScene/Sandstorm/SandstormManager.h"
#include"Scene/GameObjects/PlayScene/Character/Turret/TurretManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/HouseMoveObjects/HouseMoveObjectsManager.h"

using namespace DirectX;

float Player::BULLET_COOL_TIME = 1.0f;		//球クールタイム	(s)
float Player::PLAYER_MAX_SPEED = (15.0f / 60);	//前進の最大スピード(m/s)
float Player::PLAYER_ACCELERATION = (0.5f / 60);	//前進の加速度		(m/s)
float Player::PLAYER_BEND_ACCELERATION = (6.0f / 60);	//湾曲の加速度		(°/s)
float Player::PLAYER_AIR_RESISTANCE = (0.99f);		//空気抵抗
float Player::PLAYER_BEND_AIR_RESISTANCE = (0.90f);		//湾曲の空気抵抗
float Player::PLAYER_STRAT_FALLING_SPEED = (10.0f / 60);	//落下開始速度		(m/s)
float Player::PLAYER_FALL_SPEED__ACCELERATION = (0.1f / 60);	//落下の加速度		(m/s)
float Player::PLAYER_FALL_SPEED_MAX = (30.0f / 60);	//落下の最大速度	(m/s)
int Player::PLAYER_MAX_HP = 20000;							//プレイヤーのHP
int Player::PLAYER_MAX_FUEL = 5000;							//プレイヤーの燃料
int Player::PLAYER_OFFENSIVE_POWER = 1;						//プレイヤーの攻撃力
float Player::BULLET_WIDTH = 1.2f;

Player::Player() :
	m_killMotion(nullptr),
	m_motion(nullptr),
	m_pCurrentState(nullptr),
	m_pObjectsManager(nullptr),
	m_pHouseMoveObjectsManager(nullptr),
	m_pHouseMoveObjectsManager1(nullptr),
	m_pHouseMoveObjectsManager2(nullptr),
	m_cameraRotate(SimpleMath::Quaternion::Identity),
	m_AnimetionRotate(),
	m_TiltAnimation(0.0f),
	m_bloodEffect(nullptr),
	m_playerEffect(nullptr),
	m_pAirshipManager(nullptr),
	m_survival(false),
	m_reflectionVector(DirectX::SimpleMath::Vector3::Zero),
	m_position(SimpleMath::Vector3::Zero),
	m_velcity(SimpleMath::Vector3::Zero),
	m_rotate(SimpleMath::Quaternion::Identity),
	m_bulletCoolTime(),
	m_HP(PLAYER_MAX_HP),
	m_fuel(PLAYER_MAX_FUEL),
	m_offensivePower(PLAYER_OFFENSIVE_POWER),
	m_speed(),
	m_angle(SimpleMath::Vector3::Zero),
	m_bulletType(Bullet::BulletType::None),
	m_pBulletManager(nullptr),
	m_gravity()
{
	std::ifstream obj("Resources/json/Json_playerDate.Json");
	Json::CharReaderBuilder reader;
	Json::Value root;

	// ファイルが開かれているかを確認します。
	if (obj.is_open()) {
		std::string errors;

		// ファイルからJSONをパースします。
		if (Json::parseFromStream(reader, obj, &root, &errors))
		{
			// JSONに "house" が存在し、配列であるかどうかを確認します。
			if (root.isMember("PlayerData") && root["PlayerData"].isArray())
			{
				// "house" 配列を取得します。
				const Json::Value& PlayerData = root["PlayerData"][0];


				BULLET_COOL_TIME = PlayerData["BULLET_COOL_TIME"][0].asFloat();		//球クールタイム	(s)
				PLAYER_MAX_SPEED = PlayerData["PLAYER_MAX_SPEED"][0].asFloat();	//前進の最大スピード(m/s)
				PLAYER_ACCELERATION = PlayerData["PLAYER_ACCELERATION"][0].asFloat();	//前進の加速度		(m/s)
				PLAYER_BEND_ACCELERATION = PlayerData["PLAYER_BEND_ACCELERATION"][0].asFloat();	//湾曲の加速度		(°/s)
				PLAYER_AIR_RESISTANCE = (0.99f);		//空気抵抗
				PLAYER_BEND_AIR_RESISTANCE = (0.90f);		//湾曲の空気抵抗
				PLAYER_STRAT_FALLING_SPEED = (10.0f / 60);	//落下開始速度		(m/s)
				PLAYER_FALL_SPEED__ACCELERATION = (0.1f / 60);	//落下の加速度		(m/s)
				PLAYER_FALL_SPEED_MAX = (30.0f / 60);	//落下の最大速度	(m/s)
				PLAYER_MAX_HP = PlayerData["PLAYER_MAX_HP"][0].asInt();							//プレイヤーのHP
				PLAYER_MAX_FUEL = PlayerData["PLAYER_MAX_FUEL"][0].asInt();							//プレイヤーの燃料
				PLAYER_OFFENSIVE_POWER = PlayerData["PLAYER_OFFENSIVE_POWER"][0].asInt();						//プレイヤーの攻撃力
				BULLET_WIDTH = 1.2f;
			}
		}
		else {
			std::cerr << "JSONのパースエラー: " << errors << std::endl;
		}
		obj.close();
	}
	else {
		std::cerr << "JSONファイルを開く際にエラーが発生しました。" << std::endl;
	}

}

Player::~Player()
{
}

void Player::Initialize(
	BulletManager* bulletManager, 
	EnemyManager* enemyManager,
	CoinManager* coinManager,
	ObjectsManager* objectsManager,
	RespawnManager* respawnManager, 
	SupplyPointManager* supplyPointManager, 
	AirshipManager* airshipManager, 
	WindmillManager* windmillManager,
	Floor* floor,
	StreetLightManager* streetLightManager,
	MoveObjectsManager* benchManager,
	MoveObjectsManager* fenceManager,
	SandstormManager* sandstormManager,
	TurretManager* turretManager,
	FloorManager_01* floorManager_01,
	BigBrickWallManager* bigBrickWallManager,
	HouseMoveObjectsManager* houseMoveObjectsManager,
	HouseMoveObjectsManager* HouseMoveObjectsManager2,
	HouseMoveObjectsManager* HouseMoveObjectsManager3
)
{
	m_pHouseMoveObjectsManager = houseMoveObjectsManager;
	m_pHouseMoveObjectsManager1 = HouseMoveObjectsManager2;
	m_pHouseMoveObjectsManager2 = HouseMoveObjectsManager3;
	m_pBigBrickWallManager = bigBrickWallManager;
	//球のアドレス
	m_pBulletManager = bulletManager;
	m_pFenceManager = fenceManager;
	m_pObjectsManager = objectsManager;

	m_pFloorManager_01 = floorManager_01;
	m_pRespawnManager = respawnManager;

	m_pAirshipManager = airshipManager;
	m_pWindmillManager = windmillManager;
	m_pFloor = floor;
	m_pSandstormManager = sandstormManager;
	m_pBenchManager = benchManager;

	m_pStreetLightManager = streetLightManager;

	m_pTurretManager = turretManager;

	m_playerEffect = std::make_unique<PlayerEffect>();

	m_bloodEffect = std::make_unique<BloodEffect>();

	//当たり判定を生成
	m_collider = std::make_unique<Collider::Sphere>();

	//当たり判定に位置と半径をセット
	m_collider->SetPosition(m_position);

	m_collider->SetRadius(1.3f);

	//プレイヤーのインスタンスを生成する
	AddPlayerMotion(
		StatePlayerFactory::CreateMotion(
			this, bulletManager, respawnManager, supplyPointManager, enemyManager, coinManager
		)
	);

	//プレイヤーのインスタンスを生成する
	AddKillPlayerMotion(StatePlayerFactory::CreateKillMotion(this));

	//プレイヤーのインスタンスを生成する
	AddPlayerStopMotion(
		StatePlayerFactory::CreateStopMotion(
			this, bulletManager, respawnManager, supplyPointManager, enemyManager, coinManager
		)
	);
	//プレイヤーのインスタンスを生成する
	AddPlayerTurbMode(
		StatePlayerFactory::CreateTurbMode(
			this, bulletManager, respawnManager, supplyPointManager, enemyManager, coinManager
		)
	);
	//プレイヤーのインスタンスを生成する
	AddPlayerAvoidanceMotion(
		StatePlayerFactory::CreateAvoidanceMotion(
			this,  respawnManager, supplyPointManager,  coinManager
		)
	);

	//プレイヤーの情報をリセット
 	Reset();

	//リセットの後に書く（位置や角度を持たせるから）
	// プレイヤーにプロペラを追加する
	AddParts(PlayerPartFactory::CreatePlayerBody(nullptr, GetPosition(), GetRotate()));

	//動きの状態を取得
	m_pCurrentState = m_motion.get();

	//動きの初期化
	m_pCurrentState->Initialize();

}

void Player::PlayerLoudDate()
{
}

void Player::Update(const float& elapsedTime)
{

	if (m_pObjectsManager)
		m_pObjectsManager->CheckHitCharacter(this);

	if (m_pHouseMoveObjectsManager)
		m_pHouseMoveObjectsManager->CheckHitCharacter(this);

	if (m_pHouseMoveObjectsManager1)
		m_pHouseMoveObjectsManager1->CheckHitCharacter(this);

	if (m_pHouseMoveObjectsManager2)
		m_pHouseMoveObjectsManager2->CheckHitCharacter(this);

	if (m_pAirshipManager)
		m_pAirshipManager->CheckHitPlayer(this);

	if (m_pWindmillManager)
		m_pWindmillManager->CheckHitCharacter(this);

	if (m_pFloor)
		m_pFloor->CheckHitPlayer(this);

	if (m_pStreetLightManager)
		m_pStreetLightManager->CheckHitCharacter(this);

	if (m_pBenchManager)
		m_pBenchManager->CheckHitCharacter(this);

	if (m_pFenceManager)
		m_pFenceManager->CheckHitCharacter(this);

	if (m_pSandstormManager)
		m_pSandstormManager->CheckHitCharacter(this);

	if (m_pTurretManager)
		m_pTurretManager->CheckHitCharacter(this);

	if (m_pBigBrickWallManager)
 		m_pBigBrickWallManager->CheckHitCharacter(this);

	if (m_pFloorManager_01)
		m_pFloorManager_01->CheckHitCharacter(this);
	//現在の状態の更新
	m_pCurrentState->Update(elapsedTime);
	//当たり判定に位置と半径をセット
	m_collider->SetPosition(m_position);

	//空気抵抗//
	//前進のスピードの空気抵抗
	SetSpeed(Player::PLAYER_AIR_RESISTANCE*GetSpeed());
	////重力の空気抵抗
	//SetGravity(Player::PLAYER_AIR_RESISTANCE * GetGravity());
	//曲がる時の空気抵抗
	SetVelcity(Player::PLAYER_BEND_AIR_RESISTANCE * GetVelcity());
}

void Player::Render()
{	
	//現在の状態の描画
	m_pCurrentState->Render();
}

void Player::RenderShadowTex()
{
	for (auto& parts : m_parts)
	{
		// パーツを更新する
		parts->RenderShadowTex();
	}
}

void Player::Finalize()
{
	m_pCurrentState->Finalize();
}

void Player::Damage(const int& damage)
{
	//ダメージ分HPを減らす
	SetHP(GetHP() - damage);
}

void Player::DoubleShot(const float& maxBulletCoolTime)
{
	//球の発射先を羽に調整
	SimpleMath::Vector3 shot(BULLET_WIDTH, 0, 0);
	shot = SimpleMath::Vector3::Transform(shot, m_rotate);

	if (m_bulletCoolTime == 0.0f)
	{
		m_pBulletManager->Shot(m_bulletType, Bullet::BulletParent::PlayerBullet, m_position + shot, m_rotate);
		m_pBulletManager->Shot(m_bulletType, Bullet::BulletParent::PlayerBullet, m_position - shot, m_rotate);
		m_bulletCoolTime = maxBulletCoolTime;
	}
}

void Player::Shot(const float& maxBulletCoolTime)
{
	if (m_bulletCoolTime == 0.0f)
	{
		m_pBulletManager->Shot(m_bulletType, Bullet::BulletParent::PlayerBullet, m_position, m_rotate);
		m_bulletCoolTime = maxBulletCoolTime;
	}
}


void Player::Reset()
{
	//プレイヤーの情報をリセットする
	SetHP(PLAYER_MAX_HP);
	if (m_pRespawnManager)
		SetPosition(m_pRespawnManager->GetRespawnPosition());
	else
		SetPosition(DirectX::SimpleMath::Vector3(0,50,0));
	SetVelcity(SimpleMath::Vector3::Zero);
	SetFuel(PLAYER_MAX_FUEL);
	SetRotate(DirectX::SimpleMath::Quaternion::Identity);
	//９０度回転してstart
	SetAnimetionRotate(
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3::UnitY,
			DirectX::XMConvertToRadians(90)
		)
	);
	SetBulletCoolTime(0);
	SetAngle(SimpleMath::Vector3::Zero);
	SetSpeed(0);
	SetGravity(0);
	m_cameraRotate = SimpleMath::Quaternion::Identity;
	m_bloodEffect->Initialize();
	m_playerEffect->Initialize();
	SetSpeed(Player::PLAYER_MAX_SPEED);
	m_TiltAnimation = 0.0f;
	//球の種類をセット
	SetBulletType(Bullet::BulletType::Type2);
	m_survival = true;
	m_reflectionVector = DirectX::SimpleMath::Vector3::Zero;
}

void Player::PartsInitialize()
{
	for (auto& parts : m_parts)
	{
		// パーツを初期化
   		parts->Initialize(m_reflectionVector*2);
	}
}

void Player::PartsUpdate()
{
	for (auto& parts : m_parts)
	{
		// パーツを更新する
		parts->Update(GetPosition(), GetRotate());
	}
}

void Player::PartsExplosion()
{
	for (auto& parts : m_parts)
	{
		// パーツを更新する
		parts->Explosion();
	}
}

void Player::PartsMotion()
{
	for (auto& parts : m_parts)
	{
		// パーツを更新する
		parts->Speed();
	}
}

void Player::PartsRender()
{
	for (auto& part : m_parts)
	{
		//パーツを更新する
		part->Render();
	}

}
