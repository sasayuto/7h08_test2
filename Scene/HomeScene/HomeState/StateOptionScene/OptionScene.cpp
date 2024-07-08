//--------------------------------------------------------------------------------------
// File: StateIteme.cpp
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "OptionScene.h"
#include"OptionState/StateDrawOptionScene.h"
#include"OptionState/StateOptionScene/StateOptionScene.h"
#include"OptionState/StateSoundOptionScene.h"
using namespace DirectX;

OptionScene::OptionScene(HomeScene::FSM* fsm)
{
	m_pParentFsm = fsm;

}

OptionScene::~OptionScene()
{
}

// 初期化
void OptionScene::Initialize()
{
	CreateDeviceDependentResources();
	m_fsm = std::make_unique<FSM>(this);

	m_StateDrawOptionScene = std::make_unique<StateDrawOptionScene>(m_fsm.get());
	m_StateDrawOptionScene->Initialize();

	m_StateSoundOptionScene = std::make_unique<StateSoundOptionScene>(m_fsm.get());
	m_StateSoundOptionScene->Initialize();


	m_StateOptionScene = std::make_unique<StateOptionScene>(m_fsm.get());
	m_StateOptionScene->Initialize();

	m_fsm->RegisterState(OptionScene::OptionState::DRAW_OPTION_SCENE, m_StateDrawOptionScene.get());
	m_fsm->RegisterState(OptionScene::OptionState::SOUND_OPTION_SCENE, m_StateSoundOptionScene.get());
	m_fsm->RegisterState(OptionScene::OptionState::OPTION_SCENE, m_StateOptionScene.get());

	m_fsm->Start(OptionScene::OptionState::OPTION_SCENE);

}

// 更新
void OptionScene::Update(const float& elapsedTime)
{
	m_fsm->Update(elapsedTime);

}

// 描画
void OptionScene::Render()
{
	m_fsm->Render();

}

// 終了処理
void OptionScene::Finalize()
{
	m_fsm->Finalize();
}

void OptionScene::Enter()
{
	m_fsm->RequestTransition(OptionScene::OptionState::OPTION_SCENE);

}

void OptionScene::Exit()
{
}

void OptionScene::CreateDeviceDependentResources()
{
}
