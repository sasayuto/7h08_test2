//--------------------------------------------------------------------------------------
// File: StateIteme.h
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#pragma once
#include"Scene/HomeScene/HomeScene.h"

class OptionScene : public HomeScene::State
{
public:
	enum class OptionState
	{
		OPTION_SCENE,
		DRAW_OPTION_SCENE,
		SOUND_OPTION_SCENE
	};

	OptionScene(HomeScene::FSM* fsm);
	~OptionScene();
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

public:
	using FSM = FiniteStateMachine<OptionScene, OptionState>;
	using State = FSM::IState;

private:
	HomeScene::FSM* m_pParentFsm;


	// 状態遷移
	std::unique_ptr<FSM> m_fsm;                //!< 有限ステートマシン
	std::unique_ptr<State> m_StateDrawOptionScene;         //!< [ステート]食べる
	std::unique_ptr<State> m_StateSoundOptionScene;         //!< [ステート]食べる
	std::unique_ptr<State> m_StateOptionScene;         //!< [ステート]食べる

};

