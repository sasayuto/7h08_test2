#pragma once
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

#include"Scene/GameObjects/PlayScene/ObjectModel/ObjectsManager.h"
#include"AirshipParts/IAirshipComponent.h"
#include"AirshipState/IAirshipState.h"

//敵のクラスを定義する
class Airship
{
public:
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

	//当たり判定のゲッター
	Collider::Sphere* GetCollider() { return m_roughCollider.get(); }

	std::vector<std::unique_ptr<IAirshipComponent>>& GetParts() { return m_parts; };

	//生存のゲッター、セッター
	bool GetSurvival() const { return m_survival; }
	void SetSurvival(const bool& survival) { m_survival = survival; }

	//動きの状態をゲット
	IStateAirship* GetEnemyMotion() {
		return m_enemyMotion.get(); }

	//死亡の状態をゲット
	IStateAirship* GetEnemyKillMotion() { return m_enemyKillMotion.get(); }

	//現在の状態セット
	void SetIState(IStateAirship* Istate)
	{
		m_pCurrentState = Istate;
		m_pCurrentState->Initialize();
	}

	IStateAirship* GetIState() { return m_pCurrentState; }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Airship(const int& Hp, const int& Fuel, const int& offensivePower);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Airship();

	/// <summary>
	/// 初期化する
	/// </summary>
	/// <param name="bulletManager">球のアドレス</param>
	/// <param name="enemyManager">敵のマネージャーのアドレス</param>
	/// <param name="player">プレイヤーのアドレス</param>
	virtual void Initialize(
		BulletManager* bulletManager,
		ObjectsManager* objectsManager,
		Player* player
	);

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">フレーム時間</param>
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
	/// 敵をランダムに生成
	/// </summary>
	/// <param name="min">最小</param>
	/// <param name="max">最大</param>
	void SetpositionRandam(const float& min, const float& max);

	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="damage">相手が与えるダメージ</param>
	void Damage(const int& damage);

	/// <summary>
	/// 動きをリセット
	/// </summary>
	virtual void Reset();

	/// <summary>
	/// 1発発射
	/// </summary>
	/// <param name="BulletCoolTime">球のクールタイム</param>
	void Shot(const float& maxBulletCoolTime);

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
	/// パーツの当たり判定
	/// </summary>
	void PartsCollision();

	/// <summary>
	/// パーツの描画
	/// </summary>
	void PartsRender();

	/// <summary>
	/// パーツを生成する
	/// </summary>
	/// <param name="Parts">パーツのポインタ</param>
	void AddParts(std::unique_ptr<IAirshipComponent> Parts) { m_parts.emplace_back(move(Parts)); }

public:
	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="motion">通常の状態をポインタ</param>
	void AddEnemyMotion(std::unique_ptr<IStateAirship> motion) { m_enemyMotion = std::move(motion); }

	/// <summary>
	/// 死亡の状態を生成
	/// </summary>
	/// <param name="killmotion">死亡の状態をポインタ</param>
	void AddEnemyKillMotion(std::unique_ptr<IStateAirship> killmotion) { m_enemyKillMotion = std::move(killmotion); }

private:
	//生存
	bool m_survival;

	//動きの状態ポインタ
	std::unique_ptr<IStateAirship> m_enemyMotion;

	//死亡の状態のポインタ
	std::unique_ptr<IStateAirship> m_enemyKillMotion;

	// 現在の状態のアドレス
	IStateAirship* m_pCurrentState;

	//球のポインタ
	BulletManager* m_pBulletManager;

	//球のポインタ
	ObjectsManager* m_pObjectsManager;

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

	//パーツの配列のポインタ
	std::vector<std::unique_ptr<IAirshipComponent>> m_parts;

	//当たり判定のポインタ
	std::unique_ptr<Collider::Sphere> m_roughCollider;
};
