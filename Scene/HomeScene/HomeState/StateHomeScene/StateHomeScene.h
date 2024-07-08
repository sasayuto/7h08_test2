//--------------------------------------------------------------------------------------
// File: StateHomeScene.h
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#pragma once
#include"Scene/HomeScene/HomeScene.h"
#include"ImaseLib/MoveUserInterface.h"
#include"ImaseLib/UserInterface.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
class StateHomeScene : public HomeScene::State
{
public:
	enum  HomeState
	{
		STAGE_SELECT_SCENE,
		PLAYER_CUSTOM_SCENE,
		OPTION_SCENE,
		COUNT,
		RETURN_SCENE,//何にも使わないのでCountの下
		NONE_SCENE
	};

	StateHomeScene(HomeScene::FSM* fsm);

	~StateHomeScene();
	// 初期化
	void Initialize() override;

	// 更新
	void Update(const float& elapsedTime) override;

	// 描画
	void Render() override;

	// 終了処理
	void Finalize() override;

	void Enter()override;
	void Exit() override;

	// デバイスに依存するリソースを作成する関数
	void CreateDeviceDependentResources() override;

	HomeScene::FSM* GetParentFSM() { return m_pParentFsm; }

	tito::MoveUserInterface* GetUnderBar()const { return m_underBar.get(); }
public:
	using FSM = FiniteStateMachine<StateHomeScene, HomeState>;
	using State = FSM::IState;

private:
	//
	HomeScene::FSM* m_pParentFsm;

	// 状態遷移
	std::unique_ptr<FSM> m_fsm;                //!< 有限ステートマシン
	std::unique_ptr<State> m_StateOptionScene;         //!< [ステート]食べる
	std::unique_ptr<State> m_StatePlayerCustomScene;         //!< [ステート]食べる
	std::unique_ptr<State> m_StateStageSelectScene;         //!< [ステート]食べる
	std::unique_ptr<State> m_StateHomeReturnScene;         //!< [ステート]食べる
	std::unique_ptr<State> m_StateNoneScene;         //!< [ステート]食べる


private:
	//ホームの文字
	std::unique_ptr <tito::UserInterface> m_homeLetter[HomeState::COUNT];

	//ホームの文字の当たり判定
	std::unique_ptr <Collider::Box2D> m_homeLetterCollision[HomeState::COUNT];

	//選択中の枠
	std::unique_ptr <tito::MoveUserInterface> m_underBar;
};

