#pragma once

#include "ImaseLib/SceneManager.h"
#include "UserResources.h"

#include"Scene/GameObjects/PlayScene/Item/SupplyPointManager.h"
#include "Scene/GameObjects/Camera/PlaySceneCamera/PlaySceneCamera.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/EnemyManager.h"
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"
#include"Scene/GameObjects/UI/Gaueg.h"
#include"Scene/GameObjects/UI/TransitionState.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/StoneFloor.h"
#include"Scene/GameObjects/PlayScene/Character/Turret/TurretManager.h"
#include"Scene/GameObjects/PlayScene/Character/CrabRobot/CrabRobotManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/ObjectsManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Bench/BenchManager.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/FloorManagers/FloorManager_01.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Windmill/WindmillManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/StreetLight/StreetLightManager.h"
#include"Scene/GameObjects/PlayScene/Item/CoinManager.h"
#include"Scene/GameObjects/UI/Timer/Timer.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/AirshipManager.h"
#include"Scene/GameObjects/UI/Letter/returnLetter/ReturnLetter.h"
#include"Scene/GameObjects/PlayScene/Sandstorm/SandstormManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Objects/Walls/BigBrickWall/BigBrickWallManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Fence/FenceManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/HouseMoveObjects/HouseMoveObjectsManager.h"

//惑星
#include"Scene/GameObjects/Background/CloudyBackGround.h"

#include"PlayScene.h"
/// <summary>
/// TownSceneのクラスを定義する
/// </summary>
class TownScene : public PlayScene
{
public:
	TownScene() ;
	~TownScene() override;

	// 初期化
	void Initialize() override;

	// 更新
	void Update(float elapsedTime) override;

	// 描画
	void Render() override;

	// 終了処理
	void Finalize() override;

	// デバイスに依存するリソースを作成する関数
	void CreateDeviceDependentResources() override;

	// ウインドウサイズに依存するリソースを作成する関数
	void CreateWindowSizeDependentResources() override;

	// デバイスロストした時に呼び出される関数
	void ShadowMapRender() override;
	void OnDeviceLost() override;

	//追加
private:

	std::unique_ptr<PlaySceneCamera> m_Camera;

	// デバイスリソース
	DX::DeviceResources* m_deviceResources;

	//背景モデル
	std::unique_ptr<CloudyBackGround> m_cloudyBackGround;

	//背景モデル
	std::unique_ptr<StoneFloor> m_stoneFloor;

	//プレイヤーのポインタ
	std::unique_ptr<Player> m_player;

	//敵のポインタ
	std::unique_ptr<EnemyManager> m_enemyManager;

	//敵のポインタ
	std::unique_ptr<ReturnLetter> m_returnLetter;;

	//球のポインタ
	std::unique_ptr<BulletManager> m_bulletManager;

	//球のポインタ
	std::unique_ptr<WindmillManager> m_windmillManager;

	//球のポインタ
	std::unique_ptr<StreetLightManager> m_streetLightManager;

	//ゲージのポインタ
	std::unique_ptr<Gaueg> m_playerGaueg;

	//ゲージのポインタ
	std::unique_ptr<SupplyPointManager> m_supplyPointManager;

	//オブジェクトのポインタ
	std::unique_ptr<ObjectsManager> m_objectsManager;

	//オブジェクトのポインタ
	std::unique_ptr<FloorManager_01> m_floorManager_01;

	//オブジェクトのポインタ
	std::unique_ptr<BenchManager> m_benchManager;

	//オブジェクトのポインタ
	std::unique_ptr<CoinManager> m_coinManager;

	//オブジェクトのポインタ
	std::unique_ptr<AirshipManager> m_airshipManager;

	//オブジェクトのポインタ
	std::unique_ptr<SandstormManager> m_sndstormManager;

	//壁の管理者のポインタ
	std::unique_ptr<BigBrickWallManager> m_bigBrickWallManager;

	//ステージセレクトのポインタ
	std::unique_ptr<TransitionState> m_transitionState;

	//フェンス管理者のポインタ
	std::unique_ptr<FenceManager> m_fenceManager;

	//ステージセレクトのポインタ
	std::unique_ptr<HouseMoveObjectsManager> m_HouseMove_03Manager;
	//ステージセレクトのポインタ
	std::unique_ptr<HouseMoveObjectsManager> m_HouseMove_02Manager;
	//ステージセレクトのポインタ
	std::unique_ptr<HouseMoveObjectsManager> m_HouseMove_01Manager;

	//画面サイズ
	RECT m_rect;
	//けせ
	bool a = false;
	float m_timespeed = 0;
	//

};

