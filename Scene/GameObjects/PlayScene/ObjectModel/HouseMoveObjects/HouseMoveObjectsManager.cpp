#include"pch.h"
#include"HouseMoveObjectsManager.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/Effect/SandstormEffect.h"

using namespace DirectX;
const int WINDMILL_COUNT(100);

HouseMoveObjectsManager::HouseMoveObjectsManager():
	m_benchKillCount(0),
	m_HouseMoveObjectsManager{},
	m_pBulletManager(nullptr)
{
}

//コンストラクタと呼ばれる関数
HouseMoveObjectsManager::~HouseMoveObjectsManager()
{
}
//ゲームの更新を行う関数
void HouseMoveObjectsManager::Update(const float& elapsedTime)
{
	//m_HouseMoveObjectsManager.clear();
	//Intialize(m_pBulletManager);
	//球の更新
	for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
	{		
		//死んでいたら更新しない
		if (!m_HouseMoveObjectsManager[i]->GetSurvival())
			continue;

		//オブジェクトの更新
		m_HouseMoveObjectsManager[i]->Update(elapsedTime);
	}
}

//ゲームの更新処理を行う関数
void HouseMoveObjectsManager::Render()
{

	//球の描画
	for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
	{
		//死んでいたら更新しない
		if (!m_HouseMoveObjectsManager[i]->GetSurvival())
			continue;

		//オブジェクトの描画
		m_HouseMoveObjectsManager[i]->Render();
	}
}
//ゲームの更新処理を行う関数
void HouseMoveObjectsManager::RenderShadowTex(const bool dynamicflag)
{

	//球の描画
	for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
	{		
		//死んでいたら更新しない
		if (m_HouseMoveObjectsManager[i]->GetAllSurvivalFlag() == dynamicflag)
			continue;

		//死んでいたら更新しない
		if (!m_HouseMoveObjectsManager[i]->GetSurvival())
			continue;

		//視界に入っているか
		if (Draw::GetInstance()->DistanceRange(m_HouseMoveObjectsManager[i]->GetPosition()))
			continue;

		//オブジェクトの描画
		m_HouseMoveObjectsManager[i]->RenderShadowTex();
	}
}

//ゲームの終了処理を行う関数。解放処理が必要な場合　（Release関数などを呼び出す）は、この関数内でしょるする
void HouseMoveObjectsManager::Finalize()
{
	//後処理
	for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
	{
		m_HouseMoveObjectsManager[i].reset();
	}
}

void HouseMoveObjectsManager::CheckHitCharacter(Player* player)
{
	////プレイヤーとの当たり判定
	for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
	{
		//死んでいたら更新しない
		if (!m_HouseMoveObjectsManager[i]->GetSurvival())
			continue;

		//大まかなプレイヤーと大まかな敵の当たり判定
		if (!m_HouseMoveObjectsManager[i]->GetRoughCollider()->CheckHitSphere(player->GetCollider()))
			continue;

		//プレイヤーのパーツと敵のパーツの当たり判定
		for (auto& airshipParts : m_HouseMoveObjectsManager[i]->GetParts())
		{
			//直したほうがいい（）パーツと大枠のプレイヤーで当たり判定を行い
			//当たったら当たったパーツを返す当たってなかったら"null"
			if (!airshipParts->CollisionPlayer(player))
				continue;

			player->Damage(player->GetHP());

			m_HouseMoveObjectsManager[i]->GetRoughCollider()->SetRadius(
				m_HouseMoveObjectsManager[i]->GetRoughCollider()->GetRadius() * 5.0f
			);

		}
	}
}

void HouseMoveObjectsManager::CheckHitEnemy(Enemy* enemy)
{
	////プレイヤーとの当たり判定
	for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
	{
		//死んでいたら更新しない
		if (!m_HouseMoveObjectsManager[i]->GetSurvival())
			continue;

		//大まかなプレイヤーと大まかな敵の当たり判定
		if (!m_HouseMoveObjectsManager[i]->GetRoughCollider()->CheckHitSphere(enemy->GetCollider()))
			continue;

		//プレイヤーのパーツと敵のパーツの当たり判定
		for (auto& airshipParts : m_HouseMoveObjectsManager[i]->GetParts())
		{
			//直したほうがいい（）パーツと大枠のプレイヤーで当たり判定を行い
			//当たったら当たったパーツを返す当たってなかったら"null"
			if (!airshipParts->Collision(enemy))
				continue;

			enemy->Damage(enemy->GetHP());

			m_HouseMoveObjectsManager[i]->GetRoughCollider()->SetRadius(
				m_HouseMoveObjectsManager[i]->GetRoughCollider()->GetRadius() * 5.0f
			);

		}
	}
}
void HouseMoveObjectsManager::CheckHitAirship(Airship* airship)
{
	airship;
	////プレイヤーとの当たり判定
	//for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
	//{
	// 
	//	//大まかなプレイヤーと大まかな敵の当たり判定
	//	if (!m_HouseMoveObjectsManager[i]->GetRoughCollider()->CheckHitSphere(airship->GetCollider()))
	//		continue;

	//	//プレイヤーのパーツと敵のパーツの当たり判定
	//	for (auto& airshipParts : m_HouseMoveObjectsManager[i]->GetParts())
	//	{
	//		//直したほうがいい（）パーツと大枠のプレイヤーで当たり判定を行い
	//		//当たったら当たったパーツを返す当たってなかったら"null"
	//		IWindmillComponent* HitAirshipPart = airshipParts->Collision(airship);
	//		if (!HitAirshipPart)
	//			continue;

	//		//for (auto& playerParts : player->GetPlayerParts())
	//		//{
	//		//	//プレイヤーのパーツと大まかな敵の当たり判定
	//		//	if (!playerParts->Collision(HitAirshipPart))
	//		//		continue;

	//		airship->Damage(Player::PLAYER_MAX_HP);
	//		return;
	//		//}
	//	}
	//}
}

void HouseMoveObjectsManager::CheckHitSandstorm(SandstormEffect* sandstormEffect)
{
	////プレイヤーとの当たり判定
	for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
	{
		//死んでいたら更新しない
		if (!m_HouseMoveObjectsManager[i]->GetSurvival())
			continue;

		//大まかなプレイヤーと大まかな敵の当たり判定
		if (!m_HouseMoveObjectsManager[i]->GetRoughCollider()->CheckHitSphereBox(sandstormEffect->GetCollider()))
			continue;

		//プレイヤーのパーツと敵のパーツの当たり判定
		for (auto& airshipParts : m_HouseMoveObjectsManager[i]->GetParts())
		{
			//直したほうがいい（）パーツと大枠のプレイヤーで当たり判定を行い
			//当たったら当たったパーツを返す当たってなかったら"null"
			if (!airshipParts->CollisionSandstorm(sandstormEffect))
			continue;

			//パーツごとでばらけるので親の当たり判定を大きくする
			m_HouseMoveObjectsManager[i]->GetRoughCollider()->SetRadius(
				m_HouseMoveObjectsManager[i]->GetRoughCollider()->GetRadius() * 5.0f
			);
		}
	}

}
