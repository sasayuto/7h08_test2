#include"pch.h"
#include"MoveObjectsManager.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/Effect/SandstormEffect.h"

using namespace DirectX;
const int WINDMILL_COUNT(100);

MoveObjectsManager::MoveObjectsManager():
	m_benchKillCount(0),
	m_MoveObjectsManager{},
	m_pBulletManager(nullptr)
{
}

//コンストラクタと呼ばれる関数
MoveObjectsManager::~MoveObjectsManager()
{

}

//ゲームの初期化を行う関数
void MoveObjectsManager::Intialize(BulletManager* bulletManager)
{
	m_pBulletManager = bulletManager;

	for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	{
		//初期化する
		m_MoveObjectsManager[i]->Initialize(bulletManager,this);
	}

}

//ゲームの更新を行う関数
void MoveObjectsManager::Update(const float& elapsedTime)
{
	//m_MoveObjectsManager.clear();
	//Intialize(m_pBulletManager);
	//球の更新
	for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	{		
		//死んでいたら更新しない
		if (!m_MoveObjectsManager[i]->GetSurvival())
			continue;

		//オブジェクトの更新
		m_MoveObjectsManager[i]->Update(elapsedTime);
	}
}

//ゲームの更新処理を行う関数
void MoveObjectsManager::Render()
{

	//球の描画
	for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	{
		//死んでいたら更新しない
		if (!m_MoveObjectsManager[i]->GetSurvival())
			continue;

		//オブジェクトの描画
		m_MoveObjectsManager[i]->Render();
	}
}
//ゲームの更新処理を行う関数
void MoveObjectsManager::RenderShadowTex(const bool dynamicflag)
{

	//球の描画
	for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	{		
		//死んでいたら更新しない
		if (m_MoveObjectsManager[i]->GetAllSurvivalFlag() == dynamicflag)
			continue;

		//死んでいたら更新しない
		if (!m_MoveObjectsManager[i]->GetSurvival())
			continue;

		//視界に入っているか
		if (Draw::GetInstance()->DistanceRange(m_MoveObjectsManager[i]->GetPosition()))
			continue;

		//オブジェクトの描画
		m_MoveObjectsManager[i]->RenderShadowTex();
	}
}

//ゲームの終了処理を行う関数。解放処理が必要な場合　（Release関数などを呼び出す）は、この関数内でしょるする
void MoveObjectsManager::Finalize()
{
	//後処理
	for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	{
		m_MoveObjectsManager[i].reset();
	}
}

void MoveObjectsManager::CheckHitCharacter(Player* player)
{
	////プレイヤーとの当たり判定
	for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	{
		//死んでいたら更新しない
		if (!m_MoveObjectsManager[i]->GetSurvival())
			continue;

		//大まかなプレイヤーと大まかな敵の当たり判定
		if (!m_MoveObjectsManager[i]->GetRoughCollider()->CheckHitSphere(player->GetCollider()))
			continue;

		//プレイヤーのパーツと敵のパーツの当たり判定
		for (auto& airshipParts : m_MoveObjectsManager[i]->GetParts())
		{
			//直したほうがいい（）パーツと大枠のプレイヤーで当たり判定を行い
			//当たったら当たったパーツを返す当たってなかったら"null"
			if (!airshipParts->CollisionPlayer(player))
				continue;

			m_MoveObjectsManager[i]->GetRoughCollider()->SetRadius(
				m_MoveObjectsManager[i]->GetRoughCollider()->GetRadius() * 5.0f
			);

		}
	}
}

void MoveObjectsManager::CheckHitEnemy(Enemy* enemy)
{
	////プレイヤーとの当たり判定
	for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	{
		//死んでいたら更新しない
		if (!m_MoveObjectsManager[i]->GetSurvival())
			continue;

		//大まかなプレイヤーと大まかな敵の当たり判定
		if (!m_MoveObjectsManager[i]->GetRoughCollider()->CheckHitSphere(enemy->GetCollider()))
			continue;

		//プレイヤーのパーツと敵のパーツの当たり判定
		for (auto& airshipParts : m_MoveObjectsManager[i]->GetParts())
		{
			//直したほうがいい（）パーツと大枠のプレイヤーで当たり判定を行い
			//当たったら当たったパーツを返す当たってなかったら"null"
			//if (!airshipParts->CollisionPlayer(enemy))
				continue;

				m_MoveObjectsManager[i]->GetRoughCollider()->SetRadius(
					m_MoveObjectsManager[i]->GetRoughCollider()->GetRadius() * 5.0f
				);

		}
	}
}
void MoveObjectsManager::CheckHitAirship(Airship* airship)
{
	////プレイヤーとの当たり判定
	//for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	//{
	// 
	//	//大まかなプレイヤーと大まかな敵の当たり判定
	//	if (!m_MoveObjectsManager[i]->GetRoughCollider()->CheckHitSphere(airship->GetCollider()))
	//		continue;

	//	//プレイヤーのパーツと敵のパーツの当たり判定
	//	for (auto& airshipParts : m_MoveObjectsManager[i]->GetParts())
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

void MoveObjectsManager::CheckHitSandstorm(SandstormEffect* sandstormEffect)
{
	////プレイヤーとの当たり判定
	for (int i = 0; i < m_MoveObjectsManager.size(); i++)
	{
		//死んでいたら更新しない
		if (!m_MoveObjectsManager[i]->GetSurvival())
			continue;

		//大まかなプレイヤーと大まかな敵の当たり判定
		if (!m_MoveObjectsManager[i]->GetRoughCollider()->CheckHitSphereBox(sandstormEffect->GetCollider()))
			continue;

		//プレイヤーのパーツと敵のパーツの当たり判定
		for (auto& airshipParts : m_MoveObjectsManager[i]->GetParts())
		{
			//直したほうがいい（）パーツと大枠のプレイヤーで当たり判定を行い
			//当たったら当たったパーツを返す当たってなかったら"null"
			if (!airshipParts->CollisionSandstorm(sandstormEffect))
			continue;

			//パーツごとでばらけるので親の当たり判定を大きくする
			m_MoveObjectsManager[i]->GetRoughCollider()->SetRadius(
				m_MoveObjectsManager[i]->GetRoughCollider()->GetRadius() * 5.0f
			);
		}
	}

}
