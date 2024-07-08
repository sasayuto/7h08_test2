//--------------------------------------------------------------------------------------
// File: StateHomeScene.h
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#pragma once
#include"Scene/HomeScene/HomeScene.h"

class StatePlayerCustomScene : public HomeScene::State
{
public:

	StatePlayerCustomScene(HomeScene::FSM* fsm);
	~StatePlayerCustomScene();
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
private:
	HomeScene::FSM* m_fsm;
	//ホームの文字
	std::unique_ptr <tito::UserInterface> m_Letter;

	//選択中の枠
	std::unique_ptr <tito::MoveUserInterface> m_underBar;

};

