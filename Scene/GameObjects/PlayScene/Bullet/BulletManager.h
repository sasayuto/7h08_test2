#pragma once
#include"Bullet.h"
#include<list>
class Player;
class Enemy;
class StreetLight;
class MoveObjects;
class Airship;
class Turret;
class CrabRobot;
class HouseMoveObjects;
/// <summary>
/// 球の管理者クラスを定義する
/// </summary>
class BulletManager
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BulletManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BulletManager();

	/// <summary>
	/// 初期化する
	/// </summary>
	void Intialize();

	/// <summary>
	/// 処理を実行する
	/// </summary>
	void Update();

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

	/// <summary>
	/// 描画する
	/// </summary>
	void RenderShadowTex();

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();

	/// <summary>
	/// 球の発射
	/// </summary>
	/// <param name="bulletType">球の使用者</param>
	/// <param name="shooterType">球の種類</param>
	/// <param name="position">使用時の位置</param>
	/// <param name="rotate">使用時の角度</param>
	void Shot(
		const Bullet::BulletType& bulletType, 
		const Bullet::BulletParent& shooterType,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate
	);
	/// <summary>
	/// プレイヤーと球の当たり判定
	/// </summary>
	/// <param name="character">キャラクターのアドレス</param>
	template<typename Object>
	void CheckHitDamegeObjects(Object* object, Bullet::BulletParent MyParent);

	/// <summary>
	/// 飛行船と球の当たり判定
	/// </summary>
	/// <param name="character">敵のアドレス</param>
	template<typename Object>
	void CheckHitDestructionObjects(Object* object);

private:
	//球の配列のポインタ
	std::list<std::unique_ptr<Bullet>> m_bulletList;
};

template<typename Object>
inline void BulletManager::CheckHitDamegeObjects(Object* object, Bullet::BulletParent MyParent)
{
	for (std::list<std::unique_ptr<Bullet>>::iterator itBullet = m_bulletList.begin(); itBullet != m_bulletList.end(); itBullet++)
	{
		for (size_t i = 1; i <= 10; i++)
		{
			bool HitFlag = false;
			itBullet->get()->GetCollider()->SetPosition(itBullet->get()->GetPosition() - itBullet->get()->GetMove() * (static_cast<float>(i) * 0.1f));

			//自分の球ですか
			if (itBullet->get()->GetParentType() == MyParent)
				continue;

			//当たり判定
			//プレイヤーの大まかな当たり判定
			if (!itBullet->get()->GetCollider()->CheckHitSphere(object->GetCollider()))
				continue;

			//プレイヤーのパーツとの当たり判定
			for (auto& playerParts : object->GetParts())
			{
				if (!playerParts->CollisionBullet(itBullet->get()))
					continue;
				else  HitFlag = true;
				//球を未使用にする
				itBullet->get()->SetisActive(false);

				//当たっていたらダメージ処理
				object->Damage(itBullet->get()->GetOffensivePower());
				break;
			}
			if (HitFlag)
				break;
		}
	}

}

template<typename Object>
inline void BulletManager::CheckHitDestructionObjects(Object* object)
{
	int CheckNum = 4;
	for (std::list<std::unique_ptr<Bullet>>::iterator itBullet = m_bulletList.begin(); itBullet != m_bulletList.end(); itBullet++)
	{
		for (size_t i = 1; i <= CheckNum; i++)
		{
			bool HitFlag = false;
			itBullet->get()->GetCollider()->SetPosition(itBullet->get()->GetPosition() - itBullet->get()->GetMove() * (static_cast<float>(i) / static_cast<float>(CheckNum)));

			//今のところプレイヤーとの判定だけ取る
			if (itBullet->get()->GetParentType() != Bullet::BulletParent::PlayerBullet)
				continue;

			//ベンチの大まかな当たり判定
			if (!object->GetRoughCollider()->CheckHitSphere(itBullet->get()->GetCollider()))
				continue;

			//ベンチパーツとの当たり判定
			for (auto& streetLightParts : object->GetParts())
			{
				if (!streetLightParts->Collision(itBullet->get()))
					continue;
				else  HitFlag = true;

				//パーツがばらけるので大まかな判定を大きくする
				object->GetRoughCollider()->SetRadius(
					object->GetRoughCollider()->GetRadius() * 5.0f
				);

				//球を未使用にする
				itBullet->get()->SetisActive(false);
			}
			if (HitFlag)
				break;

		}
	}

}
