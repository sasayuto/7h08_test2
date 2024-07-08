#pragma once
#include <pch.h>
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"

class Respawn;
class Item;
class Enemy;
class Coin;
class Bullet;
class Objects;
struct IAirshipComponent;
struct IWindmillComponent;
class Floor;
struct IStreetLightComponent;
struct IBenchComponent;
class SandstormEffect;
struct ITurretComponent;
struct IMoveObjectsComponent;
struct IHouseMoveObjectsComponent;
/// <summary>
/// IPlayerComponentインタフェースを定義する
/// </summary>
interface  IPlayerComponent
{
	// 親のアドレスのセッター、ゲッター
	virtual IPlayerComponent* GetParent() = 0;
	virtual void SetParent(IPlayerComponent* parent) = 0;

	//子のパーツの配列のゲッター
	virtual std::vector<std::unique_ptr<IPlayerComponent>>& GetParts() = 0;
	virtual void AddPart(std::unique_ptr<IPlayerComponent> part) = 0;

	//位置のセッター、ゲッター
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;

	//位置のセッター、ゲッター
	virtual DirectX::SimpleMath::Vector3 GetProgressVector() const = 0;
	virtual void SetProgressVector(const DirectX::SimpleMath::Vector3& progressVector) = 0;

	//反射ベクトルのゲッターセッター
	virtual void SetMove(const DirectX::SimpleMath::Vector3& reflectionVector) = 0;
	virtual DirectX::SimpleMath::Vector3 GetMove()const = 0;


	//回転のゲッターセッター
	virtual DirectX::SimpleMath::Quaternion GetRotate() const = 0;
	virtual void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) = 0;

	//反射ベクトルのゲッターセッター
	virtual void SetReflectionVector(const DirectX::SimpleMath::Vector3& reflectionVector) = 0;
	virtual DirectX::SimpleMath::Vector3 GetReflectionVector()const = 0;

	//ランダムな回転のゲッターセッター
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
	virtual ~IPlayerComponent() = default;

	/// <summary>
	/// 初期化する
	/// </summary>
	/// <param name="angle">反射ベクトル</param>
	virtual void Initialize(const DirectX::SimpleMath::Vector3& reflectionVector) = 0;

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
	/// 爆発処理
	/// </summary>
	virtual void Explosion() = 0;

	/// <summary>
	/// 速度処理をする
	/// </summary>
	virtual void Speed() = 0;


	/// <summary>
	/// オブジェクトのとの当たり判定
	/// </summary>
	/// <param name="objects">オブジェクトのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionObjects(Objects* objects) = 0;

	/// <summary>
	///アイテムとの当たり判定
	/// </summary>
	/// <param name="objects">アイテムのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionItem(Item* item) = 0;

	/// <summary>
	/// 敵との当たり判定
	/// </summary>
	/// <param name="objects">敵のアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionEnemy(Enemy* enemy) = 0;

	/// <summary>
	/// コインとの当たり判定
	/// </summary>
	/// <param name="objects">コインのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionCoin(Coin* coin) = 0;

	/// <summary>
	/// 球との当たり判定
	/// </summary>
	/// <param name="objects">球のアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionBullet(Bullet* bullet) = 0;

	/// <summary>
	/// 床との当たり判定
	/// </summary>
	/// <param name="objects">床のアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionFloor(Floor* floor) = 0;

	/// <summary>
	/// 砂嵐との当たり判定
	/// </summary>
	/// <param name="objects">砂嵐のアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionSandstorm(SandstormEffect* sandstormEffect) = 0;

	/// <summary>
	/// 敵パーツとの当たり判定
	/// </summary>
	/// <param name="objects">敵パーツのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool Collision(IPlayerComponent* iPlayerComponent) = 0;

	/// <summary>
	/// 飛行船のパーツとの当たり判定
	/// </summary>
	/// <param name="objects">飛行船のパーツのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionAirshipParts(IAirshipComponent* iAirshipComponent) = 0;

	/// <summary>
	/// 風車のパーツとの当たり判定
	/// </summary>
	/// <param name="objects">風車のパーツのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionWindmillParts(IWindmillComponent* HitAirshipPart) = 0;

	/// <summary>
	/// 街灯のパーツとの当たり判定
	/// </summary>
	/// <param name="objects">街灯のパーツのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionStreetLightParts(IStreetLightComponent* iStreetLightComponent) = 0;

	/// <summary>
	/// ベンチのパーツとの当たり判定
	/// </summary>
	/// <param name="objects">ベンチのパーツのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionBenchParts(IBenchComponent* iBenchComponent) = 0;

	/// <summary>
	/// 破壊オブジェクトのパーツとの当たり判定
	/// </summary>
	/// <param name="objects">ベンチのパーツのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionIMoveObjectsParts(IMoveObjectsComponent* iMoveObjectsComponent) = 0;

	/// <summary>
	/// 破壊オブジェクトのパーツとの当たり判定
	/// </summary>
	/// <param name="objects">ベンチのパーツのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionIHouseMoveObjectsParts(IHouseMoveObjectsComponent* iHouseMoveObjectsComponent) = 0;

	/// <summary>
	/// タレットのパーツとの当たり判定
	/// </summary>
	/// <param name="objects">タレットのパーツのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionTurretPart(ITurretComponent* iTurretComponent) = 0;

	/// <summary>
	/// 後処理をおこなう
	/// </summary>
	virtual void Finalize() = 0;
};
