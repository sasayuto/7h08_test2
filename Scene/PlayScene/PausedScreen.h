#pragma once

#include"Scene/GameObjects/UI/TransitionState.h"
#include"ImaseLib/SceneManager.h"
#include"ImaseLib/MoveUserInterface.h"
#include"ImaseLib/UserInterface.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include "Scene/GameObjects/FiniteStateMachine.h"

class PlayScene;
class UserResources;

/// <summary>
/// PausedScreenのクラスを定義する
/// </summary>
class PausedScreen 
{
public:	
	enum OptionState
	{
		OPTION_SCENE,
		DRAW_OPTION_SCENE,
		SOUND_OPTION_SCENE,
		COUNTs
	};

	enum  PausedState
	{
		RESUME_GAME,
		STAGE_SELECT_SCENE,
		PLAYER_CUSTOM_SCENE,
		COUNT,
	};

	PausedScreen(Imase::Scene<UserResources>* playScene) ;
	~PausedScreen();

	// 初期化
	void Initialize() ;

	// 更新
	bool Update(float elapsedTime);

	// 描画
	void Render() ;

	// 終了処理
	void Finalize() ;

	void Enter();
	void Exit() ;

	// デバイスに依存するリソースを作成する関数
	void CreateDeviceDependentResources() ;

public:
	bool GetMenuFlag()const { return m_menuSceneFlag; };
	void SetMenuFlag(const bool& menuFlag) { m_menuSceneFlag = menuFlag; };

	void MenuInitialize();

	void MenuUpdate();
//menu
private:
	Imase::Scene<UserResources>* m_pPlayScene;
	bool m_menuSceneFlag;
	bool m_menuSceneSelectFlag;
	//ステージセレクトのポインタ
	std::unique_ptr<TransitionState> m_transitionState;

	//ステージセレクトのポインタ
	std::unique_ptr<TransitionState> m_Translucent;
public:
	using FSM = FiniteStateMachine<PausedScreen, OptionState>;
	using State = FSM::IState;

private:

	// 状態遷移
	std::unique_ptr<FSM> m_fsm;                //!< 有限ステートマシン
	std::unique_ptr<State> m_State[OptionState::COUNTs];    //!< [ステート]食料を探す 

private:
	//ホームの文字
	std::unique_ptr <tito::UserInterface> m_homeLetter[PausedState::COUNT];

	//ホームの文字の当たり判定
	std::unique_ptr <Collider::Box2D> m_homeLetterCollision[PausedState::COUNT];

	//選択中の枠
	std::unique_ptr <tito::MoveUserInterface> m_underBar;

};

class StateSoundOnScene : public PausedScreen::State
{

public:
	StateSoundOnScene(PausedScreen::FSM* fsm) :m_fsm(fsm){};
	~StateSoundOnScene() {};
	// 初期化
	void Initialize() override {};

	// 更新
	void Update(const float& elapsedTime) override { elapsedTime; };

	// 描画
	void Render() override {};

	// 終了処理
	void Finalize() override {};

	void Enter()override {};
	void Exit() override {};

	// デバイスに依存するリソースを作成する関数
	void CreateDeviceDependentResources() override {};

private:
	PausedScreen::FSM* m_fsm;
};
