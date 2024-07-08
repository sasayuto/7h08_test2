#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"Scene/GameObjects/PlayScene/Colliider/CollisionOLL.h"

class Player;

/// <summary>
/// オブジェクトの基底クラスを定義する
/// </summary>
class Objects
{
	
public:
	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//位置のセッター、ゲッター
	void SetRotateJson(const DirectX::SimpleMath::Vector3& rotate) {
		m_rotate = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			DirectX::XMConvertToRadians(rotate.x),
			DirectX::XMConvertToRadians(rotate.y),
			DirectX::XMConvertToRadians(rotate.z)
		);
	}

	//回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Matrix GetWorld() const { return m_world; }
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { m_world = world; }

	//モデルののセッター、ゲッター
	DirectX::Model* GetObjectsModel() { return m_objectsModel; }
	void SetObjectsModel(DirectX::Model * objectsModel) { m_objectsModel = objectsModel; }

	//当たり判定のゲッター
	Collider::MultipleHitDetermination* GetCollider() { return m_collider.get(); }

	//大まかな当たり判定のゲッター
	Collider::Sphere* GetRoughCollider() { return m_roughCollider.get(); }

private:
	//位置
	DirectX::SimpleMath::Vector3 m_position;
	//回転クオータニオン
	DirectX::SimpleMath::Quaternion m_rotate;

	//回転クオータニオン
	DirectX::SimpleMath::Matrix m_world;

	//モデルのポインタ
	DirectX::Model* m_objectsModel;

	//当たり判定のポインタ
	std::unique_ptr<Collider::MultipleHitDetermination> m_collider;

	//大まかな当たり判定のポインタ
	std::unique_ptr<Collider::Sphere> m_roughCollider;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Objects();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Objects();

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新する
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
	/// 敵をランダムに生成
	/// </summary>
	/// <param name="min">最小</param>
	/// <param name="max">最大</param>
	void SetpositionRandam(const float& min, const float& max);

};
