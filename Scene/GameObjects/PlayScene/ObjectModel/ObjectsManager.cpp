#include"pch.h"
#include"ObjectsManager.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"

//オブジェクト種類
#include"House.h"
#include"Objects/Houses/House_02.h"
#include"Objects/Houses/House_03.h"
#include"Objects/StoneStairs/StoneStairs.h"
#include"Objects/Walls/BigBrickWall/BigBrickWall.h"
using namespace DirectX;


ObjectsManager::ObjectsManager() 
{	
}

//コンストラクタと呼ばれる関数
ObjectsManager::~ObjectsManager()
{

}

//ゲームの初期化を行う関数
void ObjectsManager::Intialize()
{
	std::ifstream obj("Resources/json/TwonScene/Json_TwonObjects.Json");
	Json::CharReaderBuilder reader;
	Json::Value root;

	// ファイルが開かれているかを確認します。
	if (obj.is_open()) {
		std::string errors;

		// ファイルからJSONをパースします。
		if (Json::parseFromStream(reader, obj, &root, &errors))
		{
			// JSONに "house" が存在し、配列であるかどうかを確認します。
			if (root.isMember("objects") && root["objects"].isArray())
			{
				// "house" 配列を取得します。
				const Json::Value& stoneStairsArray = root["objects"][0]["stoneStairs"];

				// "house" 配列内の各要素に対してループを実行します。
				for (unsigned i = 0; i < stoneStairsArray.size(); i++)
				{
					// 新しいオブジェクトを作成し、位置と回転を設定します。
					std::unique_ptr<Objects> stoneStairs = std::make_unique<StoneStairs>();
					stoneStairs->SetPosition(SimpleMath::Vector3(
						stoneStairsArray[i]["position"][0].asFloat(),
						stoneStairsArray[i]["position"][1].asFloat(),
						stoneStairsArray[i]["position"][2].asFloat()
					));
					stoneStairs->SetRotateJson(SimpleMath::Vector3(
						stoneStairsArray[i]["rotate"][0].asFloat(),
						stoneStairsArray[i]["rotate"][1].asFloat(),
						stoneStairsArray[i]["rotate"][2].asFloat()
					));
					// リストにオブジェクトを追加します。
					m_objectsList.push_back(std::move(stoneStairs));

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
	for (int i = 0; i < m_objectsList.size(); i++) {
		m_objectsList[i]->Initialize();
	}
}

void ObjectsManager::CollJson(const Json::Value& ary, Objects* objects)
{
	// 当たり判定を確認したいときに使えるよ
	std::ofstream outputfile("Resources/ColliderDate/ColDateHouse_03.txt");
	for (unsigned j = 0; j < ary["Colliders"].size(); j++) {
		const Json::Value& nowcol = ary["Colliders"][j];
		DirectX::SimpleMath::Vector3 pos = SimpleMath::Vector3::Transform(SimpleMath::Vector3(
			nowcol["Pos"][0].asFloat(),
			nowcol["Pos"][1].asFloat(),
			nowcol["Pos"][2].asFloat()),objects->GetRotate());
		if (nowcol.isMember("OOMA") && nowcol["OOMA"].isArray())
		{
			float Rud = nowcol["Ees"][0].asFloat();
			objects->GetRoughCollider()->SetPosition(objects->GetPosition() + pos);
			objects->GetRoughCollider()->SetRadius(Rud);
			std::ostringstream oss;
			oss << "GetRoughCollider()->SetPosition(GetPosition()+DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(" << pos.x << "f, " << pos.y << "f, " << pos.z << "f),GetRotate()));" << std::endl;
			oss << "GetRoughCollider()->SetRadius(" << Rud << "f);" << std::endl;
			outputfile << oss.str() << std::endl << std::endl;
		}

		if (nowcol.isMember("S") && nowcol["S"].isArray()) {
			float Rud = objects->GetObjectsModel()->meshes[0]->boundingSphere.Radius + nowcol["Ees"][0].asFloat();
			objects->GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateSphereCollider(objects->GetPosition(), pos, Rud));
			std::ostringstream oss;
			oss << "GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateSphereCollider(" << std::endl;
			oss << "GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(" << pos.x << "f, " << pos.y << "f, " << pos.z << "f),GetRotate())," << std::endl;
			oss << Rud << "f));" << std::endl;
			outputfile << oss.str() << std::endl << std::endl;
		}

		if (nowcol.isMember("O") && nowcol["O"].isArray() || nowcol.isMember("B") && nowcol["B"].isArray()) {

			DirectX::SimpleMath::Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				DirectX::XMConvertToRadians(nowcol["Rot"][0].asFloat()),
				DirectX::XMConvertToRadians(nowcol["Rot"][1].asFloat()),
				DirectX::XMConvertToRadians(nowcol["Rot"][2].asFloat()));

			DirectX::SimpleMath::Vector3 Eex =SimpleMath::Vector3(
				nowcol["Ees"][0].asFloat(),
				nowcol["Ees"][1].asFloat(),
				nowcol["Ees"][2].asFloat());
			//当たり判定を作る
			objects->GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(objects->GetPosition(), objects->GetRotate(), pos, rot, Eex));
			std::ostringstream oss;
			if (nowcol.isMember("O") && nowcol["O"].isArray()) {
				oss << "GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(" << std::endl;
				oss << "GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(" << pos.x << "f, " << pos.y << "f, " << pos.z << "f),GetRotate())," << std::endl;
				oss << "DirectX::SimpleMath::Quaternion(" << rot.x << "f," << rot.y << "f," << rot.z << "f," << rot.w << "f)*GetRotate()," << std::endl;;
				oss << "DirectX::SimpleMath::Vector3(" << Eex.x << "f," << Eex.y << "f," << Eex.z << "f)));" << std::endl;;
			}
			if (nowcol.isMember("B") && nowcol["B"].isArray()) {
				oss << "GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(" << std::endl;
				oss << "GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(" << pos.x << "f, " << pos.y << "f, " << pos.z << "f),GetRotate())," << std::endl;
				oss << "DirectX::SimpleMath::Vector3(" << Eex.x << "f," << Eex.y << "f," << Eex.z << "f)));" << std::endl;;
			}
			outputfile << oss.str() << std::endl << std::endl;

		}

	}
}

//ゲームの更新を行う関数
void ObjectsManager::Update()
{
	//m_objectsList.clear();
	//Intialize();

	//球の更新
	for (int i = 0; i < m_objectsList.size(); i++)
	{		
		//オブジェクトの更新
		m_objectsList[i]->Update();
	}
}

//ゲームの更新処理を行う関数
void ObjectsManager::Render()
{
	//球の描画
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//視界に入っているか
		if (Draw::GetInstance()->DistanceRange(m_objectsList[i]->GetPosition()))
			continue;

		//オブジェクトの描画
		m_objectsList[i]->Render();
	}
}

void ObjectsManager::RenderShadowTex()
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
void ObjectsManager::Finalize()
{
	//後処理
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		m_objectsList[i].reset();
	}
}

void ObjectsManager::CheckHitCharacter(Player* player)
{
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//大まかなプレイヤーとの当たり判定
		if (!m_objectsList[i]->GetRoughCollider()->CheckHitSphere(player->GetCollider()))
			continue;

		//プレイヤーとの当たり判定
		if (!m_objectsList[i]->GetCollider()->CheckHitOneOrMore(player->GetCollider()))
			continue;

		for (auto& playerParts : player->GetParts())
		{
			//パーツとの当たり判定
			if (!playerParts->CollisionObjects(m_objectsList[i].get()))
				continue;

			player->Damage(player->GetHP());
			//処理軽減のため（当たっていたら終了）
			return;
		}
	}
}

void ObjectsManager::CheckHitEnemy(Enemy* enemy)
{
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//大まかなプレイヤーとの当たり判定
		if (!m_objectsList[i]->GetRoughCollider()->CheckHitSphere(enemy->GetCollider()))
			continue;

		//プレイヤーとの当たり判定
		if (!m_objectsList[i]->GetCollider()->CheckHitOneOrMore(enemy->GetCollider()))
			continue;

		for (auto& enemyParts : enemy->GetParts())
		{
			//パーツとの当たり判定
			if (!enemyParts->CollisionObjects(m_objectsList[i].get()))
				continue;

			enemy->Damage(enemy->GetHP());
			//処理軽減のため（当たっていたら終了）
			return;
		}
		return;
	}
}
void ObjectsManager::CheckHitAirship(Airship* airship)
{
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//大まかなプレイヤーとの当たり判定
		if (!m_objectsList[i]->GetRoughCollider()->CheckHitSphere(airship->GetCollider()))
			continue;

		//プレイヤーとの当たり判定
		if (!m_objectsList[i]->GetCollider()->CheckHitOneOrMore(airship->GetCollider()))
			continue;

		for (auto& airshipParts : airship->GetParts())
		{
			if (!airshipParts->Collision(m_objectsList[i].get()))
				continue;

			//処理軽減のため（当たっていたら終了）
			return;
		}
		return;
	}
}
