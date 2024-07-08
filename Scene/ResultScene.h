#pragma once

#include "ImaseLib/SceneManager.h"
#include "UserResources.h"
#include "ImaseLib/UserInterface.h"
#include"Scene/GameObjects/UI/TransitionState.h"
#include"Scene/GameObjects/Camera/TitleCamera.h"
#include"Scene/GameObjects/Background/CloudyBackGround.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/StoneFloor.h"

class ResultScene : public Imase::Scene<UserResources>
{
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

private:
	std::unique_ptr <tito::UserInterface> m_ResultBaseUI;

	std::unique_ptr <TransitionState> m_transitionState;
	std::unique_ptr<TitleCamera> m_camera;
	std::unique_ptr<CloudyBackGround> m_CloudyBackGround;
	//背景モデル
	std::unique_ptr<StoneFloor> m_stoneFloor;

};

