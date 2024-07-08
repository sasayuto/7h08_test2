#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"

class Player;
class Enemy;
/// <summary>
/// 地面のクラスを定義する
/// </summary>
class Floor
{
public:
	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//モデルののセッター、ゲッター
	DirectX::Model* GetModel() { return m_objectsModel; }
	void SetModel(DirectX::Model * objectsModel) { m_objectsModel = objectsModel; }
	//回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//当たり判定のゲッター
	Collider::OBB* GetCollider() { return m_collider.get(); }

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Floor();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Floor();

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
	/// プレイヤーと当たり判定
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	virtual void CheckHitPlayer(Player* player);

	/// <summary>
	/// プレイヤーと当たり判定
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	virtual void CheckHitEnemy(Enemy* enemy);

private:
	//位置
	DirectX::SimpleMath::Vector3 m_position;

	//位置
	DirectX::SimpleMath::Quaternion m_rotate;

	//モデルのポインタ
	DirectX::Model* m_objectsModel;

	//当たり判定のポインタ
	std::unique_ptr<Collider::OBB> m_collider;

};
