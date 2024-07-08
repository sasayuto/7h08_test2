#pragma once
#include"Scene/GameObjects/PlayScene/ObjectModel/ObjectsManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/StreetLight/StreetLightManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Bench/BenchManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/MoveObjects/MoveObjectsManager.h"
#include"Scene/GameObjects/PlayScene/Item/RespawnManager.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/Floor.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/FloorManagers/FloorManager_01.h"
#include"IPlayerComponent.h"

#include"Scene/GameObjects/PlayScene/Character/Player/StatePlayerFactory.h"
#include"Scene/GameObjects/PlayScene/Character/Player/IState.h"
#include"PlayerMotion.h"
#include"PlayerKillMotion.h"

//当たり判定
class SupplyPointManager;
class EnemyManager;
class CoinManager;
class BulletManager;
class AirshipManager;
class WindmillManager;
class SandstormManager;
class TurretManager;
class BigBrickWallManager;
class HouseMoveObjectsManager;
class BloodEffect;
class PlayerEffect;

//ステートクラス
class Players;
class KillMotion;

/// <summary>
/// プレイヤーのクラスを定義する
/// </summary>
class Player
{
public:
	static float BULLET_COOL_TIME;					//球クールタイム	(s)
	static float PLAYER_MAX_SPEED;					//前進の最大スピード(m/s)
	static float PLAYER_ACCELERATION;					//前進の加速度		(m/s)
	static float PLAYER_BEND_ACCELERATION;			//湾曲の加速度		(°/s)
	static float PLAYER_AIR_RESISTANCE;				//空気抵抗
	static float PLAYER_BEND_AIR_RESISTANCE;			//湾曲の空気抵抗
	static float PLAYER_STRAT_FALLING_SPEED;			//落下開始速度		(m/s)
	static float PLAYER_FALL_SPEED__ACCELERATION;		//落下の加速度		(m/s)
	static float PLAYER_FALL_SPEED_MAX;				//落下の最大速度	(m/s)
	static int PLAYER_MAX_HP;							//プレイヤーのHP	
	static int PLAYER_MAX_FUEL;						//プレイヤーの燃料	
	static int PLAYER_OFFENSIVE_POWER;				//プレイヤーの攻撃力
	static float BULLET_WIDTH;

	//カメラの方向
	DirectX::SimpleMath::Quaternion GetCameraRotate()const { return m_cameraRotate; };
	void SetCameraRotate(const DirectX::SimpleMath::Quaternion& cameraRotate) { m_cameraRotate = cameraRotate; }

	//通常の状態
	IState* GetMotion() { return m_motion.get(); }

	//死亡の状態
	IState* GetKillMotion() { return m_killMotion.get(); }

	//停止の状態
	IState* GetStopMotion() { return m_stopMotion.get(); }

	//停止の状態
	IState* GetAvoidanceMotion() { return m_avoidanceMotion.get(); }

	//加速の状態
	IState* GetTurbMode() { return m_turbMode.get(); }

	//現在の状態セット
	void SetIState(IState* Istate) {
		m_pCurrentState = Istate;
		m_pCurrentState->Initialize();
	}

	//プレイヤーの煙エフェクトのポインタのゲッター
	PlayerEffect* GetPlayerEffect() { return m_playerEffect.get(); };

	//プレイヤーの血のエフェクトのゲッター
	BloodEffect* GetBloodEffect() { return m_bloodEffect.get(); };

	//傾きアニメーションのセッター、ゲッター
	float GetTiltAnimation() const { return m_TiltAnimation; };
	void SetTiltAnimation(const float& tiltAnimation) { m_TiltAnimation = tiltAnimation;; };

	//アニメーションの回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Quaternion GetAnimetionRotate()const { return m_AnimetionRotate; };
	void SetAnimetionRotate(const DirectX::SimpleMath::Quaternion& animetionRotate) { m_AnimetionRotate = animetionRotate; };

	//生存フラグのゲッターセッター
	bool GetSurvival() { return m_survival; }
	void SetSurvival(const bool& survival) { m_survival = survival; }

	//反射ベクトルのゲッター、セッター
	void SetReflectionVector(const DirectX::SimpleMath::Vector3& reflectionVector) { m_reflectionVector = reflectionVector; }
	DirectX::SimpleMath::Vector3 GetReflectionVector() { return m_reflectionVector; }

	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//方向のゲッター、セッター
	DirectX::SimpleMath::Vector3 GetAngle() const { return m_angle; }
	void SetAngle(const DirectX::SimpleMath::Vector3& angle) { m_angle = angle; }

	//HPのゲッター、セッター
	int GetHP() const { return m_HP; }
	void SetHP(const int& HP) { m_HP = HP; }

	//燃料のゲッター、セッター
	int GetFuel() const { return m_fuel; }
	void SetFuel(const int& fuel) { m_fuel = fuel; }

	//攻撃力のゲッター、セッター
	int GetOffensivePower() const { return m_offensivePower; }
	void SetOffensivePower(const int& offensivePower) { m_offensivePower = offensivePower; }

	//速度(方向)のゲッター、セッター
	DirectX::SimpleMath::Vector3 GetVelcity() const { return m_velcity; }
	void SetVelcity(const DirectX::SimpleMath::Vector3& velcity) { m_velcity = velcity; }

	//速度のゲッター、セッター
	float GetSpeed() const { return m_speed; }
	void SetSpeed(const float& speed) { m_speed = speed; }

	//球クールタイムのゲッター、セッター
	float GetBulletCoolTime() const { return m_bulletCoolTime; }
	void SetBulletCoolTime(const float& bulletCoolTime) { m_bulletCoolTime = bulletCoolTime; }

	//重力のゲッター、セッター
	float GetGravity() const { return m_gravity; }
	void SetGravity(const float& gravity) { m_gravity = gravity; }

	//球の種類のゲッター、セッター
	Bullet::BulletType GetBulletType() const { return m_bulletType; }
	void SetBulletType(const Bullet::BulletType& bulletType) { m_bulletType = bulletType; }

	//当たり判定のゲッター
	Collider::Sphere* GetCollider() { return m_collider.get(); }


public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	///  初期化する
	/// </summary>
	/// <param name="bulletManager">球の管理者のアドレス</param>
	/// <param name="enemyManager">敵の管理者のアドレス</param>
	/// <param name="coinManager">コインの管理者のアドレス</param>
	/// <param name="objectsManager">オブジェクトの管理者のアドレス</param>
	/// <param name="respawnManager">リスポーン地点の管理者のアドレス</param>
	/// <param name="supplyPointManager">アイテムの管理者のアドレス</param>
	/// <param name="airshipManager">飛行船の管理者のアドレス</param>
	/// <param name="windmillManager">風車の管理者のアドレス</param>
	/// <param name="floor">床の管理者のアドレス</param>
	/// <param name="streetLightManager">街灯の管理者のアドレス</param>
	/// <param name="BenchManager">ベンチの管理者のアドレス</param>
	/// <param name="sandstormManager">砂嵐の管理者のアドレス</param>
	/// <param name="turretManager">タレットの管理者のアドレス</param>
	/// <param name="floorManager_01">床の管理者のアドレス</param>
	void Initialize(
		BulletManager* bulletManager,
		EnemyManager* enemyManager = nullptr,
		CoinManager* coinManager = nullptr,
		ObjectsManager* objectsManager = nullptr,
		RespawnManager* respawnManager = nullptr,
		SupplyPointManager* supplyPointManager = nullptr,
		AirshipManager* airshipManager = nullptr,
		WindmillManager* windmillManager = nullptr,
		Floor* floor = nullptr,
		StreetLightManager* streetLightManager = nullptr,
		MoveObjectsManager* BenchManager = nullptr,
		MoveObjectsManager* fenceManager = nullptr,
		SandstormManager* sandstormManager = nullptr,
		TurretManager* turretManager = nullptr,
		FloorManager_01* floorManager_01 = nullptr,
		BigBrickWallManager* bigBrickWallManager = nullptr,
		HouseMoveObjectsManager* houseMoveObjectsManager = nullptr,
		HouseMoveObjectsManager * HouseMoveObjectsManager2 = nullptr,
		HouseMoveObjectsManager * HouseMoveObjectsManager3 = nullptr
	);

	void PlayerLoudDate();
	/// <summary>
	/// 処理を実行する
	/// </summary>
	/// <param name="elapsedTime">1フレーム時間</param>
	void Update(const float& elapsedTime);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

	/// <summary>
	/// シャドウマップ用の画像を作る
	/// </summary>
	void RenderShadowTex();

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();

	/// <summary>
	/// 動きをリセット
	/// </summary>
	void Reset();

	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="damage">相手が与えるダメージ</param>
	void Damage(const int& damage);

	/// <summary>
	/// 2発発射
	/// </summary>
	/// <param name="BulletCoolTime">球のクールタイム</param>
	void DoubleShot(const float& BulletCoolTime);

	/// <summary>
	/// 1発発射
	/// </summary>
	/// <param name="BulletCoolTime">球のクールタイム</param>
	void Shot(const float& maxBulletCoolTime);

	/// <summary>
	/// パーツを生成する
	/// </summary>
	/// <param name="Parts">パーツのポインタ</param>
	void AddParts(std::unique_ptr<IPlayerComponent> Parts) { m_parts.emplace_back(move(Parts)); }
	std::vector<std::unique_ptr<IPlayerComponent>>& GetParts() { return m_parts; }

	/// <summary>
	/// パーツの初期化
	/// </summary>
	void PartsInitialize();

	/// <summary>
	/// パーツの更新をする
	/// </summary>
	void PartsUpdate();

	/// <summary>
	/// パーツの爆発処理
	/// </summary>
	void PartsExplosion();

	/// <summary>
	/// パーツの速度処理をする
	/// </summary>
	void PartsMotion();

	/// <summary>
	/// パーツの速度処理をする
	/// </summary>
	void PartsRender();

private:
	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="motion">通常の状態のポインタ</param>
	void AddPlayerMotion(std::unique_ptr<IState> motion) { m_motion = std::move(motion); }

	/// <summary>
	/// 死亡の状態を生成
	/// </summary>
	/// <param name="killmotion">死亡の状態のポインタ</param>
	void AddKillPlayerMotion(std::unique_ptr<IState> killmotion) { m_killMotion = std::move(killmotion); }

	/// <summary>
	/// 死亡の状態を生成
	/// </summary>
	/// <param name="killmotion">死亡の状態のポインタ</param>
	void AddPlayerStopMotion(std::unique_ptr<IState> killmotion) { m_stopMotion = std::move(killmotion); }

	/// <summary>
	/// 死亡の状態を生成
	/// </summary>
	/// <param name="killmotion">死亡の状態のポインタ</param>
	void AddPlayerAvoidanceMotion(std::unique_ptr<IState> avoidanceMotion) { m_avoidanceMotion = std::move(avoidanceMotion); }

	/// <summary>
	/// 死亡の状態を生成
	/// </summary>
	/// <param name="killmotion">死亡の状態のポインタ</param>
	void AddPlayerTurbMode(std::unique_ptr<IState> turbMode) { m_turbMode = std::move(turbMode); }

private:
	//通常の状態のポインタ
	std::unique_ptr<IState> m_motion;

	//死亡の状態のポインタ
	std::unique_ptr<IState> m_killMotion;

	//死亡の状態のポインタ
	std::unique_ptr<IState> m_stopMotion;

	//死亡の状態のポインタ
	std::unique_ptr<IState> m_avoidanceMotion;

	//死亡の状態のポインタ
	std::unique_ptr<IState> m_turbMode;

	// 現在の状態のポインタ
	IState* m_pCurrentState;

	//オブジェクトのポインタ
	ObjectsManager* m_pObjectsManager;
	
	HouseMoveObjectsManager* m_pHouseMoveObjectsManager;
	HouseMoveObjectsManager* m_pHouseMoveObjectsManager1;
	HouseMoveObjectsManager* m_pHouseMoveObjectsManager2;

	//リスポーン地点の管理者のポインタ
	RespawnManager* m_pRespawnManager;

	//飛行船の管理者のポインタ
	AirshipManager* m_pAirshipManager;

	//風車の管理者のポインタ
	WindmillManager* m_pWindmillManager;

	//床のポインタ
	Floor* m_pFloor;

	//床の管理者のポインタ
	FloorManager_01* m_pFloorManager_01;

	//街灯の管理者のポインタ
	StreetLightManager* m_pStreetLightManager;

	//砂嵐の管理者のポインタ
	SandstormManager* m_pSandstormManager;

	//ベンチの管理者のポインタ
	MoveObjectsManager* m_pBenchManager;

	//ベンチの管理者のポインタ
	MoveObjectsManager* m_pFenceManager;

	//タレットの管理者のポインタ
	TurretManager* m_pTurretManager;

	//タレットの管理者のポインタ
	BigBrickWallManager* m_pBigBrickWallManager;

	//パーツの配列のポインタ
	std::vector<std::unique_ptr<IPlayerComponent>> m_parts;

	//カメラ回転
	DirectX::SimpleMath::Quaternion m_cameraRotate;

	//煙のエフェクトのポインタ
	std::unique_ptr<PlayerEffect> m_playerEffect;

	//煙のエフェクトのポインタ
	std::unique_ptr<BloodEffect> m_bloodEffect;

	//飛行機のZ軸アニメーション
	float m_TiltAnimation;

	//アニメーションの回転クオータニオン
	DirectX::SimpleMath::Quaternion m_AnimetionRotate;

	//生存フラグ
	bool m_survival;

	//反射ベクトル
	DirectX::SimpleMath::Vector3 m_reflectionVector;

	//球の管理者のポインタ
	BulletManager* m_pBulletManager;

	//球の種類
	Bullet::BulletType m_bulletType;

	//位置
	DirectX::SimpleMath::Vector3 m_position;

	//速度(方向)
	DirectX::SimpleMath::Vector3 m_velcity;

	//速度
	float m_speed;

	//回転クオータニオン
	DirectX::SimpleMath::Quaternion m_rotate;

	//方向
	DirectX::SimpleMath::Vector3 m_angle;

	//球のクールタイム
	float m_bulletCoolTime;

	//HP
	int m_HP;

	//燃料
	int m_fuel;

	//攻撃力
	int m_offensivePower;

	//重力
	float m_gravity;

	//当たり判定のポインタ
	std::unique_ptr<Collider::Sphere> m_collider;
};