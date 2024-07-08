//--------------------------------------------------------------------------------------
// File: MenuScene.h
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#pragma once
#include "ImaseLib/SceneManager.h"
#include "UserResources.h"
#include "Scene/StageSelectScene.h"
#include "Scene/GameObjects/FiniteStateMachine.h"
#include"Scene/GameObjects/UI/MenuBackGround/MenuBackGroundUI.h"
#include"Scene/GameObjects/Camera/TitleCamera.h"
#include"Scene/GameObjects/Background/CloudyBackGround.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/StoneFloor.h"

class HomeScene : public Imase::Scene<UserResources>
{
	// クラス定数
public:

	//UIの縦幅
	static const int LETTER_WIDTH = 90;


	enum HomeState
	{
		STAGE_SELECT_SCENE,
		PLAYER_CUSTOM_SCENE,
		OPTION_SCENE,
		HOME_SCENE,
		COUNT
	};

public:
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

	TransitionState* GetTransitionState() { return m_transitionState.get(); }
	ReturnLetter* GetReturnLetter() { return m_returnLetter.get(); }
	// エイリアス宣言
public:
	using FSM = FiniteStateMachine<HomeScene, HomeState>;
	using State = FSM::IState;

private:
	/// <summary>
	/// 
	/// </summary>
	void SaveGunData();

private:

	// 状態遷移
	std::unique_ptr<FSM> m_fsm;                //!< 有限ステートマシン
	std::unique_ptr<State> m_State[COUNT];    //!< [ステート]食料を探す 

private:
	std::unique_ptr<TransitionState> m_transitionState;
	std::unique_ptr<ReturnLetter> m_returnLetter;
	std::unique_ptr<TitleCamera> m_camera;
	std::unique_ptr<CloudyBackGround> m_CloudyBackGround;
	//背景モデル
	std::unique_ptr<StoneFloor> m_stoneFloor;

};
