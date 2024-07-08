#include"pch.h"
#include"RespawnManager.h"
#include"Scene/GameObjects/PlayScene//Character/Player/Player.h"

using namespace DirectX;

#define RESPAWN_COUNT			(50)		//リスポーンの個数

RespawnManager::RespawnManager() :
	m_RespawnList(),
	m_respawnPosition(SimpleMath::Vector3(000.0f,250.0f,0.0f))
{
	//すべてのリスポーンのインスタンスを生成する
	for (int i = 0; i < RESPAWN_COUNT; i++)
	{
		std::unique_ptr<Item> respawnList = std::make_unique<Respawn>();
		m_RespawnList.push_back(std::move(respawnList));
	}
}
//コンストラクタと呼ばれる関数
RespawnManager::~RespawnManager()
{

}

//ゲームの初期化を行う関数
void RespawnManager::Intialize()
{

	for (int i = 0; i < RESPAWN_COUNT; i++)
	{
		//範囲内のランダムな位置にセット
		m_RespawnList[i]->SetpositionRandam(-250,250);

		//初期化する
		m_RespawnList[i]->Initialize();

	}

}

//ゲームの更新を行う関数
void RespawnManager::Update(const float& elapsedTime)
{
	//球の更新
	for (int i = 0; i < RESPAWN_COUNT; i++)
	{		
		//リスポーンの更新
		m_RespawnList[i]->Update(elapsedTime);
	}
}

//ゲームの更新処理を行う関数
void RespawnManager::Render()
{
	//球の描画
	for (int i = 0; i < RESPAWN_COUNT; i++)
	{
		//視界に入っているか
		if (Draw::GetInstance()->VisibilityRange(m_RespawnList[i]->GetPosition()))
			continue;

		m_RespawnList[i]->Render();
	}
}

//ゲームの終了処理を行う関数。解放処理が必要な場合　（Release関数などを呼び出す）は、この関数内でしょるする
void RespawnManager::Finalize()
{
	//後処理
	for (int i = 0; i < RESPAWN_COUNT; i++)
	{
		m_RespawnList[i].reset();
	}
}

void RespawnManager::CheckHitCharacter(Player* player)
{
	for (int i = 0; i < RESPAWN_COUNT; i++)
	{
		//プレイヤーとの当たり判定
		if (!m_RespawnList[i]->GetCollider()->CheckHitSphere(player->GetCollider()))
		{
			continue;
		}

		for (auto& playerParts : player->GetParts())
		{
			//パーツとの当たり判定
			if (!playerParts->CollisionItem(m_RespawnList[i].get()))
				continue;

			//リスポーン地点を保持する
			m_respawnPosition = m_RespawnList[i]->GetPosition();

			//使用済みか
			if (!m_RespawnList[i]->GetSurvival())	continue;

			////回復処理
			m_RespawnList[i]->Recovery(player);

			//補充不可にする
			m_RespawnList[i]->SetSurvival(false);
			
			//処理軽減のため（当たっていたら終了）
			return;
		}
		return;
	}
}
