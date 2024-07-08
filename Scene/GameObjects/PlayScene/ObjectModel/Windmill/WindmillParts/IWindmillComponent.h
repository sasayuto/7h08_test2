#pragma once
#include <pch.h>
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"

class Bullet;
class Player;
struct IPlayerComponent;
class Enemy;
class Airship;
/// <summary>
/// IPlayerComponentインタフェースを定義する
/// </summary>
interface IWindmillComponent
{
	// 親のアドレスのセッター、ゲッター
	virtual IWindmillComponent* GetParent() = 0;
	virtual void SetParent(IWindmillComponent* parent) = 0;

	//
	virtual std::vector<std::unique_ptr<IWindmillComponent>>& GetParts() = 0;
	virtual void AddPart(std::unique_ptr<IWindmillComponent> part) = 0;

	//位置のセッター、ゲッター
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;

	//回転のゲッターセッター
	virtual DirectX::SimpleMath::Quaternion GetRotate() const = 0;
	virtual void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) = 0;

	//モデルのセッター、ゲッター
	virtual DirectX::Model* GetPartModel() = 0;
	virtual void SetPartModel(DirectX::Model* supplyPointModel) = 0;

	//当たり判定のゲッター
	virtual Collider::OBB* GetCollider() = 0;

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~IWindmillComponent() = default;

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	virtual void Update(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	/// 描画する
	/// </summary>
	virtual void Render() = 0;
	
	/// <summary>
	/// シャドウマップ用の画像を作る
	/// </summary>
	virtual void RenderShadowTex() = 0;

	/// <summary>
	/// 当たり判定の処理をする
	/// </summary>
	virtual IWindmillComponent* Collision(Player* player) = 0;
	virtual bool CollisionPlayer(Player* player) = 0;
	virtual bool CollisionEnemy(Enemy* enemy) = 0;
	virtual IWindmillComponent* Collision(Airship* airship) = 0;
	virtual bool Collision(Bullet* bullet) = 0;

	/// <summary>
	/// 後処理をおこなう
	/// </summary>
	virtual void Finalize() = 0;
};
