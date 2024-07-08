#pragma once
#include <pch.h>
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"

class Bullet;
class Objects;
class Player;
class Enemy;
/// <summary>
/// IPlayerComponentインタフェースを定義する
/// </summary>
interface  IAirshipComponent
{
	// 親のアドレスのセッター、ゲッター
	virtual IAirshipComponent* GetParent() = 0;
	virtual void SetParent(IAirshipComponent* parent) = 0;

	virtual std::vector<std::unique_ptr<IAirshipComponent>>& GetParts() = 0;
	virtual void AddPart(std::unique_ptr<IAirshipComponent> part) = 0;

	//位置のセッター、ゲッター
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;

	//回転のゲッターセッター
	virtual DirectX::SimpleMath::Quaternion GetRotate() const = 0;
	virtual void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) = 0;

	//死亡回転のゲッターセッター
	virtual DirectX::SimpleMath::Quaternion GetKillRotate() const = 0;
	virtual void SetKillRotate(const DirectX::SimpleMath::Quaternion& killRotate) = 0;

	//死亡回転のゲッターセッター
	virtual DirectX::SimpleMath::Quaternion GetRandomRotate() const = 0;
	virtual void SetRandomRotate(const DirectX::SimpleMath::Quaternion & killRotate) = 0;

	//重力のゲッター、セッター
	virtual float GetGravity() const = 0;
	virtual void SetGravity(const float& gravity) = 0;

	//モデルのセッター、ゲッター
	virtual DirectX::Model* GetPartModel() = 0;
	virtual void SetPartModel(DirectX::Model* supplyPointModel) = 0;

	//当たり判定のゲッター
	virtual Collider::OBB* GetCollider() = 0;

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~IAirshipComponent() = default;

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
	virtual void RenderShadowTex()=0;

	/// <summary>
	/// 爆発処理
	/// </summary>
	virtual void Explosion() = 0;

	/// <summary>
	/// 速度処理をする
	/// </summary>
	virtual void Speed() = 0;

	/// <summary>
	/// 当たり判定の処理をする
	/// </summary>
	/// <param name="respawnManager">リスポーン地点のアドレス</param>
	/// <param name="supplyPointManager">アイテムのアドレス</param>
	/// <param name="enemyManager">敵のマネージャーのアドレス</param>
	/// <param name="coinManager">コインのアドレス</param>
	/// <param name="bulletManager">球のアドレス</param>
	/// <param name="objectsManager">オブジェクトのアドレス</param>
	/// <param name="objectsManager">木のアドレス</param>
	virtual bool Collision(Objects* objects) = 0;
	virtual bool CollisionPlayer(Player* player) = 0;
	virtual bool CollisionEnemy(Enemy* enemy) = 0;
	virtual bool CollisionBullet(Bullet* bullet) = 0;

	/// <summary>
	/// 後処理をおこなう
	/// </summary>
	virtual void Finalize() = 0;
};
