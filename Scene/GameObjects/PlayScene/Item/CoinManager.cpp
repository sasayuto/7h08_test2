#include"pch.h"
#include"CoinManager.h"
#include"Scene/GameObjects/PlayScene//Character/Player/Player.h"

using namespace DirectX;

//int型だけは、宣言と同時に数値設定が可能
#define  COIN_CLEAR_COUNT			(100)		//クリアに必要なコインの個数
#define  COIN_COUNT			(50)		//クリアに必要なコインの個数

CoinManager::CoinManager():
	m_coinCount(0),
	m_supplyPointList(),
	m_sceneFlag(false)
{
}

CoinManager::~CoinManager()
{
}

void CoinManager::Intialize(std::string failName)
{
	std::ifstream obj(failName);

	Json::CharReaderBuilder reader;

	Json::Value root;
	//ファイルを開く
	if (obj.is_open())
	{
		std::string errors;
		//
		if (Json::parseFromStream(reader, obj, &root, &errors))
		{
			const Json::Value& wallsArray = root["coin"];
			for (const Json::Value& wallDate : wallsArray)
			{
				//floatからVector3に変換
				std::unique_ptr<Item> windmill = std::make_unique<Coin>();
				windmill->SetPosition(
					SimpleMath::Vector3(wallDate["position"][0].asFloat(),
						wallDate["position"][1].asFloat(),
						wallDate["position"][2].asFloat()
					));
				windmill->SetRotate(DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
					DirectX::XMConvertToRadians(wallDate["rotate"][0].asFloat()),
					DirectX::XMConvertToRadians(wallDate["rotate"][1].asFloat()),
					DirectX::XMConvertToRadians(wallDate["rotate"][2].asFloat())
				));
				m_supplyPointList.push_back(std::move(windmill));
			}
		}
		else
		{
			std::cerr << "a" << errors << std::endl;
		}
		obj.close();
	}
	else
	{
		std::cerr << "Error opening JSON obj:" << std::endl;
	}
	for (int i = 0; i < COIN_COUNT; i++)
	{
		std::unique_ptr<Item> respawnList = std::make_unique<Coin>();
		respawnList->SetpositionRandam(-300, 300);
		m_supplyPointList.push_back(std::move(respawnList));
	}

	//すべてのアイテムを未使用状態にする
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{
		m_supplyPointList[i]->Initialize();
	}
}

void CoinManager::Update(const float& elapsedTime)
{
	//m_supplyPointList.clear();
	//Intialize();
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{
		//敵が生きているか
		if (!m_supplyPointList[i]->GetSurvival())		continue;

		//視界に入っているか
		if (Draw::GetInstance()->VisibilityRange(m_supplyPointList[i]->GetPosition()))
			continue;

		//アイテムの更新
		m_supplyPointList[i]->Update(elapsedTime);
	}

	//クリア判定
	if (m_coinCount == COIN_CLEAR_COUNT)
	{
		m_sceneFlag = true;
	}
}

//ゲームの更新処理を行う関数
void CoinManager::Render()
{
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{
		//敵が生きているか
		if (!m_supplyPointList[i]->GetSurvival())		continue;

		//視界に入っているか
		if (Draw::GetInstance()->VisibilityRange(m_supplyPointList[i]->GetPosition()))
			continue;

		//アイテムの更新
		m_supplyPointList[i]->Render();
	}
}
void CoinManager::RenderShadowTex()
{
	//球の描画
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{
		//敵が生きているか
		if (!m_supplyPointList[i]->GetSurvival())		continue;

		//視界に入っているか
		if (Draw::GetInstance()->DistanceRange(m_supplyPointList[i]->GetPosition()))
			continue;

		//オブジェクトの描画
		m_supplyPointList[i]->RenderShadowTex();
	}
}

void CoinManager::Finalize()
{
	//後処理
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{		
		m_supplyPointList[i].reset();
	}
}

void CoinManager::CheckHitCharacter(Player* player)
{
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{		
		//敵が生きているか
		if (!m_supplyPointList[i]->GetSurvival())	
			continue;

		//プレイヤーの当たり判定
		if (!m_supplyPointList[i]->GetCollider()->CheckHitSphere(player->GetCollider()))
			continue;

		for (auto& playerParts : player->GetParts())
		{
			//パーツとの当たり判定
			if (!playerParts->CollisionItem(m_supplyPointList[i].get()))
				continue;

			m_coinCount++;
			//アイテムを未使用にする
			m_supplyPointList[i]->SetSurvival(false);
			return;
		}
		return;
	}
}
