#pragma once
#include"HouseMoveObjects.h"

class Enemy;
class Player;
class Airship;
class BulletManager;
class SandstormEffect;

/// <summary>
/// オブジェクトの管理者のクラスを定義する
/// </summary>
class HouseMoveObjectsManager
{
public:
	//キルカウント
	int GetBenchKillCount() { return m_benchKillCount; }
	void SetBenchKillCount(int benchKillCount) { m_benchKillCount = benchKillCount; }

	//子のパーツを生成
	void AddMoveObjects(std::unique_ptr<HouseMoveObjects> moveObjects)  { m_HouseMoveObjectsManager.push_back(std::move(moveObjects)); }

	//オブジェクトのポインタ
	std::vector<std::unique_ptr<HouseMoveObjects>>& GetHouseMoveObjectsManager() { return m_HouseMoveObjectsManager; };

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="mapLoader">マップのアドレス</param>
	HouseMoveObjectsManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~HouseMoveObjectsManager();

	/// <summary>
	/// 初期化する
	/// </summary>
	template<typename TTT>
	void Intialize(BulletManager* bulletManager, std::string failName)
	{
		std::vector<DirectX::SimpleMath::Vector3> ColliderPosition[TTT::PART_NUM];
		std::vector<DirectX::SimpleMath::Vector3> ColliderExtents[TTT::PART_NUM];
		std::vector<DirectX::SimpleMath::Quaternion> ColliderRotate[TTT::PART_NUM];

		std::ifstream obj(failName);

		Json::CharReaderBuilder reader;
		Json::Value root;
		if (obj.is_open()) {
			std::string errors;
			// ファイルからJSONをパースします。
			if (Json::parseFromStream(reader, obj, &root, &errors))
			{
				if (root.isMember("ColliderDate") && root["ColliderDate"].isArray())
				{
					for (size_t i = 0; i < TTT::PART_NUM; i++)
					{
						std::string numberString = std::to_string(i + 1);
						// 一桁の場合は数字の前に0を追加
						if (numberString.length() == 1) numberString = "0" + numberString;
						// ファイルが開かれているかを確認します。
								// JSONに "ColliderDate" が存在し、配列であるかどうかを確認します。
							// "ColliderDate" 配列を取得します。
						const Json::Value& Array = root["ColliderDate"][0][numberString][0];

						// JSONに "ColliderDate" が存在し、配列であるかどうかを確認します。
						if (Array.isMember("Obb") && Array["Obb"].isArray())
						{

							// "ColliderDate" 配列内の各要素に対してループを実行します。
							for (auto& houseData : Array["Obb"]) {

								ColliderPosition[i].push_back(
									DirectX::SimpleMath::Vector3(
										houseData["position"][0].asFloat(),
										houseData["position"][1].asFloat(),
										houseData["position"][2].asFloat()
									)
								);

								ColliderExtents[i].push_back(
									DirectX::SimpleMath::Vector3(
									houseData["extents"][0].asFloat(),
									houseData["extents"][1].asFloat(),
									houseData["extents"][2].asFloat()
								)
								);

								ColliderRotate[i].push_back(
									DirectX::SimpleMath::Quaternion(
										houseData["rotate"][0].asFloat(),
										houseData["rotate"][1].asFloat(),
										houseData["rotate"][2].asFloat(),
										houseData["rotate"][3].asFloat()
									)
								);

							}
						}
					}
				}
				if (root.isMember("Posture") && root["Posture"].isArray())
				{
					for (auto& houseData : root["Posture"]) {
						{						//floatからVector3に変換
							std::unique_ptr<HouseMoveObjects> windmill = std::make_unique<TTT>();

							windmill->SetPosition(
								DirectX::SimpleMath::Vector3(houseData["position"][0].asFloat(),
									houseData["position"][1].asFloat(),
									houseData["position"][2].asFloat()
								));

							windmill->SetRotateJson(
								DirectX::SimpleMath::Vector3(houseData["rotate"][0].asFloat(),
									houseData["rotate"][1].asFloat(),
									houseData["rotate"][2].asFloat()
								));

							AddMoveObjects(std::move(windmill));
						}

					}
				}
			}
		}

		m_pBulletManager = bulletManager;

		for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
		{
			//初期化する
			m_HouseMoveObjectsManager[i]->Initialize(bulletManager, this, ColliderPosition, ColliderExtents, ColliderRotate);
		}

	}

	/// <summary>
	/// 更新する
	/// </summary>
	void Update(const float& elapsedTime);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

	/// <summary>
	/// シャドウマップ用の画像を作る
	/// </summary>
	void RenderShadowTex(const bool flag);


	/// <summary>
	/// 後始末
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// プレイヤーと球の当たり判定
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	void CheckHitCharacter(Player* player);

	/// <summary>
	/// プレイヤーと球の当たり判定
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	void CheckHitEnemy(Enemy* enemy);
	
	/// <summary>
	/// 飛行船と球の当たり判定
	/// </summary>
	/// <param name="character">敵のアドレス</param>
	virtual void CheckHitAirship(Airship* airship);

	/// <summary>
	/// 飛行船と球の当たり判定
	/// </summary>
	/// <param name="character">敵のアドレス</param>
	void CheckHitSandstorm(SandstormEffect* sandstormEffect);

private:
	//オブジェクトのポインタ
	std::vector<std::unique_ptr<HouseMoveObjects>> m_breakObjectsManager;

	//オブジェクトのポインタ
	std::vector<std::unique_ptr<HouseMoveObjects>> m_HouseMoveObjectsManager;

	BulletManager* m_pBulletManager;

	//キルカウント
	int m_benchKillCount;
};

