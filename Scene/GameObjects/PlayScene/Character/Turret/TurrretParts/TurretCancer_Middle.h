#pragma once
#include"TurretComponent.h"

class BulletManager;
/// <summary>
/// TurretCancer_Middleクラスを定義する
/// </summary>
class TurretCancer_Middle : public TurretComponent
{
public:
	static const float FALL_SPEED_ACCELERATION;		//落下の加速度		(m/s)
	static const float EXPLOSIVE_ROTATE;		//モデルの回転の速さ(°/s）
	static const float EXPLOSIVE_RANDOM_POWER;	//爆発のランダムな方向のパワー		(m/s)
	static const float EXPLOSIVE_POWER;			//爆発の方向のパワー		(m/s)
	static const float BULLET_COOL_TIME;		//球クールタイム	(s)
	static const int MAX_HP;	//HP

public:
	/// <summary>
	/// 処理を実行する
	/// </summary>
	/// <param name="parent">球の管理者のアドレス</param>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	TurretCancer_Middle(
		BulletManager* bulletManager,
		ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TurretCancer_Middle()override;

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="position">１フレーム時間</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	void Update(
		const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	)override;

	/// <summary>
	///爆発処理
	/// </summary>
	/// <param name="position">１フレーム時間</param>
	void Explosion(const float& elapsedTime)override;

	/// <summary>
	/// 描画する
	/// </summary>
	void Render()override;

	/// <summary>
	/// 後処理
	/// </summary>
	void Finalize()override;

private:

	//球の管理者のポインタ
	BulletManager* m_pBulletManager;

	//球のクールタイム
	float m_bulletCoolTime;

	DirectX::SimpleMath::Quaternion m_CancerAngle;
	float b = 0;
	bool h = false;


};