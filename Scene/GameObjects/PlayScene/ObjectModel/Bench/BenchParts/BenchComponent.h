#pragma once
#include <pch.h>
#include"IBenchComponent.h"

#include"Scene/GameObjects/PlayScene/Bullet/Bullet.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/Effect/SandstormEffect.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

/// <summary>
/// PlayerComponentのクラスを定義する
/// </summary>
class BenchComponent :public IBenchComponent
{
public:
	// 親のゲッターセッター
	IBenchComponent* GetParent()override { return m_pParent; }
	void SetParent(IBenchComponent* parent) override { m_pParent = parent; }

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
	std::vector<std::unique_ptr<IBenchComponent>>& GetParts()override { return m_PlayerParts; }

	//子のパーツを生成
	void AddPart(std::unique_ptr<IBenchComponent> part) override{ m_PlayerParts.push_back(std::move(part)); }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	BenchComponent(
		IBenchComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) :
		m_pParent(parent),
		m_position(position),
		m_rotate(angle),
		m_collider(nullptr),
		m_pPartModel(nullptr),
		m_gravity(),
		m_survival(true),
		m_randomRotate(DirectX::SimpleMath::Quaternion::Identity),
		m_timer(0)
	{	//当たり判定を生成
		m_collider = std::make_unique<Collider::OBB>();
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BenchComponent() override {}

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize()override {}

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	virtual void Update(const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) override {
		position; angle;
	}

	/// <summary>
	/// 爆発処理
	/// </summary>
	virtual void Explosion(const float& elapsedTime) override{};

	/// <summary>
	/// 描画する
	/// </summary>
	virtual void Render() override {}

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
		//スケーリング、位置調整、回転をさせる
		DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
		DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
		DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

		world = rotate * translation;
		// 飛行機の描画
		Draw::GetInstance()->ShadowMapTexCreate(GetPartModel(), world);

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
			for (auto& playerParts : player->GetPlayerParts())
			{
				//風車の自分のパーツとプレイヤーのパーツの当たり判定
				if (playerParts->CollisionBenchParts(this))
					//性格だが思い
					//for (auto& windmillParts : GetParts())
					//	windmillParts->CollisionPlayerParts(player);
					SetSurvival(false);
					return true;

				//風車のパーツと
				for (auto& windmillParts : GetParts())
					if (windmillParts->CollisionPlayer(player)) return true;
			}
			//全てのパーツが当たってなかったらfalse
			return false;
		}
	}
	
	virtual IBenchComponent* Collision(Enemy* enemy)override {
		if (GetCollider()->CheckHitSphere(enemy->GetCollider()))return this;
		return nullptr;
	};
	virtual IBenchComponent* Collision(Airship* airship)override {
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
	IBenchComponent* m_pParent;

	//パーツの配列のポインタ
	std::vector<std::unique_ptr<IBenchComponent>> m_PlayerParts;

	//経過時間
	float m_timer;

};
