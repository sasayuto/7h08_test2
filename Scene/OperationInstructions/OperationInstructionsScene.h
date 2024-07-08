#pragma once

#include "ImaseLib/SceneManager.h"
#include "UserResources.h"
#include"Scene/GameObjects/UI/TransitionState.h"
#include"Scene/GameObjects/UI/OperationInstructions/OperationInstructionsUI.h"
#include"Scene/GameObjects/UI/Letter/returnLetter/ReturnLetter.h"
class OperationInstructionsScene : public Imase::Scene<UserResources>
{
public:
	OperationInstructionsScene();
	~OperationInstructionsScene() override;

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

private:
	std::unique_ptr<ReturnLetter> m_returnLetter;
	std::unique_ptr<TransitionState> m_transitionState;
	std::unique_ptr<OperationInstructionsUI> m_operationInstructionsUI;
};

