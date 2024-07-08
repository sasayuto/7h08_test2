#pragma once
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/Floor.h"
#include"CrabRobotState/ICrabRobotState.h"
#include"CrabRobotParts/ICrabRobotComponent.h"
class TurretManager;
class AirshipManager;
class SandstormManager;
class CrabRobotManager;
/// <summary>
/// 蟹ロボットの基底クラスを定義する
/// </summary>
class CrabRobot
{
public:
	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//HPのゲッター、セッター
	int GetHP() const { return m_HP; }
	void SetHP(const int& HP) { m_HP = HP; }

	//攻撃力のゲッター、セッター
	int GetOffensivePower() const { return m_offensivePower; }
	void SetOffensivePower(const int& offensivePower) { m_offensivePower = offensivePower; }

	//当たり判定のゲッター
	Collider::Sphere* GetCollider() { return m_collider.get(); }

	//子のパーツの配列のゲッター
	std::vector<std::unique_ptr<ICrabRobotComponent>>& GetParts() { return m_parts; };

	//生存のゲッター、セッター
	bool GetSurvival() const { return m_survival; }
	void SetSurvival(const bool& survival) { m_survival = survival; }

	//反射ベクトルのゲッター、セッター
	void SetReflectionVector(const DirectX::SimpleMath::Vector3& reflectionVector) { m_reflectionVector = reflectionVector; }
	DirectX::SimpleMath::Vector3 GetReflectionVector() { return m_reflectionVector; }

	//動きの状態をゲッター
	ICrabRobotState* GetTurretMotion() {return m_turretMotion.get(); }

	//死亡の状態をゲッター
	ICrabRobotState* GetTurretKillMotion() { return m_turretKillMotion.get(); }

	//現在の状態セット
	void SetIState(ICrabRobotState* Istate)
	{
		m_pCurrentState = Istate;
		m_pCurrentState->Initialize();
	}

	//現在の状態のゲッター
	ICrabRobotState* GetIState() { return m_pCurrentState; }

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="Hp">HPの初期値</param>
	/// <param name="offensivePower">攻撃力の初期値</param>
	CrabRobot(const int& Hp, const int& offensivePower);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CrabRobot();

	
	/// <summary>
	/// 初期化する
	/// </summary>
	/// <param name="bulletManager">球の管理者のアドレス</param>
	/// <param name="crabRobotManager">蟹ロボットの管理者のアドレス</param>
	/// <param name="airshipManager">飛行船の管理者のアドレス</param>
	/// <param name="floor">床のアドレス</param>
	/// <param name="sandstormManager">砂嵐のアドレス</param>
	virtual void Initialize(
		BulletManager* bulletManager,
		CrabRobotManager* crabRobotManager,
		AirshipManager* airshipManager,
		Floor* floor,
		SandstormManager* sandstormManager
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
	/// パーツの描画
	/// </summary>
	void PartsRender();

	/// <summary>
	//パーツを生成する
	//</summary>
	//<param name="Parts">パーツのポインタ</param>
	void AddParts(std::unique_ptr<ICrabRobotComponent> Parts) { m_parts.emplace_back(move(Parts)); }

public:
	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="motion">通常の状態をポインタ</param>
	void AddTurrertMotion(std::unique_ptr<ICrabRobotState> motion) { m_turretMotion = std::move(motion); }

	/// <summary>
	/// 死亡の状態を生成
	/// </summary>
	/// <param name="killmotion">死亡の状態をポインタ</param>
	void AddTurretKillMotion(std::unique_ptr<ICrabRobotState> killmotion) { m_turretKillMotion = std::move(killmotion); }

private:
	//生存
	bool m_survival;

	//動きの状態ポインタ
	std::unique_ptr<ICrabRobotState> m_turretMotion;

	//死亡の状態のポインタ
	std::unique_ptr<ICrabRobotState> m_turretKillMotion;

	// 現在の状態のアドレス
	ICrabRobotState* m_pCurrentState;

	//球のポインタ
	BulletManager* m_pBulletManager;

	//飛行船のポインタ
	AirshipManager* m_pAirshipManager;

	//床のポインタ
	Floor* m_pFloor;

	//砂嵐の管理者のポインタ
	SandstormManager* m_pSandstormManager;

	//位置
	DirectX::SimpleMath::Vector3 m_position;

	//回転
	DirectX::SimpleMath::Quaternion m_rotate; 

	//HP
	int m_HP;

	//攻撃力
	int m_offensivePower;

	//反射ベクトル
	DirectX::SimpleMath::Vector3 m_reflectionVector;

	//パーツの配列のポインタ
	std::vector<std::unique_ptr<ICrabRobotComponent>> m_parts;

	//当たり判定のポインタ
	std::unique_ptr<Collider::Sphere> m_collider;

};
