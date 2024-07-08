//--------------------------------------------------------------------------------------
// File: StateHome.h
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#pragma once
#include"../../OptionScene.h"

class StateOptionScene : public OptionScene::State
{
public:
	enum OptionState
	{
		DRAW_OPTION_SCENE,
		SOUND_OPTION_SCENE,
		COUNT
	};

	StateOptionScene(OptionScene::FSM* fsm);
	~StateOptionScene();
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

	OptionScene::FSM* GetParentFSM() { return m_pParentFsm; }

	tito::MoveUserInterface* GetUnderBar()const { return m_underBar.get(); }

public:
	using FSM = FiniteStateMachine<StateOptionScene, OptionState>;
	using State = FSM::IState;

private:
	//
	OptionScene::FSM* m_pParentFsm;


	// 状態遷移
	std::unique_ptr<FSM> m_fsm;                //!< 有限ステートマシン
	std::unique_ptr<State> m_StateDrawOptionScene;         //!< [ステート]食べる
	std::unique_ptr<State> m_StateSoundOptionScene;         //!< [ステート]食べる

private:
	//ホームの文字
	std::unique_ptr <tito::UserInterface> m_optionLetter[OptionState::COUNT];

	//ホームの文字の当たり判定
	std::unique_ptr <Collider::Box2D> m_optionLetterCollision[OptionState::COUNT];

	std::unique_ptr <tito::MoveUserInterface> m_underBar;

};

