#pragma once

#include "ImaseLib/SceneManager.h"
#include "UserResources.h"
#include"Scene/GameObjects/UI/Timer/Timer.h"
#include"Scene/GameObjects/UI/Timer/Score.h"
#include"Scene/GameObjects/PlayScene/Sun/Sun.h"
#include"Scene/PlayScene/PausedScreen.h"

/// <summary>
/// PlaySceneの基底クラスを定義する
/// </summary>
class PlayScene : public Imase::Scene<UserResources>
{
public:
	PlayScene() ;
	~PlayScene() override;

	// 初期化
	virtual void Initialize() override;

	// 更新
	virtual void Update(float elapsedTime) override;

	// 描画
	virtual void Render() override;

	// 描画
	virtual void ShadowMapRender() {};

	// 終了処理
	virtual void Finalize() override;

	// デバイスに依存するリソースを作成する関数
	virtual void CreateDeviceDependentResources() override;

	// ウインドウサイズに依存するリソースを作成する関数
	virtual void CreateWindowSizeDependentResources() override;

	// デバイスロストした時に呼び出される関数
	virtual void OnDeviceLost() override;

	//追加

public:
	bool GetMenuFlag()const { return m_menuSceneFlag; };
	void SetMenuFlag(const bool& menuFlag) { m_menuSceneFlag = menuFlag; };

	float GetTimer()const { return m_timer; };
	void SetTimer(const float& timer) { m_timer = timer; };

private:
	//オブジェクトのポインタ
	std::unique_ptr<TimerTex> m_timerTex;

	//太陽のポインタ
	std::unique_ptr<Sun> m_sun;

	//オブジェクトのポインタ
	std::unique_ptr<ScoreTex> m_score;
	//秒数
	float m_timer;
//menu
private:
	//ステージセレクトのポインタ
	std::unique_ptr<PausedScreen> m_PausedScreen;
	bool m_menuSceneFlag;

};

