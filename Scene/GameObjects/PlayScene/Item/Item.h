#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"Scene/GameObjects/Models/Resources.h"
class Player;

/// <summary>
/// アイテムの基底クラスを定義する
/// </summary>
class Item
{
public:
	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//大きさのセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetScale() const { return m_scale; }
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }

	//使用フラグのセッター、ゲッター
	bool GetSurvival() const { return m_survival; }
	void SetSurvival(const bool& survival) { m_survival = survival; }

	//回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Matrix GetWorld() const { return m_world; }
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { m_world = world; }

	//モデルのセッター、ゲッター
	DirectX::Model* GetSupplyPointModel() { return m_pSupplyPointModel; }
	void SetSupplyPointModel(DirectX::Model* supplyPointModel) { m_pSupplyPointModel = supplyPointModel; }

	//当たり判定のゲッター
	Collider::Sphere* GetCollider() { return m_collider.get(); }

private:
	//位置
	DirectX::SimpleMath::Vector3 m_position;

	//位置
	DirectX::SimpleMath::Quaternion m_rotate;

	//大きさ
	DirectX::SimpleMath::Vector3 m_scale;

	//使用フラグ
	bool m_survival;

	//モデルのポインタ
	DirectX::Model* m_pSupplyPointModel;

	//当たり判定のポインタ
	std::unique_ptr<Collider::Sphere> m_collider;
	DirectX::SimpleMath::Matrix m_world;

public:
	//円にランダムに生成
	void SetpositionRandam(const float& min, const float& max);

	/// <summary>
	/// 回復をさせる
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	virtual void Recovery(Player* player);

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Item();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Item();

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
	/// シャドウマップ用の画像を作る
	/// </summary>
	virtual void RenderShadowTex();

	/// <summary>
	/// 後始末
	/// </summary>
	virtual void Finalize();
};
