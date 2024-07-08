#pragma once

#include "ImaseLib/SceneManager.h"
#include "UserResources.h"

#include"Scene/GameObjects/UI/SwayUserInterface.h"
#include"Scene/GameObjects/UI/TransitionState.h"
#include"Scene/GameObjects/UI/Letter/SpaseLetter.h"
#include"Scene/GameObjects/Camera/StageSelectCamera.h"
#include"Scene/GameObjects/Background/CloudyBackGround.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy_03.h"
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/ObjectsManager.h"
#include"Scene/GameObjects/PlayScene/Sun/Sun.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Objects/Walls/BigBrickWall/BigBrickWallManager.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/StoneFloor.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/HouseMoveObjects/HouseMoveObjectsManager.h"

class GameTitle : public Imase::Scene<UserResources>
{
public:

	static const float SELECT_TINE;

	GameTitle();
	~GameTitle() override;

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
	void OnDeviceLost() override;

	/// <summary>
	/// 影になるオブジェクトの描画
	/// </summary>
	void ShadowMapRender();

private:
	//ゲージのポインタ
	std::unique_ptr<SwayUserInterface> m_titleName;
	std::unique_ptr <TransitionState> m_transitionState;
	std::unique_ptr <StageSelectCamera> m_titleCamera;
	std::unique_ptr <Background> m_grandCanyon;
	std::unique_ptr <Enemy> m_enemy;
	std::unique_ptr <BulletManager> m_bulletManager;
	std::unique_ptr <ObjectsManager> m_objectsManager;
	std::unique_ptr <Sun> m_sun;
	std::unique_ptr <SpaseLetter> m_spaseLetter;
	//シーン遷移のアニメーションのポインタ
	std::unique_ptr<tito::Transition> m_translucent;

	float m_timerShadowSpeed;
	//背景モデル
	std::unique_ptr<StoneFloor> m_stoneFloor;

	//オブジェクトのポインタ
	std::unique_ptr<FloorManager_01> m_floorManager_01;
	//壁の管理者のポインタ
	std::unique_ptr<BigBrickWallManager> m_bigBrickWallManager;

	//ステージセレクトのポインタ
	std::unique_ptr<HouseMoveObjectsManager> m_HouseMove_03Manager;
	//ステージセレクトのポインタ
	std::unique_ptr<HouseMoveObjectsManager> m_HouseMove_02Manager;
	//ステージセレクトのポインタ
	std::unique_ptr<HouseMoveObjectsManager> m_HouseMove_01Manager;

	//経過時間
	float m_nowTimer;
	float m_transition;
};

