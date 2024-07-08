#pragma once
#include <pch.h>
#include"IAirshipComponent.h"

/// <summary>
/// PlayerComponentのクラスを定義する
/// </summary>
class AirshipComponent :public IAirshipComponent
{
public:
	// 親のゲッターセッター
	IAirshipComponent* GetParent()override { return m_pParent; }
	void SetParent(IAirshipComponent* parent) override { m_pParent = parent; }

	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position)override { m_position = position; }

	//回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Quaternion GetRotate() const override { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate)override { m_rotate = rotate; }

	//死亡回転のゲッターセッター
	DirectX::SimpleMath::Quaternion GetKillRotate() const override { return m_killrotate; }
	void SetKillRotate(const DirectX::SimpleMath::Quaternion& killRotate)override { m_killrotate = killRotate; }

	//死亡回転のゲッターセッター
	DirectX::SimpleMath::Quaternion GetRandomRotate() const override { return m_randomRotate; }
	void SetRandomRotate(const DirectX::SimpleMath::Quaternion& killRotate)override { m_randomRotate = killRotate; }

	//重力のゲッター、セッター
	float GetGravity() const override{ return m_gravity; }
	void SetGravity(const float& gravity) override{ m_gravity = gravity; }

	//モデルのセッター、ゲッター
	DirectX::Model* GetPartModel()override { return m_pPartModel; }
	void SetPartModel(DirectX::Model* supplyPointModel)override { m_pPartModel = supplyPointModel; }

	//当たり判定のゲッター
	Collider::OBB* GetCollider() override { return m_collider.get(); }

	//子のパーツのゲッター
	std::vector<std::unique_ptr<IAirshipComponent>>& GetParts()override { return m_PlayerParts; }

	//子のパーツを生成
	void AddPart(std::unique_ptr<IAirshipComponent> part) override{ m_PlayerParts.push_back(std::move(part)); }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	AirshipComponent(
		IAirshipComponent* parent,
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
		m_randomRotate(DirectX::SimpleMath::Quaternion::Identity)
	{	//当たり判定を生成
		m_collider = std::make_unique<Collider::OBB>();
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~AirshipComponent() override {}

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize()override {}

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
		for (auto& Part : GetParts())
		{
			Part->RenderShadowTex();
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
	/// 当たり判定の処理をする
	/// </summary>
	/// <param name="respawnManager">リスポーン地点のアドレス</param>
	/// <param name="supplyPointManager">アイテムのアドレス</param>
	/// <param name="enemyManager">敵のマネージャーのアドレス</param>
	/// <param name="coinManager">コインのアドレス</param>
	/// <param name="bulletManager">球のアドレス</param>
	/// <param name="objectsManager">オブジェクトのアドレス</param>
	virtual bool Collision(Objects* objects) override {
		if (objects->GetCollider()->CheckHitOneOrMore(GetCollider()))return true;
		for (auto& playerPart : GetParts())
		{
			// パーツを更新する
			if (playerPart->Collision(objects))return true;
		}
		return false;
	}

	virtual bool CollisionBullet(Bullet* bullet)override {
		if (GetCollider()->CheckHitSphere(bullet->GetCollider()))
			return true;
		for (auto& playerPart : GetParts())
		{
			// パーツを更新する
			if (playerPart->CollisionBullet(bullet))
				return true;
		}
		return false;
	}

	virtual bool CollisionPlayer(Player* player)override {
		//大まかなプレイヤーと風車パーツの当たり判定
		//あたってなかったらパーツの判定
		if (!GetCollider()->CheckHitSphere(player->GetCollider())) {

			//パーツが当たってたらtrue
			for (auto& airshipPart : GetParts())
				if (airshipPart->CollisionPlayer(player))
					return true;
			//全てのパーツが当たってなかったらfalse
			return false;
		}
		//プレイヤーのパーツと敵のパーツの当たり判定
		for (auto& playerParts : player->GetParts())
		{
			//風車の自分のパーツとプレイヤーのパーツの当たり判定
			if (playerParts->CollisionAirshipParts(this))
				//性格だが思い
				//for (auto& windmillParts : GetParts())
				//	windmillParts->CollisionPlayerParts(player);
				return true;

			//風車のパーツと
			for (auto& airshipPart : GetParts())
				if (airshipPart->CollisionPlayer(player)) return true;
		}
		//全てのパーツが当たってなかったらfalse
		return false;
	}

	virtual bool CollisionEnemy(Enemy* enemy)override
	{
		//大まかなプレイヤーと風車パーツの当たり判定
		//あたってなかったらパーツの判定
		if (!GetCollider()->CheckHitSphere(enemy->GetCollider())) {

			//パーツが当たってたらtrue
			for (auto& windmillPart : GetParts())
				if (windmillPart->CollisionEnemy(enemy))
					return true;
			//全てのパーツが当たってなかったらfalse
			return false;
		}
		//プレイヤーのパーツと敵のパーツの当たり判定
		for (auto& enemyParts : enemy->GetParts())
		{
			//風車の自分のパーツとプレイヤーのパーツの当たり判定
			if (enemyParts->CollisionAirshipParts(this))
				//性格だが思い
				//for (auto& windmillParts : GetParts())
				//	windmillParts->CollisionPlayerParts(player);
				return true;

			//風車のパーツと
			for (auto& windmillParts : GetParts())
				if (windmillParts->CollisionEnemy(enemy)) return true;
		}
		//全てのパーツが当たってなかったらfalse
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

	//プロペラのモデル
	DirectX::Model* m_pPartModel;

	//当たり判定のポインタ
	std::unique_ptr<Collider::OBB> m_collider;

	//親のポインタ
	IAirshipComponent* m_pParent;

	//プロペラの死亡時の回転
	DirectX::SimpleMath::Quaternion m_killrotate;

	//プロペラの死亡時のランダムな方向に飛ばす回転
	DirectX::SimpleMath::Quaternion m_randomRotate;

	//パーツの配列のポインタ
	std::vector<std::unique_ptr<IAirshipComponent>> m_PlayerParts;

	//重力
	float m_gravity;

};
