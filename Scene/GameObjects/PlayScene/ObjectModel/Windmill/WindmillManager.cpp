#include"pch.h"
#include"WindmillManager.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"

using namespace DirectX;
const int WINDMILL_COUNT(0);

WindmillManager::WindmillManager(): 
	m_mapLoader(nullptr)
{
}

//コンストラクタと呼ばれる関数
WindmillManager::~WindmillManager()
{

}

//ゲームの初期化を行う関数
void WindmillManager::Intialize()
{
	std::ifstream obj("Resources/json/TwonScene/Json_TwonWindmill.Json");
	Json::CharReaderBuilder reader;
	Json::Value root;

	// ファイルが開かれているかを確認します。
	if (obj.is_open()) {
		std::string errors;

		// ファイルからJSONをパースします。
		if (Json::parseFromStream(reader, obj, &root, &errors))
		{
			// "house" 配列を取得します。
			const Json::Value& Array = root["windmill"];

			// "house" 配列内の各要素に対してループを実行します。
			for (const Json::Value& wallData : Array)
			{
				// 新しいオブジェクトを作成し、位置と回転を設定します。
				std::unique_ptr<Windmill> objects = std::make_unique<Windmill>();
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
				m_objectsList.push_back(std::move(objects));
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

	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//初期化する
		m_objectsList[i]->Initialize();
	}

}

//ゲームの更新を行う関数
void WindmillManager::Update()
{
	//球の更新
	for (int i = 0; i < m_objectsList.size(); i++)
	{		
		//オブジェクトの更新
		m_objectsList[i]->Update();
	}
}

//ゲームの更新処理を行う関数
void WindmillManager::Render()
{

	//球の描画
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//視界に入っているか
		if (Draw::GetInstance()->VisibilityRange(m_objectsList[i]->GetPosition(), 20))
			continue;

		//オブジェクトの描画
		m_objectsList[i]->Render();
	}
}
//ゲームの更新処理を行う関数
void WindmillManager::RenderShadowTex()
{

	//球の描画
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//視界に入っているか
		if (Draw::GetInstance()->DistanceRange(m_objectsList[i]->GetPosition()))
			continue;

		//オブジェクトの描画
		m_objectsList[i]->RenderShadowTex();
	}
}

//ゲームの終了処理を行う関数。解放処理が必要な場合　（Release関数などを呼び出す）は、この関数内でしょるする
void WindmillManager::Finalize()
{
	//後処理
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		m_objectsList[i].reset();
	}
}

void WindmillManager::CheckHitCharacter(Player* player)
{
	//プレイヤーとの当たり判定
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//大まかなプレイヤーと大まかな敵の当たり判定
		if (!m_objectsList[i]->GetRoughCollider()->CheckHitSphere(player->GetCollider()))
			continue;

		//プレイヤーのパーツと敵のパーツの当たり判定
		for (auto& airshipParts : m_objectsList[i]->GetParts())
		{

			//プレイヤーのパーツと大まかな敵の当たり判定
			if (!airshipParts->CollisionPlayer(player))
				continue;

			player->Damage(player->GetHP());
			return;

		}
	}
}

void WindmillManager::CheckHitEnemy(Enemy* enemy)
{
	//プレイヤーとの当たり判定
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//大まかなプレイヤーと大まかな敵の当たり判定
		if (!m_objectsList[i]->GetRoughCollider()->CheckHitSphere(enemy->GetCollider()))
			continue;

		//プレイヤーのパーツと敵のパーツの当たり判定
		for (auto& airshipParts : m_objectsList[i]->GetParts())
		{
			//直したほうがいい（）パーツと大枠のプレイヤーで当たり判定を行い

			//プレイヤーのパーツと大まかな敵の当たり判定
			if (!airshipParts->CollisionEnemy(enemy))
				continue;

			enemy->Damage(enemy->GetHP());
			return;
		}
	}
}
void WindmillManager::CheckHitAirship(Airship* airship)
{
	//プレイヤーとの当たり判定
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//大まかなプレイヤーと大まかな敵の当たり判定
		if (!m_objectsList[i]->GetRoughCollider()->CheckHitSphere(airship->GetCollider()))
			continue;

		//プレイヤーのパーツと敵のパーツの当たり判定
		for (auto& airshipParts : m_objectsList[i]->GetParts())
		{
			//直したほうがいい（）パーツと大枠のプレイヤーで当たり判定を行い
			//当たったら当たったパーツを返す当たってなかったら"null"
			IWindmillComponent* HitAirshipPart = airshipParts->Collision(airship);
			if (!HitAirshipPart)
				continue;

			//for (auto& playerParts : player->GetPlayerParts())
			//{
			//	//プレイヤーのパーツと大まかな敵の当たり判定
			//	if (!playerParts->Collision(HitAirshipPart))
			//		continue;

			airship->Damage(Player::PLAYER_MAX_HP);
			return;
			//}
		}
	}
}
