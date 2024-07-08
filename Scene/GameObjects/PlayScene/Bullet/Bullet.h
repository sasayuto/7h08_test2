#pragma once
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"

/// <summary>
/// 球の基底クラスを定義する
/// </summary>
class Bullet
{
public:
	//球の使用者
	enum class BulletParent
	{
		None,
		PlayerBullet,
		EnemyBullet,
		OverID
	};

	//球の種類
	enum class BulletType
	{
		None,
		Type1,
		Type2,
		Type3,
		Type4,
		Turret,
		OverID
	};

	//使用中のゲッター、セッター
	bool GetisActive() const { return m_isActive; }
	void SetisActive(const bool& flag) { m_isActive = flag; }

	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetMove() const { return m_move; }
	void SetMove(const DirectX::SimpleMath::Vector3& Move) { m_move = Move; }

	//回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Quaternion GetRotate() const  { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//球のタイプのゲッター
	Bullet::BulletParent GetParentType() const {return m_bulletparent; }

	int GetOffensivePower()const { return m_offensivePower; }
	//大きさのセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetScale() const { return m_scale; }
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }

	float GetSpeed()const { return m_speed; }
	//当たり判定のゲッター
	Collider::Sphere* GetCollider() { return m_collider.get(); }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Bullet(const float& speed,const int& offensivePower, const float& scale);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Bullet();

	/// <summary>
	/// 初期化する
	/// </summary>
	/// <param name="bulletType">球の使用者</param>
	/// <param name="shooterType">球の種類</param>
	/// <param name="position">使用時の位置</param>
	/// <param name="rotate">使用時の角度</param>
	virtual void Initialize(
		const BulletParent& shooterType, 
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& rotate
	);

	/// <summary>
	/// 処理を実行する
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画する
	/// </summary>
	virtual void Render();

	/// <summary>
	/// シャドウマップ用の画像を作る
	/// </summary>
	virtual void RenderShadowTex();

	/// <summary>
	/// 後始末
	/// </summary>
	virtual void Finalize();

private:
	//発射対象
	BulletParent m_bulletparent;

	//球のポジション
	DirectX::SimpleMath::Vector3 m_position;

	//球の大きさ
	DirectX::SimpleMath::Vector3 m_scale;

	//球の速さ
	float m_speed;

	//球の攻撃力
	int m_offensivePower;

	//球の方向
	DirectX::SimpleMath::Quaternion m_rotate;

	//使用されているかのグラフ
	bool m_isActive;

	// 球のモデルのポインタ
	DirectX::Model* m_bulletModel;

	//当たり判定のポインタ
	std::unique_ptr<Collider::Sphere> m_collider;

	DirectX::SimpleMath::Vector3 m_move;
}; 