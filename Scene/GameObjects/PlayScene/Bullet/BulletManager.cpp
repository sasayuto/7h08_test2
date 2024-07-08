#include"pch.h"
#include"BulletManager.h"

//当たり判定
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/StreetLight/StreetLight.h"
#include"Scene/GameObjects/PlayScene/Character/Turret/Turret.h"
#include"Scene/GameObjects/PlayScene/Character/CrabRobot/CrabRobot.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Bench/Bench.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/HouseMoveObjects/HouseMoveObjects.h"

//球の種類
#include"Bullet_01.h"
#include"Bullet_02.h"
#include"Bullet_Turret.h"

using namespace DirectX;

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
	
}

//ゲームの初期化を行う関数
void BulletManager::Intialize()
{
}

//ゲームの更新を行う関数
void BulletManager::Update()
{
	//球の更新
	for (std::list<std::unique_ptr<Bullet>>::iterator itBullet = m_bulletList.begin(); itBullet != m_bulletList.end(); itBullet++)
	{
		//描画距離設定
		if (Draw::GetInstance()->DespawnDistance(itBullet->get()->GetPosition(), 300.0f))
			itBullet->get()->SetisActive(false);

		//使用されてなかったらリストから排除
		if (!itBullet->get()->GetisActive())
		{
			itBullet = m_bulletList.erase(itBullet);
			if (itBullet == m_bulletList.end()) break;
			continue;

		}
		//球の更新
		itBullet->get()->Update();

		////球と球の当たり判定（重い）
		//CheckHitBullet(m_bulletList[i].get());
	}
}

void BulletManager::Render()
{
	for (std::list<std::unique_ptr<Bullet>>::iterator itBullet = m_bulletList.begin(); itBullet != m_bulletList.end(); itBullet++)
	{
		//視界に入っているか
		if (Draw::GetInstance()->VisibilityRange(itBullet->get()->GetPosition()))
			continue;

		//球の描画
		itBullet->get()->Render();

	}
}

void BulletManager::RenderShadowTex()
{
	for (std::list<std::unique_ptr<Bullet>>::iterator itBullet = m_bulletList.begin(); itBullet != m_bulletList.end(); itBullet++)
	{
		//視界に入っているか
		if (Draw::GetInstance()->VisibilityRange(itBullet->get()->GetPosition()))
			continue;

		//球の描画
		itBullet->get()->RenderShadowTex();

	}

}

void BulletManager::Finalize()
{
	//timerを渡してm_effectの更新処理を行う
	for (std::list<std::unique_ptr<Bullet>>::iterator itBullet = m_bulletList.begin(); itBullet != m_bulletList.end(); itBullet++)
	{
		//球の後始末
		itBullet->get()->Finalize();
	}
}

//球の発射
void BulletManager::Shot(const Bullet::BulletType& bulletType, const Bullet::BulletParent& shooterType, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate)
{
	//球を生成
	std::unique_ptr<Bullet> bullet;

	//タイプによって生成を変える
	switch (bulletType)
	{
	case Bullet::BulletType::Type1:
		bullet = std::make_unique<Bullet_01>();
		bullet->Initialize(shooterType, position, rotate);
		m_bulletList.push_back(std::move(bullet));
		break;

	case Bullet::BulletType::Type2:
		bullet = std::make_unique<Bullet_02>();
		bullet->Initialize(shooterType, position, rotate);
		m_bulletList.push_back(std::move(bullet));
		break;

	case Bullet::BulletType::Turret:
		bullet = std::make_unique<Bullet_Turret>();
		bullet->Initialize(shooterType, position, rotate);
		m_bulletList.push_back(std::move(bullet));
		break;

	}
}


