#pragma once

#include "ImaseLib/SceneManager.h"
#include "UserResources.h"
#include"Scene/GameObjects/UI/TransitionState.h"
#include"Scene/GameObjects/UI/MenuBackGround/MenuBackGroundUI.h"
#include"Scene/GameObjects/UI/Letter/StageSelectLetter.h"
#include"Scene/GameObjects/Camera/TitleCamera.h"
#include"Scene/SelectScene/MenuSelect/MenuSelect.h"
#include"Scene/GameObjects/UI/Letter/returnLetter/ReturnLetter.h"
class TitleScene : public Imase::Scene<UserResources>
{
public:
	TitleScene();
	~TitleScene() override;

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
	/// <summary>
	/// 
	/// </summary>
	void SaveGunData();

private:
	std::unique_ptr<TransitionState> m_transitionState;
	std::unique_ptr<ReturnLetter> m_returnLetter;
	std::unique_ptr<MenuBackGroundUI> m_menuBackGroundUI;

	std::unique_ptr <MenuSelect> m_menuSelect;
};

