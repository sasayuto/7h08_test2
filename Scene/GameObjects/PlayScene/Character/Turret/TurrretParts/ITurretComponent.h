#pragma once
#include <pch.h>
#include"Scene/GameObjects/PlayScene/Colliider/CollisionOLL.h"

class Bullet;
class Player;
class Enemy;
class Airship;
/// <summary>
/// ITurretComponentインタフェースを定義する
/// </summary>
interface ITurretComponent
{
	// 親のアドレスのセッター、ゲッター
	virtual ITurretComponent* GetParent() = 0;

	//子のパーツの配列のゲッター
	virtual std::vector<std::unique_ptr<ITurretComponent>>& GetParts() = 0;
	virtual void AddPart(std::unique_ptr<ITurretComponent> part) = 0;

	//位置のセッター、ゲッター
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;

	//回転のゲッターセッター
	virtual DirectX::SimpleMath::Quaternion GetRotate() const = 0;
	virtual void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) = 0;

	//生存のセッター、ゲッター
	virtual bool GetSurvival() const = 0;
	virtual void SetSurvival(const bool& survival) = 0;

	//HPのゲッター、セッター
	virtual int GetHp() const = 0;
	virtual void SetHp(const int& Hp) = 0;

	//時間のゲッター、セッター
	virtual float GetTimer() const = 0;
	virtual void SetTimer(const float& timer) = 0;

	//死亡回転のゲッターセッター
	virtual DirectX::SimpleMath::Quaternion GetRandomRotate() const = 0;
	virtual void SetRandomRotate(const DirectX::SimpleMath::Quaternion& killRotate) = 0;

	//重力のゲッター、セッター
	virtual float GetGravity() const = 0;
	virtual void SetGravity(const float& gravity) = 0;

	//モデルのセッター、ゲッター
	virtual DirectX::Model* GetPartModel() = 0;
	virtual void SetPartModel(DirectX::Model* supplyPointModel) = 0;

	//当たり判定のゲッター
	virtual Collider::MultipleHitDetermination* GetCollider() = 0;

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ITurretComponent() = default;

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="position">１フレーム時間</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	virtual void Update(
		const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	/// 爆発処理
	/// </summary>
	/// <param name="position">１フレーム時間</param>
	virtual void Explosion(const float& elapsedTime) = 0;


	/// <summary>
	/// 描画する
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// 当たり判定の処理をする
	/// </summary>
	virtual bool CollisionPlayer(Player* player) = 0;
	virtual bool CollisionBullet(Bullet* bullet) = 0;

	/// <summary>
	/// 後処理をおこなう
	/// </summary>
	virtual void Finalize() = 0;
};
