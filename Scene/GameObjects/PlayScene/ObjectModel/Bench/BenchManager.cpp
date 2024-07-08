#include"pch.h"
#include"BenchManager.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/Effect/SandstormEffect.h"

using namespace DirectX;
const int WINDMILL_COUNT(100);

BenchManager::BenchManager():
	MoveObjectsManager()
{
	std::ifstream obj("Resources/json/TwonScene/Json_TwonBench.Json");

	Json::CharReaderBuilder reader;

	Json::Value root;
	//ファイルを開く
	if (obj.is_open())
	{
		std::string errors;
		//
		if (Json::parseFromStream(reader, obj, &root, &errors))
		{
			const Json::Value& wallsArray = root["bench_01"];
			for (const Json::Value& wallDate : wallsArray)
			{
				//floatからVector3に変換
				std::unique_ptr<MoveObjects> windmill = std::make_unique<Bench>();
				windmill->SetPosition(
					SimpleMath::Vector3(wallDate["position"][0].asFloat(),
						wallDate["position"][1].asFloat(),
						wallDate["position"][2].asFloat()
					));
				windmill->SetRotateJson(
					SimpleMath::Vector3(wallDate["rotate"][0].asFloat(),
						wallDate["rotate"][1].asFloat(),
						wallDate["rotate"][2].asFloat()
					));
				AddMoveObjects(std::move(windmill));
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

}
