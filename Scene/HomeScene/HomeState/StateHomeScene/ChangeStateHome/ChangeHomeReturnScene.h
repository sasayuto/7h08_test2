//--------------------------------------------------------------------------------------
// File: ChangeStageSelectScene.h
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#pragma once
#include "../StateHomeScene.h"

class ChangeHomeReturnScene : public StateHomeScene::State
{
public:

	ChangeHomeReturnScene(StateHomeScene::FSM* fsm);
	~ChangeHomeReturnScene();

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
	//
	StateHomeScene::FSM* m_fsm;

};

