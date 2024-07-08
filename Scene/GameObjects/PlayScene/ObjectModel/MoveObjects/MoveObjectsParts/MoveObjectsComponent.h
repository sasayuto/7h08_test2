#pragma once
#include <pch.h>
#include"IMoveObjectsComponent.h"

#include"Scene/GameObjects/PlayScene/Bullet/Bullet.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/Effect/SandstormEffect.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

/// <summary>
/// PlayerComponentのクラスを定義する
/// </summary>
class MoveObjectsComponent :public IMoveObjectsComponent
{
public:
	// 親のゲッターセッター
	IMoveObjectsComponent* GetParent()override { return m_pParent; }
	void SetParent(IMoveObjectsComponent* parent) override { m_pParent = parent; }

	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position)override { m_position = position; }

	//回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Quaternion GetRotate() const override { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate)override { m_rotate = rotate; }

	//位置のセッター、ゲッター
	bool GetSurvival() const override { return m_survival; }
	void SetSurvival(const bool& survival) override { m_survival = survival; }

	//死亡回転のゲッターセッター
	DirectX::SimpleMath::Quaternion GetRandomRotate() const override { return m_randomRotate; }
	void SetRandomRotate(const DirectX::SimpleMath::Quaternion& killRotate)override { m_randomRotate = killRotate; }

	//重力のゲッター、セッター
	float GetGravity() const override { return m_gravity; }
	void SetGravity(const float& gravity) override { m_gravity = gravity; }

	//重力のゲッター、セッター
	float GetTimer() const override { return m_timer; }
	void SetTimer(const float& timer) override { m_timer = timer; }

	//モデルのセッター、ゲッター
	DirectX::Model* GetPartModel()override { return m_pPartModel; }
	void SetPartModel(DirectX::Model* supplyPointModel)override { m_pPartModel = supplyPointModel; }

	//当たり判定のゲッター
	Collider::OBB* GetCollider() override { return m_collider.get(); }

	//子のパーツのゲッター
	std::vector<std::unique_ptr<IMoveObjectsComponent>>& GetParts()override { return m_PlayerParts; }

	//子のパーツを生成
	void AddPart(std::unique_ptr<IMoveObjectsComponent> part) override{ m_PlayerParts.push_back(std::move(part)); }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	MoveObjectsComponent(
		IMoveObjectsComponent* parent,
		const DirectX::SimpleMath::Vector3& MODEL_POS_ADJUSTMENT,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle,
		const float& FALL_SPEED_ACCELERATION,
		const float& EXPLOSIVE_ROTATE,
		const float& EXPLOSIVE_RANDOM_POWER,
		const float& EXPLOSIVE_POWER
	) :
		m_pParent(parent),
		m_position(position),
		m_rotate(angle),
		m_collider(nullptr),
		m_pPartModel(nullptr),
		m_gravity(),
		m_survival(true),
		m_randomRotate(DirectX::SimpleMath::Quaternion::Identity),
		m_timer(0),
		FALL_SPEED_ACCELERATION(FALL_SPEED_ACCELERATION),
		EXPLOSIVE_ROTATE(EXPLOSIVE_ROTATE),
		EXPLOSIVE_RANDOM_POWER(EXPLOSIVE_RANDOM_POWER),
		EXPLOSIVE_POWER(EXPLOSIVE_POWER),
		MODEL_POS_ADJUSTMENT(MODEL_POS_ADJUSTMENT)
	{	
		//当たり判定を生成
		m_collider = std::make_unique<Collider::OBB>();
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~MoveObjectsComponent() override {}

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize()override {
		//360度ランダムな方向を取得
		std::random_device seed;
		std::default_random_engine engine(seed());
		std::uniform_real_distribution<> dist(0, 6.28f);
		float explosionSpeedX = static_cast<float>(dist(engine));

		//ランダムな回転をセット
		SetRandomRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, explosionSpeedX));

		//爆発力をランダムにする
		std::uniform_real_distribution<> power(5, 10);
		float explosionPower = static_cast<float>(power(engine)) / 60;

		//爆発力を重力に付ける
		SetGravity(-explosionPower);

		//当たり判定の初期化
		GetCollider()->Initialize(
			GetPosition(),
			GetRotate(),
			GetPartModel()->meshes[0]->boundingBox.Extents
		);
		// パーツを更新する
		for (auto& playerPart : GetParts())
		{
			playerPart->Initialize();
		}
	}

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	virtual void Update(const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) override 
	{
		//親の位置と合わせる
		m_position =  position + DirectX::SimpleMath::Vector3::Transform(MODEL_POS_ADJUSTMENT, angle);
		//親の回転と合わせる
		SetRotate(angle);
		//当たり判定の更新
		GetCollider()->Update(
			GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
			GetRotate()
		);

		// パーツを更新する
		for (auto& playerPart : GetParts())
		{
			if (playerPart->GetSurvival())	playerPart->Update(elapsedTime, GetPosition(), GetRotate());
			else							playerPart->Explosion(elapsedTime);
		}
	}

	/// <summary>
	/// 爆発処理
	/// </summary>
	virtual void Explosion(const float& elapsedTime) override{
		//アニメーションを超えたら更新しない
	if (GetTimer() >= Bench::ANIMATION_TIME)
		return;

	//時間を計測
	SetTimer(GetTimer() + elapsedTime);

	DirectX::SimpleMath::Vector3 position = GetPosition();

	//ランダムな方向
	position += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, 0, EXPLOSIVE_RANDOM_POWER), GetRandomRotate());

	////破壊される方向に飛ばす(反射ベクトル)
	//position += -GetReflectionVector() * EXPLOSIVE_POWER;

	//重力をつける
	SetGravity(GetGravity() + FALL_SPEED_ACCELERATION);

	//キル座標に重力をつける
	position.y -= GetGravity();

	//爆発のクオータニオン回転
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::Identity;
	q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(EXPLOSIVE_ROTATE));
	q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(EXPLOSIVE_ROTATE));

	SetRotate(q * GetRotate());
	SetPosition(position);

	//当たり判定の更新
	GetCollider()->Update(
		GetPosition(),
		GetRotate()
	);
	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Explosion(elapsedTime);
	}
};

	/// <summary>
	/// 描画する
	/// </summary>
	virtual void Render() override {
		//アニメーションを超えたら描画しない
		if (GetTimer() >= Bench::ANIMATION_TIME)
			return;
		//視界に入っているか
		if (Draw::GetInstance()->VisibilityRange(GetPosition(), m_pPartModel->meshes[0]->boundingSphere.Radius))
			return;
		//スケーリング、位置調整、回転をさせる
		DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
		world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
		world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

		// 飛行機の描画n
		Draw::GetInstance()->ShadowMapRender(GetPartModel(), world);
		//Draw::GetInstance()->TestCubeModel(m_collider->GetExtents(),m_collider->GetPosition(),m_rotate);

		// パーツを更新する
		for (auto& playerPart : GetParts())
		{
			playerPart->Render();
		}
	}

	virtual bool SurvivalCheck() {
		if (!m_survival)
			return false;

		for (auto& parts : m_PlayerParts)
			if (!parts->SurvivalCheck())
				return false;

		return true;

	};

	/// <summary>
	/// シャドウマップ用の画像を作る
	/// </summary>
	virtual void RenderShadowTex() override {
		//アニメーションを超えたら描画しない
		if (GetTimer() >= Bench::ANIMATION_TIME)
			return;

		//スケーリング、位置調整、回転をさせる
		DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
		DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
		DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

		world = rotate * translation;
		// 飛行機の描画
		Draw::GetInstance()->ShadowMapTexCreate(GetPartModel(), world);
			// パーツを更新する
		for (auto& playerPart : GetParts())
		{
			playerPart->RenderShadowTex();
		}
	};

	/// <summary>
	/// 当たり判定の処理をする
	/// </summary>
	/// <param name="respawnManager">リスポーン地点のアドレス</param>
	/// <param name="supplyPointManager">アイテムのアドレス</param>
	/// <param name="enemyManager">敵のマネージャーのアドレス</param>
	/// <param name="coinManager">コインのアドレス</param>
	/// <param name="bulletManager">球のアドレス</param>
	/// <param name="objectsManager">オブジェクトのアドレス</param>
	virtual bool CollisionPlayer(Player* player)override {
		{
			//大まかなプレイヤーと風車パーツの当たり判定
			//あたってなかったらパーツの判定
			if (!GetCollider()->CheckHitSphere(player->GetCollider())) {

				//パーツが当たってたらtrue
				for (auto& windmillPart : GetParts())
					if (windmillPart->CollisionPlayer(player))
						return true;

				//全てのパーツが当たってなかったらfalse
				return false;
			}

			//プレイヤーのパーツと敵のパーツの当たり判定
			for (auto& playerParts : player->GetParts())
			{
				//風車の自分のパーツとプレイヤーのパーツの当たり判定
				if (playerParts->CollisionIMoveObjectsParts(this))
				{
					//性格だが思い
					//for (auto& windmillParts : GetParts())
					//	windmillParts->CollisionPlayerParts(player);
					SetSurvival(false);
					return true;
				}
				//風車のパーツと
				for (auto& windmillParts : GetParts())
					if (windmillParts->CollisionPlayer(player)) return true;
			}
			//全てのパーツが当たってなかったらfalse
			return false;
		}
	}
	
	virtual IMoveObjectsComponent* Collision(Enemy* enemy)override {
		if (GetCollider()->CheckHitSphere(enemy->GetCollider()))return this;
		return nullptr;
	};
	virtual IMoveObjectsComponent* Collision(Airship* airship)override {
		if (GetCollider()->CheckHitSphere(airship->GetCollider()))return this;
		return nullptr;

	};
	virtual bool Collision(Bullet* bullet)override {
		if (GetCollider()->CheckHitSphere(bullet->GetCollider()))
		{
			SetSurvival(false);
			SetGravity(-0.1f);
			return true;
		}
		for (auto& streetLightParts : GetParts())
		{
			if (streetLightParts->Collision(bullet))
				return true;
		}
		return false;
	}
	virtual bool CollisionSandstorm(SandstormEffect* sandstormEffect)
	{
		if (GetCollider()->CheckHitOBBBox(sandstormEffect->GetCollider()))
		{
			SetSurvival(false);
			SetGravity(-0.1f);
			for (auto& streetLightParts : GetParts())
				streetLightParts->CollisionSandstorm(sandstormEffect);

			return true;
		}
		for (auto& streetLightParts : GetParts())
		{
			if (streetLightParts->CollisionSandstorm(sandstormEffect))
				return true;
		}
		return false;
	}

	/// <summary>
	/// 後処理をおこなう
	/// </summary>
	virtual void Finalize()override {}
private:


	//プロペラの位置
	DirectX::SimpleMath::Vector3 m_position;

	//プロペラの方向
	DirectX::SimpleMath::Quaternion m_rotate;

	//生存
	bool m_survival;

	//プロペラの死亡時のランダムな方向に飛ばす回転
	DirectX::SimpleMath::Quaternion m_randomRotate;

	//重力
	float m_gravity;

	//プロペラのモデル
	DirectX::Model* m_pPartModel;

	//当たり判定のポインタ
	std::unique_ptr<Collider::OBB> m_collider;

	//親のポインタ
	IMoveObjectsComponent* m_pParent;

	//パーツの配列のポインタ
	std::vector<std::unique_ptr<IMoveObjectsComponent>> m_PlayerParts;

	//経過時間
	float m_timer;

	const float FALL_SPEED_ACCELERATION;	//落下の加速度			(m/s)
	const float EXPLOSIVE_ROTATE;	//モデルの回転の速さ	(°/s）
	const float EXPLOSIVE_RANDOM_POWER;		//爆発の横のパワー		(m/s)
	const float EXPLOSIVE_POWER;		//爆発の横のパワー		(m/s)
	const DirectX::SimpleMath::Vector3 MODEL_POS_ADJUSTMENT;
};
