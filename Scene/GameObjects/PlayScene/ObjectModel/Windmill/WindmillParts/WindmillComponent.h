#pragma once
#include <pch.h>
#include"IWindmillComponent.h"

#include"Scene/GameObjects/PlayScene/Bullet/Bullet.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

/// <summary>
/// PlayerComponentのクラスを定義する
/// </summary>
class WindmillComponent :public IWindmillComponent
{
public:
	// 親のゲッターセッター
	IWindmillComponent* GetParent()override { return m_pParent; }
	void SetParent(IWindmillComponent* parent) override { m_pParent = parent; }

	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position)override { m_position = position; }

	//回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Quaternion GetRotate() const override { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate)override { m_rotate = rotate; }

	//モデルのセッター、ゲッター
	DirectX::Model* GetPartModel()override { return m_pPartModel; }
	void SetPartModel(DirectX::Model* supplyPointModel)override { m_pPartModel = supplyPointModel; }

	//当たり判定のゲッター
	Collider::OBB* GetCollider() override { return m_collider.get(); }

	//子のパーツのゲッター
	std::vector<std::unique_ptr<IWindmillComponent>>& GetParts()override { return m_PlayerParts; }

	//子のパーツを生成
	void AddPart(std::unique_ptr<IWindmillComponent> part) override { m_PlayerParts.push_back(std::move(part)); }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	WindmillComponent(
		IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) :
		m_pParent(parent),
		m_position(position),
		m_rotate(angle),
		m_collider(nullptr),
		m_pPartModel(nullptr)
	{	//当たり判定を生成
		m_collider = std::make_unique<Collider::OBB>();
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~WindmillComponent() override {}

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
	virtual IWindmillComponent* Collision(Player* player)override {
		if (GetCollider()->CheckHitSphere(player->GetCollider()))return this;
		for (auto& windmillPart : GetParts())
		{
			// パーツを更新する
			IWindmillComponent* HitPrats = windmillPart->Collision(player);
			if (HitPrats)
				return HitPrats;
		}
		return nullptr;
	}

	virtual IWindmillComponent* Collision(Airship* airship)override {
		if (GetCollider()->CheckHitSphere(airship->GetCollider()))return this;
		for (auto& windmillPart : GetParts())
		{
			// パーツを更新する
			IWindmillComponent* HitPrats = windmillPart->Collision(airship);
			if (HitPrats)
				return HitPrats;
		}
		return nullptr;

	};
	virtual bool Collision(Bullet* bullet)override {
		if (GetCollider()->CheckHitSphere(bullet->GetCollider()))return true;
		for (auto& playerPart : GetParts())
		{
			// パーツを更新する
			if (playerPart->Collision(bullet))return true;
		}
		return false;
	}
	virtual bool CollisionPlayer(Player* player)override
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
			if (playerParts->CollisionWindmillParts(this))
				//性格だが思い
				//for (auto& windmillParts : GetParts())
				//	windmillParts->CollisionPlayerParts(player);
				return true;

			//風車のパーツと
			for (auto& windmillParts : GetParts())
				if (windmillParts->CollisionPlayer(player)) return true;
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
		for (auto& playerParts : enemy->GetParts())
		{
			//風車の自分のパーツとプレイヤーのパーツの当たり判定
			if (playerParts->CollisionWindmillParts(this))
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
	IWindmillComponent* m_pParent;

	//パーツの配列のポインタ
	std::vector<std::unique_ptr<IWindmillComponent>> m_PlayerParts;
};
