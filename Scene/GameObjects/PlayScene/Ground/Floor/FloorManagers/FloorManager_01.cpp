#include"pch.h"
#include"FloorManager_01.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"../MinStoneFloor/MinStoneFloor.h"
using namespace DirectX;


FloorManager_01::FloorManager_01() 
{	
}

//コンストラクタと呼ばれる関数
FloorManager_01::~FloorManager_01()
{

}

//ゲームの初期化を行う関数
void FloorManager_01::Intialize()
{
	std::ifstream obj("Resources/json/TwonScene/Json_TwonFloor.Json");
	Json::CharReaderBuilder reader;
	Json::Value root;

	// ファイルが開かれているかを確認します。
	if (obj.is_open()) {
		std::string errors;

		// ファイルからJSONをパースします。
		if (Json::parseFromStream(reader, obj, &root, &errors)) 
		{
			// JSONに "house" が存在し、配列であるかどうかを確認します。
			if (root.isMember("floor") && root["floor"].isArray())
			{
				// "house" 配列を取得します。
				const Json::Value& Array = root["floor"][0]["minStoneFloor"];

				// "house" 配列内の各要素に対してループを実行します。
				for (const Json::Value& wallData : Array)
				{
					// 新しいオブジェクトを作成し、位置と回転を設定します。
					std::unique_ptr<Floor> objects = std::make_unique<MinStoneFloor>();
					objects->SetPosition(SimpleMath::Vector3(
						wallData["position"][0].asFloat(),
						wallData["position"][1].asFloat(),
						wallData["position"][2].asFloat()
					));
					objects->SetRotate(DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
						DirectX::XMConvertToRadians(wallData["rotate"][0].asFloat()),
						DirectX::XMConvertToRadians(wallData["rotate"][1].asFloat()),
						DirectX::XMConvertToRadians(wallData["rotate"][2].asFloat())
					));

					// リストにオブジェクトを追加します。
					m_floorsList.push_back(std::move(objects));
				}

			}
			else {
				std::cerr << "JSONに 'house' データが含まれていません。" << std::endl;
			}
		}
		else {
			std::cerr << "JSONのパースエラー: " << errors << std::endl;
		}
		obj.close();
	}
	else {
		std::cerr << "JSONファイルを開く際にエラーが発生しました。" << std::endl;
	}

	// オブジェクトを初期化します。
	for (int i = 0; i < m_floorsList.size(); i++) {
		m_floorsList[i]->Initialize();
	}
}

//ゲームの更新を行う関数
void FloorManager_01::Update()
{
	//球の更新
	for (int i = 0; i < m_floorsList.size(); i++)
	{		
		//オブジェクトの更新
		m_floorsList[i]->Update();
	}
}

//ゲームの更新処理を行う関数
void FloorManager_01::Render()
{
	//球の描画
	for (int i = 0; i < m_floorsList.size(); i++)
	{
		//オブジェクトの描画
		m_floorsList[i]->Render();
	}
}

//ゲームの終了処理を行う関数。解放処理が必要な場合　（Release関数などを呼び出す）は、この関数内でしょるする
void FloorManager_01::Finalize()
{
	//後処理
	for (int i = 0; i < m_floorsList.size(); i++)
	{
		m_floorsList[i].reset();
	}
}

void FloorManager_01::CheckHitCharacter(Player* player)
{
	for (int i = 0; i < m_floorsList.size(); i++)
	{
		//プレイヤーとの当たり判定
		if (!m_floorsList[i]->GetCollider()->CheckHitSphere(player->GetCollider()))
			continue;

		for (auto& playerParts : player->GetParts())
		{
			//パーツとの当たり判定
			if (!playerParts->CollisionFloor(m_floorsList[i].get()))
				continue;

			player->Damage(player->GetHP());
			//処理軽減のため（当たっていたら終了）
		}
	}
}

void FloorManager_01::CheckHitEnemy(Enemy* enemy)
{
	for (int i = 0; i < m_floorsList.size(); i++)
	{
		//プレイヤーとの当たり判定
		if (!m_floorsList[i]->GetCollider()->CheckHitSphere(enemy->GetCollider()))
			continue;

		for (auto& playerParts : enemy->GetParts())
		{
			//パーツとの当たり判定
			if (!playerParts->CollisionFloor(m_floorsList[i].get()))
				continue;

			enemy->Damage(enemy->GetHP());
			//処理軽減のため（当たっていたら終了）
		}
	}

}

