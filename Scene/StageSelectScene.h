#pragma once

#include "ImaseLib/SceneManager.h"
#include "UserResources.h"
#include"Scene/GameObjects/UI/TransitionState.h"
#include"Scene/GameObjects/UI/Letter/StageSelectLetter.h"
#include"Scene/GameObjects/UI/Letter/returnLetter/ReturnLetter.h"
#include"Scene/GameObjects/Camera/TitleCamera.h"
#include"Scene/GameObjects/PlayScene/Sun/Sun.h"
#include"Scene/GameObjects/SelectScene/SelectPlayer.h"
#include"Scene/StageSelect/StageSelect.h"
#include"Scene/GameObjects/SelectScene/Palace/Palace.h"
class StageSelectScene : public Imase::Scene<UserResources>
{
public:

	static const float TRANSITION_TIME;
public:
	StageSelectScene();
	~StageSelectScene() override;

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
		/// <summary>
	/// 影になるオブジェクトの描画
	/// </summary>
	void ShadowMapRender();

private:
	std::unique_ptr<TransitionState> m_transitionState;

	std::unique_ptr <StageSelect> m_stageSelect;

	std::unique_ptr <TitleCamera> m_titleCamera;

	std::unique_ptr <ReturnLetter> m_returnLetter;
	std::unique_ptr <Sun> m_sun;
	std::unique_ptr <StageSelectLetter> m_stageSelectLetter;
	std::unique_ptr <tito::MoveUserInterface> m_decision;
	std::unique_ptr <Collider::Box2D> m_decisionCol;
	bool m_m_decisionFlag;

	//宮殿のポインタ
	std::unique_ptr <Palace> m_palace;

	//プレイヤーのポインタ
	std::unique_ptr <SelectPlayer> m_player;


	//決定してから遷移するまでの時間
	float m_decisionStopTimer;

	//決定したかのフラグ
	bool m_decisionFlag;

	//戻りの決定したかのフラグ
	bool m_ReturnDecisionFlag;
	float m_timerShadowSpeed;

	/// <summary>
	/// 遷移するときの処理
	/// </summary>
	/// <param name="transitionTime">決定が押されてから遷移するまでの時間</param>
	void TransitionProcessing(const float& elapsedTime,const float& transitionTime);



};

