#include"pch.h"
#include"StreetLightManager.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/Effect/SandstormEffect.h"

using namespace DirectX;
const int WINDMILL_COUNT(00);

StreetLightManager::StreetLightManager() :
	m_bulletManager(nullptr),
	m_objectsList{},
	m_streetLightKillCount(0)
{
}

//コンストラクタと呼ばれる関数
StreetLightManager::~StreetLightManager()
{

}

//ゲームの初期化を行う関数
void StreetLightManager::Intialize(BulletManager* bulletManager)
{
	m_bulletManager = bulletManager;
	std::ifstream obj("Resources/json/TwonScene/Json_TwonStreetLight.Json");
	Json::CharReaderBuilder reader;
	Json::Value root;

	// ファイルが開かれているかを確認します。
	if (obj.is_open()) {
		std::string errors;

		// ファイルからJSONをパースします。
		if (Json::parseFromStream(reader, obj, &root, &errors))
		{
			// "house" 配列を取得します。
			const Json::Value& Array = root["StreetLight"];

			// "house" 配列内の各要素に対してループを実行します。
			for (const Json::Value& wallData : Array)
			{
				// 新しいオブジェクトを作成し、位置と回転を設定します。
				std::unique_ptr<StreetLight> objects = std::make_unique<StreetLight>();
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
		m_objectsList[i]->Initialize(bulletManager,this);
	}

}

//ゲームの更新を行う関数
void StreetLightManager::Update(const float& elapsedTime)
{
	//m_objectsList.clear();
	//Intialize(m_bulletManager);
	//球の更新
	for (int i = 0; i < m_objectsList.size(); i++)
	{		
		//死んでいたら更新しない
		if (!m_objectsList[i]->GetSurvival())
			continue;

		//オブジェクトの更新
		m_objectsList[i]->Update(elapsedTime);
	}
}

//ゲームの更新処理を行う関数
void StreetLightManager::Render()
{
	//球の描画
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//死んでいたら描画しない
		if (!m_objectsList[i]->GetSurvival())
			continue;

		//オブジェクトの描画
		m_objectsList[i]->Render();
	}
}
//ゲームの更新処理を行う関数
void StreetLightManager::RenderShadowTex(const bool dynamicflag)
{
	//球の描画
	for (int i = 0; i < m_objectsList.size(); i++)
	{

		//死んでいたら更新しない
		if (m_objectsList[i]->GetAllSurvivalFlag() == dynamicflag)
			continue;

		//死んでいたら更新しない
		if (!m_objectsList[i]->GetSurvival())
			continue;

		//視界に入っているか
		if (Draw::GetInstance()->DistanceRange(m_objectsList[i]->GetPosition()))
			continue;

		//オブジェクトの描画
		m_objectsList[i]->RenderShadowTex();
	}
}

//ゲームの終了処理を行う関数。解放処理が必要な場合　（Release関数などを呼び出す）は、この関数内でしょるする
void StreetLightManager::Finalize()
{
	//後処理
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		m_objectsList[i].reset();
	}
}

void StreetLightManager::CheckHitCharacter(Player* player)
{
	////プレイヤーとの当たり判定
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//死んでいたら更新しない
		if (!m_objectsList[i]->GetSurvival())
			continue;

		//大まかなプレイヤーと大まかな敵の当たり判定
		if (!m_objectsList[i]->GetRoughCollider()->CheckHitSphere(player->GetCollider()))
			continue;

		for (auto& airshipParts : m_objectsList[i]->GetParts())
		{
			//大まかなプレイヤーと街灯のパーツの当たり判定と
			//プレイヤーのパーツと敵のパーツの当たり判定
			if (!airshipParts->CollisionPlayer(player))
				continue;

			//パーツごとでばらけるので親の当たり判定を大きくする
			m_objectsList[i]->GetRoughCollider()->SetRadius(
				m_objectsList[i]->GetRoughCollider()->GetRadius() * 5.0f
			);

			return;
		}
	}
}

void StreetLightManager::CheckHitEnemy(Enemy* enemy)
{
	////プレイヤーとの当たり判定
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//死んでいたら更新しない
		if (!m_objectsList[i]->GetSurvival())
			continue;

		//大まかなプレイヤーと大まかな敵の当たり判定
		if (!m_objectsList[i]->GetRoughCollider()->CheckHitSphere(enemy->GetCollider()))
			continue;

		//プレイヤーのパーツと敵のパーツの当たり判定
		for (auto& airshipParts : m_objectsList[i]->GetParts())
		{
			//直したほうがいい（）パーツと大枠のプレイヤーで当たり判定を行い
			//当たったら当たったパーツを返す当たってなかったら"null"
			//if (!airshipParts->CollisionPlayer(enemy))
				continue;

				//パーツごとでばらけるので親の当たり判定を大きくする
				m_objectsList[i]->GetRoughCollider()->SetRadius(
					m_objectsList[i]->GetRoughCollider()->GetRadius() * 5.0f
				);

			return;
		}
	}
}
void StreetLightManager::CheckHitSandstorm(SandstormEffect* sandstormEffect)
{
	////プレイヤーとの当たり判定
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//死んでいたら更新しない
		if (!m_objectsList[i]->GetSurvival())
			continue;

		//大まかなプレイヤーと大まかな敵の当たり判定
		if (!m_objectsList[i]->GetRoughCollider()->CheckHitSphereBox(sandstormEffect->GetCollider()))
			continue;

		//プレイヤーのパーツと敵のパーツの当たり判定
		for (auto& airshipParts : m_objectsList[i]->GetParts())
		{
			//直したほうがいい（）パーツと大枠のプレイヤーで当たり判定を行い
			//当たったら当たったパーツを返す当たってなかったら"null"
			if (!airshipParts->CollisionSandstorm(sandstormEffect))
				continue;

			//パーツごとでばらけるので親の当たり判定を大きくする
			m_objectsList[i]->GetRoughCollider()->SetRadius(
				m_objectsList[i]->GetRoughCollider()->GetRadius() * 5.0f
			);
		}
	}

}

void StreetLightManager::CheckHitAirship(Airship* airship)
{
	////プレイヤーとの当たり判定
	//for (int i = 0; i < m_objectsList.size(); i++)
	//{
	//	//大まかなプレイヤーと大まかな敵の当たり判定
	//	if (!m_objectsList[i]->GetRoughCollider()->CheckHitSphere(airship->GetCollider()))
	//		continue;

	//	//プレイヤーのパーツと敵のパーツの当たり判定
	//	for (auto& airshipParts : m_objectsList[i]->GetParts())
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
