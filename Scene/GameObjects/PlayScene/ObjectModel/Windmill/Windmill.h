#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"../Objects.h"

#include"WindmillParts/IWindmillComponent.h"
class Player;

/// <summary>
/// オブジェクトのクラスを定義する
/// </summary>
class Windmill 
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

	std::vector<std::unique_ptr<IWindmillComponent>>& GetParts() { return m_parts; };

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Windmill();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Windmill();

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新する
	/// </summary>
	virtual void Update();

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
	void AddParts(std::unique_ptr<IWindmillComponent> Parts) { m_parts.emplace_back(move(Parts)); }

	////パーツの配列のポインタ
	std::vector<std::unique_ptr<IWindmillComponent>> m_parts;

private:
	//位置
	DirectX::SimpleMath::Vector3 m_position;

	//回転クオータニオン
	DirectX::SimpleMath::Quaternion m_rotate;

	//大まかな当たり判定のポインタ
	std::unique_ptr<Collider::Sphere> m_roughCollider;
};
