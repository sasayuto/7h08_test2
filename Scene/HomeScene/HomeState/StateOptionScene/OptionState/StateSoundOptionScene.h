//--------------------------------------------------------------------------------------
// File: StateSoundOptionScene.h
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#pragma once
#include"../OptionScene.h"
#include"Scene/GameObjects/UI/Gaueg/VolumeGaueg.h"

class StateSoundOptionScene : public OptionScene::State
{
	
public:

	StateSoundOptionScene(OptionScene::FSM* fsm);
	~StateSoundOptionScene();
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
	OptionScene::FSM* m_fsm;

	//ボリュームのゲージのポインタ
	std::unique_ptr<VolumeGaueg> m_bgmGaueg;

	//ボリュームのゲージのポインタ
	std::unique_ptr<VolumeGaueg> m_soundEffectGaueg;

	//ホームの文字
	std::unique_ptr <tito::UserInterface> m_Letter[2];

};

