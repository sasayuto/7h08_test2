#include"pch.h"
#include"SupplyPointManager.h"
#include"Scene/GameObjects/PlayScene//Character/Player/Player.h"

using namespace DirectX;

//int型だけは、宣言と同時に数値設定が可能
#define  SUPPLYPOINT_HP_COUNT					(20)		//HP回復の個数
#define  SUPPLYPOINT_FUEl_COUNT					(20)		//燃料回復の個数

//総数
#define  SUPPLYPOINT_COUNT		(SUPPLYPOINT_HP_COUNT + SUPPLYPOINT_FUEl_COUNT+COIN_COUNT);

SupplyPointManager::SupplyPointManager():
	m_itemGetCount(0)
{

}

SupplyPointManager::~SupplyPointManager()
{

}

void SupplyPointManager::Intialize(std::string failName)
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
			const Json::Value& wallsArray = root["Heat"];
			for (const Json::Value& wallDate : wallsArray)
			{
				//floatからVector3に変換
				std::unique_ptr<Item> windmill = std::make_unique<HpSupplyPoint>();
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
			for (const Json::Value& wallDate : root["Fuel"])
			{
				//floatからVector3に変換
				std::unique_ptr<Item> windmill = std::make_unique<FuelSupplyPoint>();
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


	//すべてのアイテムを未使用状態にする
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{
		m_supplyPointList[i]->Initialize();
	}

}

void SupplyPointManager::Update(const float& elapsedTime)
{
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{
		//敵が生きているか
		if (!m_supplyPointList[i]->GetSurvival())		continue;

		//アイテムの更新
		m_supplyPointList[i]->Update(elapsedTime);
	}

}

//ゲームの更新処理を行う関数
void SupplyPointManager::Render()
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

void SupplyPointManager::RenderShadowTex()
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

void SupplyPointManager::Finalize()
{
	//後処理
	for (int i = 0; i < m_supplyPointList.size(); i++)
	{		
		m_supplyPointList[i].reset();
	}
}

void SupplyPointManager::CheckHitCharacter(Player* player)
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

			//回復処理
			m_supplyPointList[i]->Recovery(player);

			//補充不可にする
			m_supplyPointList[i]->SetSurvival(false);

			m_itemGetCount++;
			//処理軽減のため（当たっていたら終了）
			return;
		}
		return;
	}
}
