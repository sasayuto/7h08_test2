#include "pch.h"
#include "OperationInstructionsScene.h"
#include "../TitleScene.h"
using namespace DirectX;

OperationInstructionsScene::OperationInstructionsScene() :
	m_transitionState(nullptr),
	m_operationInstructionsUI(nullptr)
{

}

OperationInstructionsScene::~OperationInstructionsScene()
{
}

void OperationInstructionsScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
	m_returnLetter->Initialize();
	m_transitionState->Initialize();
	m_operationInstructionsUI->Initialize();
}

void OperationInstructionsScene::Update(float elapsedTime)
{
	//キー入力
	auto keyboardTraker = KeyboardTracker::GetInstance()->GetKeyboardTracker();

	m_operationInstructionsUI->Update();
	m_transitionState->Update(elapsedTime);

	//タブが押されたら前の画面に戻る
	if (keyboardTraker.pressed.Tab)
		m_transitionState->SetAnimationReturnFlag(true);

	if (m_transitionState->GetStageReturnSelct())
		ChangeScene<TitleScene>();
	UNREFERENCED_PARAMETER(elapsedTime);
}

void OperationInstructionsScene::Render()
{
	m_operationInstructionsUI->Render();
	m_returnLetter->Render();

	m_transitionState->Render();
}

void OperationInstructionsScene::Finalize()
{
}

void OperationInstructionsScene::CreateDeviceDependentResources()
{	
	m_returnLetter = std::make_unique<ReturnLetter>();
	//背景のインスタンスを生成
	m_transitionState = std::make_unique<TransitionState>();
	//背景のインスタンスを生成
	m_operationInstructionsUI = std::make_unique<OperationInstructionsUI>();
}

void OperationInstructionsScene::CreateWindowSizeDependentResources()
{
}

void OperationInstructionsScene::OnDeviceLost()
{
	Finalize();
}
