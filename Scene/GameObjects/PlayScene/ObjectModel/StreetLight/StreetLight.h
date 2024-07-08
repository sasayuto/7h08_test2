#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"../Objects.h"
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"

#include"StreetLightParts/IStreetLightComponent.h"
class Player;
class StreetLightManager;
/// <summary>
/// オブジェクトのクラスを定義する
/// </summary>
class StreetLight
{
public:
	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//大まかな当たり判定のゲッター
	Collider::Sphere* GetRoughCollider() { return m_roughCollider.get(); }

	//位置のセッター、ゲッター
	bool GetSurvival() const { return m_survival; }
	void SetSurvival(const bool& survival) { m_survival = survival; }

	//位置のセッター、ゲッター
	bool GetAllSurvivalFlag() const { return m_allSurvivalFlag; }


	std::vector<std::unique_ptr<IStreetLightComponent>>& GetParts() { return m_parts; };

	static const float ANIMATION_TIME;//爆発モーションの時間

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StreetLight();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StreetLight();

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize(BulletManager* bulletManager, StreetLightManager* streetLightManager);

	/// <summary>
	/// 更新する
	/// </summary>
	virtual void Update(const float& elapsedTime);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

	/// <summary>
	/// シャドウマップ用の画像を作る
	/// </summary>
	void RenderShadowTex();

	void SetpositionRandam(const float& min, const float& max);

private:
	/// <summary>
/// パーツを生成する
/// </summary>
/// <param name="Parts">パーツのポインタ</param>
	void AddParts(std::unique_ptr<IStreetLightComponent> Parts) { m_parts.emplace_back(move(Parts)); }

	////パーツの配列のポインタ
	std::vector<std::unique_ptr<IStreetLightComponent>> m_parts;

private:
	//プロペラのモデル
	DirectX::Model* m_pStreetLight;

	//位置
	DirectX::SimpleMath::Vector3 m_position;

	//回転クオータニオン
	DirectX::SimpleMath::Quaternion m_rotate;

	//回転クオータニオン
	DirectX::SimpleMath::Matrix m_world;

	//大まかな当たり判定のポインタ
	std::unique_ptr<Collider::Sphere> m_roughCollider;

	BulletManager* m_pBulletManager;
	//生存
	bool m_survival;

	//経過時間
	float m_timer;
	//全て生きているか
	bool m_allSurvivalFlag;

	StreetLightManager* m_pStreetLightManager;

	bool m_killCountFlag;
};
