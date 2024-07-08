#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"../Objects.h"
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"

#include"MoveObjectsParts/IMoveObjectsComponent.h"
class Player;
class MoveObjectsManager;
/// <summary>
/// オブジェクトのクラスを定義する
/// </summary>
class MoveObjects
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

	//大まかな当たり判定のゲッター
	Collider::Sphere* GetRoughCollider() { return m_roughCollider.get(); }

	//モデルのセッター、ゲッター
	DirectX::Model* GetModel() { return m_pPartModel; }
	void SetModel(DirectX::Model* supplyPointModel) { m_pPartModel = supplyPointModel; }

	//位置のセッター、ゲッター
	bool GetSurvival() const { return m_survival; }
	void SetSurvival(const bool& survival) { m_survival = survival; }

	//位置のセッター、ゲッター
	bool GetAllSurvivalFlag() const { return m_allSurvivalFlag; }

	std::vector<std::unique_ptr<IMoveObjectsComponent>>& GetParts() { return m_parts; };

	static const float ANIMATION_TIME;//爆発モーションの時間

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MoveObjects();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~MoveObjects();

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize(BulletManager* bulletManager, MoveObjectsManager* benchManager);

	/// <summary>
	/// 更新する
	/// </summary>
	virtual void Update(const float& elapsedTime);

	/// <summary>
	/// 描画する
	/// </summary>
	virtual void Render();
		
	/// <summary>
	/// シャドウマップ用の画像を作る
	/// </summary>
	virtual void RenderShadowTex();

	virtual void SetpositionRandam(const float& min, const float& max);

public:
	/// <summary>
	/// パーツを生成する
	/// </summary>
	/// <param name="Parts">パーツのポインタ</param>
	void AddParts(std::unique_ptr<IMoveObjectsComponent> Parts) { m_parts.emplace_back(move(Parts)); }

private:
	//位置
	DirectX::SimpleMath::Vector3 m_position;

	//ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	//回転クオータニオン
	DirectX::SimpleMath::Quaternion m_rotate;

	//大まかな当たり判定のポインタ
	std::unique_ptr<Collider::Sphere> m_roughCollider;

	BulletManager* m_pBulletManager;

	MoveObjectsManager* m_pBenchManager;
	//生存
	bool m_survival;

	//経過時間
	float m_timer;

	bool m_killCountFlag;

	//全て生きているか
	bool m_allSurvivalFlag;

	//プロペラのモデル
	DirectX::Model* m_pPartModel;

	////パーツの配列のポインタ
	std::vector<std::unique_ptr<IMoveObjectsComponent>> m_parts;

};
