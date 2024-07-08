//--------------------------------------------------------------------------------------
// File: ChangeNoneScene.cpp
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "ChangeNoneScene.h"

using namespace DirectX;

ChangeNoneScene::ChangeNoneScene(StateHomeScene::FSM* fsm)
{
	m_fsm = fsm;
}

ChangeNoneScene::~ChangeNoneScene()
{
}

// 初期化
void ChangeNoneScene::Initialize()
{
	CreateDeviceDependentResources();

}

// 更新
void ChangeNoneScene::Update(const float& elapsedTime)
{
}

// 描画
void ChangeNoneScene::Render()
{
}

// 終了処理
void ChangeNoneScene::Finalize()
{
}

void ChangeNoneScene::Enter()
{
	//文字枠の位置を移動(ぶっ飛ばせー)
	m_fsm->GetOwner()->GetUnderBar()->SetPosition(DirectX::SimpleMath::Vector2(10000,10000));
}

void ChangeNoneScene::Exit()
{
}

void ChangeNoneScene::CreateDeviceDependentResources()
{
}
