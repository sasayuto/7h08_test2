#pragma once
#include <pch.h>
#include"IPlayerComponent.h"

#include"Scene/GameObjects/PlayScene/Ground/Floor/Floor.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/AirshipParts/IAirshipComponent.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Windmill/WindmillParts/IWindmillComponent.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/StreetLight/StreetLightParts/IStreetLightComponent.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Bench/BenchParts/IBenchComponent.h"
#include"Scene/GameObjects/PlayScene/Character/Turret/TurrretParts/ITurretComponent.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/HouseMoveObjects/IHouseMoveObjectsComponent.h"
#include"Scene/GameObjects/PlayScene/Effect/SandstormEffect.h"
/// <summary>
/// PlayerComponentのクラスを定義する
/// </summary>
class  PlayerComponent :public IPlayerComponent
{
public:
	// 親のゲッターセッター
	IPlayerComponent* GetParent()override { return m_pParent; }
	void SetParent(IPlayerComponent* parent) override { m_pParent = parent; }

	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position)override { m_position = position; }

	//回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Quaternion GetRotate() const override { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate)override { m_rotate = rotate; }

	//反射ベクトルのゲッターセッター
	void SetReflectionVector(const DirectX::SimpleMath::Vector3& reflectionVector)override { m_reflectionVector = reflectionVector; }
	DirectX::SimpleMath::Vector3 GetReflectionVector()const override { return m_reflectionVector; }

	//反射ベクトルのゲッターセッター
	void SetMove(const DirectX::SimpleMath::Vector3& move)override { m_move = move; }
	DirectX::SimpleMath::Vector3 GetMove()const override { return m_move; }

	//死亡回転のゲッターセッター
	DirectX::SimpleMath::Quaternion GetRandomRotate() const override { return m_randomRotate; }
	void SetRandomRotate(const DirectX::SimpleMath::Quaternion& killRotate)override { m_randomRotate = killRotate; }

	//重力のゲッター、セッター
	float GetGravity() const override{ return m_gravity; }
	void SetGravity(const float& gravity) override{ m_gravity = gravity; }

	//モデルのセッター、ゲッター
	DirectX::Model* GetPartModel()override { return m_pPartModel; }
	void SetPartModel(DirectX::Model* supplyPointModel)override { m_pPartModel = supplyPointModel; }

	//位置のセッター、ゲッター
	virtual DirectX::SimpleMath::Vector3 GetProgressVector() const override { return m_progressVector; };
	virtual void SetProgressVector(const DirectX::SimpleMath::Vector3& progressVector) override { m_progressVector = progressVector; };

	//当たり判定のゲッター
	Collider::OBB* GetCollider() override { return m_collider.get(); }

	//子のパーツのゲッター
	std::vector<std::unique_ptr<IPlayerComponent>>& GetParts()override { return m_PlayerParts; }

	//子のパーツを生成
	void AddPart(std::unique_ptr<IPlayerComponent> part) override{ m_PlayerParts.push_back(std::move(part)); }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	PlayerComponent(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) :
		m_pParent(parent),
		m_position(position),
		m_rotate(angle),
		m_collider(nullptr),
		m_pPartModel(nullptr),
		m_killrotate(DirectX::SimpleMath::Quaternion::Identity),
		m_gravity(0),
		m_randomRotate(DirectX::SimpleMath::Quaternion::Identity),
		m_reflectionVector(),
		m_progressVector(DirectX::SimpleMath::Vector3::Zero),
		m_move()
	{	//当たり判定を生成
		m_collider = std::make_unique<Collider::OBB>();
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~PlayerComponent() override {}

	/// <summary>
	/// 初期化する
	/// </summary>
	/// <param name="angle">反射ベクトル</param>
	virtual void Initialize(const DirectX::SimpleMath::Vector3& reflectionVector)override { reflectionVector; }

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	virtual void Update(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) override {
		position; angle;
	}

	/// <summary>
	/// 描画する
	/// </summary>
	virtual void Render() override {}

		/// <summary>
	/// シャドウマップ用の画像を作る
	/// </summary>
	virtual void RenderShadowTex() override {
		//スケーリング、位置調整、回転をさせる
		DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
		DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
		DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

		world = rotate * translation;
		// 飛行機の描画
		Draw::GetInstance()->ShadowMapTexCreateNoPicture(GetPartModel(), world);

		//Draw::GetInstance()->TestCubeModel(
		//	GetPartModel()->meshes[0]->boundingBox.Extents, 
		//	GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		//	GetRotate()
		//);

			// パーツを更新する
		for (auto& playerPart : GetParts())
		{
			playerPart->RenderShadowTex();
		}
	};

	/// <summary>
	/// 爆発処理
	/// </summary>
	virtual void Explosion() override {}

	/// <summary>
	/// 速度処理をする
	/// </summary>
	virtual void Speed() override {}

	/// <summary>
	/// オブジェクトのとの当たり判定
	/// </summary>
	/// <param name="objects">オブジェクトのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionObjects(Objects* objects) override {
		//当たっていたら反射ベクトルを返す
		DirectX::SimpleMath::Vector3 reflectionVector = objects->GetCollider()->CheckHitreflectionVector(GetCollider(), GetMove());
		if (reflectionVector != DirectX::SimpleMath::Vector3::Zero)
		{
			//書けば当たったパーツの後のパーツの判定を行ってくれるが
			//死んだときにパーツがばらけ反射ベクトルにとび次ぎは当たらないので割愛
			// 他のプレイヤーの当たり判定も同様
			for (auto& playerPart : GetParts())
				playerPart->CollisionObjects(objects);

			//まだしっかり反射ベクトルがとれないので反対方向に飛ばす
			reflectionVector = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ, GetRotate());
			SetReflectionVector(-reflectionVector * 2);
			SetGravity(-0.1f);
			return true;
		}

		for (auto& playerPart : GetParts())
		{
			// パーツを更新する
			if (playerPart->CollisionObjects(objects))
				return true;
		}
		return false;
	}

	/// <summary>
	///アイテムとの当たり判定
	/// </summary>
	/// <param name="objects">アイテムのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionItem(Item* item)override {
		if (GetCollider()->CheckHitSphere(item->GetCollider()))return true;
		for (auto& playerPart : GetParts())
		{
			// パーツを更新する
			if (playerPart->CollisionItem(item)) return true;
		}
		return false;
	}

	/// <summary>
	/// 敵との当たり判定
	/// </summary>
	/// <param name="objects">敵のアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionEnemy(Enemy* enemy) override {
		if (GetCollider()->CheckHitSphere(enemy->GetCollider()))return true;
		for (auto& playerPart : GetParts())
		{
			// パーツを更新する
			if (playerPart->CollisionEnemy(enemy)) return true;
		}
		return false;
	}

	/// <summary>
	/// 砂嵐との当たり判定
	/// </summary>
	/// <param name="objects">砂嵐のアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionSandstorm(SandstormEffect* sandstormEffect)
	{
		if (GetCollider()->CheckHitOBBBox(sandstormEffect->GetCollider()))
		{
			SetGravity(-0.1f);
			//常時触れていることがあるので1つのパーツが当たっても他のパーツの当たり判定もとる
			for (auto& playerPart : GetParts())
				// パーツを更新する
				playerPart->CollisionSandstorm(sandstormEffect);
			return true;
		}
		for (auto& playerPart : GetParts())
			// パーツを更新する
			if (playerPart->CollisionSandstorm(sandstormEffect)) return true;
		return false;
	}



	/// <summary>
	/// コインとの当たり判定
	/// </summary>
	/// <param name="objects">コインのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionCoin(Coin* coin)override {
		if (GetCollider()->CheckHitSphere(coin->GetCollider()))return true;
		for (auto& playerPart : GetParts())
		{
			// パーツを更新する
			if (playerPart->CollisionCoin(coin)) return true;
		}
		return false;
	}

	/// <summary>
	/// 球との当たり判定
	/// </summary>
	/// <param name="objects">球のアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionBullet(Bullet* bullet)override {
		if (GetCollider()->CheckHitSphere(bullet->GetCollider()))
		{
			SetGravity(-0.1f);
			return true;
		}for (auto& playerPart : GetParts())
		{
			// パーツを更新する
			if (playerPart->CollisionBullet(bullet)) return true;
		}
		return false;
	}

	/// <summary>
	/// 敵パーツとの当たり判定
	/// </summary>
	/// <param name="objects">敵パーツのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool Collision(IPlayerComponent* iPlayerComponent)override
	{
		if (GetCollider()->CheckHitOBB(iPlayerComponent->GetCollider()))return true;
		for (auto& playerPart : GetParts())
		{
			// パーツを更新する
			if (playerPart->Collision(iPlayerComponent)) return true;
		}
		return false;

	}

	/// <summary>
	/// 飛行船のパーツとの当たり判定
	/// </summary>
	/// <param name="objects">飛行船のパーツのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionAirshipParts(IAirshipComponent* iAirshipComponent)override
	{
		//当たっていたら反射ベクトルを返す
		DirectX::SimpleMath::Vector3 reflectionVector = iAirshipComponent->GetCollider()->CheckHitreflectionVector(GetCollider());
		if (reflectionVector != DirectX::SimpleMath::Vector3::Zero)
		{
			////死んだときにパーツがばらけるが反射ベクトルにとび次ぎは当たらないので割愛
			//for (auto& playerPart : GetParts())
			//	// パーツを更新する
			//	playerPart->Collision(iWindmillComponent);

			//まだしっかり反射ベクトルがとれないので反対方向に飛ばす
			reflectionVector = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ, GetRotate());
			SetReflectionVector(-reflectionVector * 2);
			SetGravity(-0.1f);
			return true;
		}
		for (auto& playerPart : GetParts())
		{
			// パーツを更新する
			if (playerPart->CollisionAirshipParts(iAirshipComponent)) return true;
		}
		return false;
	}

	/// <summary>
	/// 床との当たり判定
	/// </summary>
	/// <param name="objects">床のアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionFloor(Floor* floor)
	{
		if (GetCollider()->CheckHitOBB(floor->GetCollider()))
		{
			SetGravity(-0.1f);

			return true;
		}
		for (auto& playerPart : GetParts())
		{
			// パーツを更新する
			if (playerPart->CollisionFloor(floor)) return true;
		}
		return false;
	}

	/// <summary>
	/// 風車のパーツとの当たり判定
	/// </summary>
	/// <param name="objects">風車のパーツのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionWindmillParts(IWindmillComponent* iWindmillComponent)
	{
		//当たっていたら反射ベクトルを返す
		DirectX::SimpleMath::Vector3 reflectionVector = iWindmillComponent->GetCollider()->CheckHitreflectionVector(GetCollider());
		if (reflectionVector != DirectX::SimpleMath::Vector3::Zero)
		{
			//まだしっかり反射ベクトルがとれないので反対方向に飛ばす
			reflectionVector = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ, GetRotate());
			SetReflectionVector(-reflectionVector * 2);
			SetGravity(-0.1f);
			return true;
		}
		for (auto& playerPart : GetParts())
		{
			// パーツを更新する
			if (playerPart->CollisionWindmillParts(iWindmillComponent)) return true;
		}
		return false;

	}

	/// <summary>
	/// 街灯のパーツとの当たり判定
	/// </summary>
	/// <param name="objects">街灯のパーツのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionStreetLightParts(IStreetLightComponent* iStreetLightComponent)
	{
		if (iStreetLightComponent->GetCollider()->CheckHitOBB(GetCollider()))
			return true;

		for (auto& playerPart : GetParts())
			// パーツを更新する
			if (playerPart->CollisionStreetLightParts(iStreetLightComponent))
				return true;

		return false;
	}

	virtual bool CollisionIHouseMoveObjectsParts(IHouseMoveObjectsComponent* iHouseMoveObjectsComponent)
	{
		//当たっていたら反射ベクトルを返す
		DirectX::SimpleMath::Vector3 reflectionVector = iHouseMoveObjectsComponent->GetCollider()->CheckHitreflectionVector(GetCollider(),m_move);
		if (reflectionVector != DirectX::SimpleMath::Vector3::Zero)
		{
			for (auto& playerPart : GetParts())
				// パーツを更新する
				playerPart->CollisionIHouseMoveObjectsParts(iHouseMoveObjectsComponent);

			//まだしっかり反射ベクトルがとれないので反対方向に飛ばす
			reflectionVector = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ, GetRotate());
			SetReflectionVector(-reflectionVector * 2);
			SetGravity(-0.1f);
			return true;
		}
		for (auto& playerPart : GetParts())
			// パーツを更新する
			if (playerPart->CollisionIHouseMoveObjectsParts(iHouseMoveObjectsComponent))
				return true;

		return false;
	}

	/// <summary>
	/// ベンチのパーツとの当たり判定
	/// </summary>
	/// <param name="objects">ベンチのパーツのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionBenchParts(IBenchComponent* iBenchComponent)
	{
		if (iBenchComponent->GetCollider()->CheckHitOBB(GetCollider()))
			return true;

		for (auto& playerPart : GetParts())
			// パーツを更新する
			if (playerPart->CollisionBenchParts(iBenchComponent))
				return true;

		return false;
	}
	/// <summary>
	/// 破壊オブジェクトのパーツとの当たり判定
	/// </summary>
	/// <param name="objects">ベンチのパーツのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionIMoveObjectsParts(IMoveObjectsComponent* iMoveObjectsComponent)
	{
		if (iMoveObjectsComponent->GetCollider()->CheckHitOBB(GetCollider()))
			return true;

		for (auto& playerPart : GetParts())
			// パーツを更新する
			if (playerPart->CollisionIMoveObjectsParts(iMoveObjectsComponent))
				return true;

		return false;

	}

	/// <summary>
	/// タレットのパーツとの当たり判定
	/// </summary>
	/// <param name="objects">タレットのパーツのアドレス</param>
	/// <returns>Hitでtrue</returns>
	virtual bool CollisionTurretPart(ITurretComponent* iTurretComponent)
	{
		if (iTurretComponent->GetCollider()->CheckAllHit(GetCollider()))
		{
			SetGravity(-0.1f);
			for (auto& playerPart : GetParts())
				// パーツを更新する
				playerPart->CollisionTurretPart(iTurretComponent);

			return true;
		}

		for (auto& playerPart : GetParts())
			// パーツを更新する
			if (playerPart->CollisionTurretPart(iTurretComponent))
				return true;

		return false;
	}

	/// <summary>
	/// 後処理をおこなう
	/// </summary>
	virtual void Finalize()override {}
private:
	//プロペラの位置
	DirectX::SimpleMath::Vector3 m_position;
	
	//プロペラの位置
	DirectX::SimpleMath::Vector3 m_progressVector;

	//プロペラの方向
	DirectX::SimpleMath::Quaternion m_rotate;

	//プロペラのモデル
	DirectX::Model* m_pPartModel;

	//当たり判定のポインタ
	std::unique_ptr<Collider::OBB> m_collider;

	//親のポインタ
	IPlayerComponent* m_pParent;

	//プロペラの死亡時の回転
	DirectX::SimpleMath::Quaternion m_killrotate;

	//プロペラの死亡時のランダムな方向に飛ばす回転
	DirectX::SimpleMath::Quaternion m_randomRotate;

	//重力
	float m_gravity;

	//パーツの配列のポインタ
	std::vector<std::unique_ptr<IPlayerComponent>> m_PlayerParts;

	//反射ベクトル
	DirectX::SimpleMath::Vector3 m_reflectionVector;

	//反射ベクトル
	DirectX::SimpleMath::Vector3 m_move;
};
