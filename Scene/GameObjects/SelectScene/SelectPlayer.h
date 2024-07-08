#pragma once
#include"Scene/GameObjects/PlayScene/ObjectModel/ObjectsManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/StreetLight/StreetLightManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Bench/BenchManager.h"
#include"Scene/GameObjects/PlayScene/Item/RespawnManager.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/Floor.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/FloorManagers/FloorManager_01.h"
#include"Scene/GameObjects/PlayScene/Character/Player/IPlayerComponent.h"
#include "ImaseLib/MoveUserInterface.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"

#include"Scene/GameObjects/PlayScene/Character/Player/StatePlayerFactory.h"
#include"Scene/GameObjects/PlayScene/Character/Player/IState.h"

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

class BloodEffect;
class PlayerEffect;

//ステートクラス
class Players;
class KillMotion;

/// <summary>
/// プレイヤーのクラスを定義する
/// </summary>
class SelectPlayer
{
public:
	static const float BULLET_COOL_TIME;					//球クールタイム	(s)
	static const float PLAYER_MAX_SPEED;					//前進の最大スピード(m/s)
	static const float PLAYER_ACCELERATION;					//前進の加速度		(m/s)
	static const float PLAYER_BEND_ACCELERATION;			//湾曲の加速度		(°/s)
	static const float PLAYER_AIR_RESISTANCE;				//空気抵抗
	static const float PLAYER_BEND_AIR_RESISTANCE;			//湾曲の空気抵抗
	static const float PLAYER_STRAT_FALLING_SPEED;			//落下開始速度		(m/s)
	static const float PLAYER_FALL_SPEED__ACCELERATION;		//落下の加速度		(m/s)
	static const float PLAYER_FALL_SPEED_MAX;				//落下の最大速度	(m/s)
	static const int PLAYER_MAX_HP;							//プレイヤーのHP	
	static const int PLAYER_MAX_FUEL=1000000;						//プレイヤーの燃料	
	static const int PLAYER_OFFENSIVE_POWER=100;				//プレイヤーの攻撃力
	static const float BULLET_WIDTH;

	//カメラの方向
	DirectX::SimpleMath::Quaternion GetCameraRotate()const { return m_cameraRotate; };
	void SetCameraRotate(const DirectX::SimpleMath::Quaternion& cameraRotate) { m_cameraRotate = cameraRotate; }


	//プレイヤーの煙エフェクトのポインタのゲッター
	PlayerEffect* GetPlayerEffect() { return m_playerEffect.get(); };

	//傾きアニメーションのセッター、ゲッター
	float GetTiltAnimation() const { return m_TiltAnimation; };
	void SetTiltAnimation(const float& tiltAnimation) { m_TiltAnimation = tiltAnimation;; };

	//アニメーションの回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Quaternion GetAnimetionRotate()const { return m_AnimetionRotate; };
	void SetAnimetionRotate(const DirectX::SimpleMath::Quaternion& animetionRotate) { m_AnimetionRotate = animetionRotate; };

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
	SelectPlayer();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SelectPlayer();

	/// <summary>
	///  初期化する
	/// </summary>
	/// <param name="bulletManager">球の管理者のアドレス</param>
	/// <param name="enemyManager">敵の管理者のアドレス</param>
	/// <param name="coinManager">コインの管理者のアドレス</param>
	/// <param name="objectsManager">オブジェクトの管理者のアドレス</param>
	/// <param name="respawnManager">リスポーン地点の管理者のアドレス</param>
	/// <param name="supplyPointManager">アイテムの管理者のアドレス</param>
	/// <param name="treeManager">木の管理者のアドレス</param>
	/// <param name="airshipManager">飛行船の管理者のアドレス</param>
	/// <param name="windmillManager">風車の管理者のアドレス</param>
	/// <param name="floor">床の管理者のアドレス</param>
	/// <param name="streetLightManager">街灯の管理者のアドレス</param>
	/// <param name="BenchManager">ベンチの管理者のアドレス</param>
	/// <param name="sandstormManager">砂嵐の管理者のアドレス</param>
	/// <param name="turretManager">タレットの管理者のアドレス</param>
	/// <param name="floorManager_01">床の管理者のアドレス</param>
	void Initialize(BulletManager* bulletManager);

	/// <summary>
	/// 処理を実行する
	/// </summary>
	/// <param name="elapsedTime">1フレーム時間</param>
	void Update(const float& elapsedTime,const bool& decisionFlag,  const bool& returnDecisionFlag);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();

	/// <summary>
	/// パーツを生成する
	/// </summary>
	/// <param name="Parts">パーツのポインタ</param>
	void AddParts(std::unique_ptr<IPlayerComponent> Parts) { m_parts.emplace_back(move(Parts)); }
	std::vector<std::unique_ptr<IPlayerComponent>>& GetPlayerParts() { return m_parts; }

	/// <summary>
	/// 影になるオブジェクトの描画
	/// </summary>
	void ShadowMapRender();

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
	//パーツの配列のポインタ
	std::vector<std::unique_ptr<IPlayerComponent>> m_parts;

	//カメラ回転
	DirectX::SimpleMath::Quaternion m_cameraRotate;

	//煙のエフェクトのポインタ
	std::unique_ptr<PlayerEffect> m_playerEffect;

	//飛行機のZ軸アニメーション
	float m_TiltAnimation;

	//アニメーションの回転クオータニオン
	DirectX::SimpleMath::Quaternion m_AnimetionRotate;

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

	//ゲージとベースのポインタ
	std::unique_ptr<tito::MoveUserInterface> m_HorizontalTriangle[2];
	std::unique_ptr<Collider::Box2D> m_HorizontalTrianglecol[2];

};