#pragma once
#include <pch.h>
#include"ICrabRobotComponent.h"

#include"Scene/GameObjects/PlayScene/Bullet/Bullet.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

/// <summary>
/// PlayerComponentのクラスを定義する
/// </summary>
class CrabRobotComponent :public ICrabRobotComponent
{
public:
	// 親のゲッターセッター
	ICrabRobotComponent* GetParent()override { return m_pParent; }

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
	int GetHp() const override { return m_Hp; }
	void SetHp(const int& Hp) override { m_Hp = Hp; }

	//重力のゲッター、セッター
	float GetTimer() const override { return m_timer; }
	void SetTimer(const float& timer) override { m_timer = timer; }

	//モデルのセッター、ゲッター
	DirectX::Model* GetPartModel()override { return m_pPartModel; }
	void SetPartModel(DirectX::Model* supplyPointModel)override { m_pPartModel = supplyPointModel; }

	//当たり判定のゲッター
	Collider::MultipleHitDetermination* GetCollider() override { return m_collider.get(); }

	//子のパーツの配列のゲッター
	std::vector<std::unique_ptr<ICrabRobotComponent>>& GetParts()override { return m_PlayerParts; }

	//子のパーツを生成
	void AddPart(std::unique_ptr<ICrabRobotComponent> part) override { m_PlayerParts.push_back(std::move(part)); }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	CrabRobotComponent(
		ICrabRobotComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) :
		m_pParent(parent),
		m_position(position),
		m_rotate(angle),
		m_collider(nullptr),
		m_pPartModel(nullptr),
		m_gravity(),
		m_randomRotate(),
		m_timer(),
		m_survival(true),
		m_Hp(0)
	{	//当たり判定を生成
		m_collider = std::make_unique<Collider::MultipleHitDetermination>();
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CrabRobotComponent() override {}

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize()override {}

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">１フレーム時間</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	virtual void Update(
		const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) override {
		position; angle; elapsedTime;
	}

	/// <summary>
	/// 爆発処理
	/// </summary>
	/// <param name="elapsedTime">１フレーム時間</param>
	virtual void Explosion(const float& elapsedTime) override { elapsedTime; }


	/// <summary>
	/// 描画する
	/// </summary>
	virtual void Render() override {}

	/// <summary>
	/// 当たり判定の処理をする
	/// </summary>
	/// <param name="respawnManager">リスポーン地点のアドレス</param>
	/// <param name="supplyPointManager">アイテムのアドレス</param>
	/// <param name="enemyManager">敵のマネージャーのアドレス</param>
	/// <param name="coinManager">コインのアドレス</param>
	/// <param name="bulletManager">球のアドレス</param>
	/// <param name="objectsManager">オブジェクトのアドレス</param>

	virtual bool CollisionBullet(Bullet* bullet)override {
		if (GetCollider()->CheckAllHit(bullet->GetCollider()))
		{
			SetHp(GetHp() - bullet->GetOffensivePower());
			return true;
		}
		for (auto& playerPart : GetParts())
		{
			// パーツを更新する
			if (playerPart->CollisionBullet(bullet))return true;
		}
		return false;
	}
	virtual bool CollisionPlayer(Player* player)override {
		
			//大まかなプレイヤーと風車パーツの当たり判定
			if (GetCollider()->CheckAllHit(player->GetCollider())) 
				//プレイヤーのパーツと自分のパーツの当たり判定
				//for (auto& playerParts : player->GetParts())
					//if (playerParts->CollisionTurretPart(this))
					//{
						SetHp(GetHp() - player->GetOffensivePower());
						return true;
					//}
			//パーツが当たってたらtrue
			for (auto& windmillPart : GetParts())
				if (windmillPart->CollisionPlayer(player))	return true;

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

	//生存
	bool m_survival;

	//ＨＰ
	int m_Hp;

	//プロペラの死亡時のランダムな方向に飛ばす回転
	DirectX::SimpleMath::Quaternion m_randomRotate;

	//重力
	float m_gravity;

	//プロペラのモデル
	DirectX::Model* m_pPartModel;

	//当たり判定のポインタ
	std::unique_ptr<Collider::MultipleHitDetermination> m_collider;

	//経過時間
	float m_timer;

	//親のポインタ
	ICrabRobotComponent* m_pParent;

	//パーツの配列のポインタ
	std::vector<std::unique_ptr<ICrabRobotComponent>> m_PlayerParts;
};
