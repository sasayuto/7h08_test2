#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"Scene/GameObjects/Models/Resources.h"
class Player;

/// <summary>
/// アイテムの基底クラスを定義する
/// </summary>
class Sun
{
public:
	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetRightDirect() const { return m_rightDirect; }
	void SetRightDirect(const DirectX::SimpleMath::Vector3& rightDirect) { m_rightDirect = rightDirect; }

	//位置のセッター、ゲッター
	float GetObjectsRight() const { return m_objectsRight; }
	void SetObjectsRight(const float& objectsRight) { m_objectsRight = objectsRight; }

	//回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//モデルのセッター、ゲッター
	DirectX::Model* GetSupplyPointModel() { return m_pSupplyPointModel; }
	void SetSupplyPointModel(DirectX::Model* supplyPointModel) { m_pSupplyPointModel = supplyPointModel; }

	//当たり判定のゲッター
	Collider::Sphere* GetCollider() { return m_collider.get(); }

	static const DirectX::SimpleMath::Vector3 INITIAL_POSITION;

	//位置
	static const DirectX::SimpleMath::Quaternion INITIAL_ROTATE;

	static const float SUNSET_TIME;
	static const float LIGHT_INTENSITY_UPPER_LIMIT;
	static const float LIGHT_INTENSITY_LOWER_LIMIT;
	static const float SUNSHINE_HOURS;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Sun();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Sun();

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">1フレーム時間</param>
	virtual void Update(const float& elapsedTime);

	/// <summary>
	/// 描画する
	/// </summary>
	virtual void Render();

	/// <summary>
	/// 後始末
	/// </summary>
	virtual void Finalize();
private:
	//位置
	DirectX::SimpleMath::Vector3 m_position;

	DirectX::SimpleMath::Vector3 m_rightDirect;

	//位置
	DirectX::SimpleMath::Quaternion m_rotate;

	//位置
	float m_objectsRight;

	//モデルのポインタ
	DirectX::Model* m_pSupplyPointModel;

	//当たり判定のポインタ
	std::unique_ptr<Collider::Sphere> m_collider;


};
