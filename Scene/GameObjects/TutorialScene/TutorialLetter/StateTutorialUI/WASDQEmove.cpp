#include "pch.h"
#include"WASDQEmove.h"
#include<random>
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"

#include"../TutorialUI.h"
using namespace DirectX;

const float DRAWING_TIME(1);

WASDQEmove::WASDQEmove(TutorialUI* tutorialUI):
	IStateTutorialUI(),
	m_pTutorialUI(tutorialUI),
	m_wasdPushFlag(false),
	m_operationUI{}
{
}

void WASDQEmove::Initialize()
{
	for (int i = 0; i < 4; i++)
	{
		m_operationUI[i] = std::make_unique<tito::OperationUI>();

	}

	GetTextLetter()->Initialize(
		L"Resources/Textures/WASDQEmove.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);

	m_operationUI[0]->Create(
		L"Resources/Textures/WkeyLetter.png",
		DirectX::SimpleMath::Vector2(-200, 200),
		tito::ANCHOR::BOTTOM_RIGHT,
		tito::POSITION_ANCHOR::BOTTOM_RIGHT);
	m_operationUI[0]->SetBrightness(0.5f);
	m_operationUI[1]->Create(
		L"Resources/Textures/AkeyLetter.png",
		DirectX::SimpleMath::Vector2(-300, 100),
		tito::ANCHOR::BOTTOM_RIGHT,
		tito::POSITION_ANCHOR::BOTTOM_RIGHT);
	m_operationUI[1]->SetBrightness(0.666f);
	m_operationUI[2]->Create(
		L"Resources/Textures/SkeyLetter.png",
		DirectX::SimpleMath::Vector2(-200, 100),
		tito::ANCHOR::BOTTOM_RIGHT,
		tito::POSITION_ANCHOR::BOTTOM_RIGHT);
	m_operationUI[2]->SetBrightness(0.833f);
	m_operationUI[3]->Create(
		L"Resources/Textures/DkeyLetter.png",
		DirectX::SimpleMath::Vector2(-100, 100),
		tito::ANCHOR::BOTTOM_RIGHT,
		tito::POSITION_ANCHOR::BOTTOM_RIGHT);
	m_operationUI[3]->SetBrightness(1.0f);

}

void WASDQEmove::Update(const float& elapsedTime)
{
	//コインゲットミッションを開始にする
	m_pTutorialUI->SetTaskDrawFlag(true);

	//キーが押されたか
	if (KeyboardSingleton::GetInstance()->Up())			m_wasdPushFlag = true;
	if (KeyboardSingleton::GetInstance()->Down())		m_wasdPushFlag = true;
	if (KeyboardSingleton::GetInstance()->Left())		m_wasdPushFlag = true;
	if (KeyboardSingleton::GetInstance()->Right())		m_wasdPushFlag = true;
	if (KeyboardSingleton::GetInstance()->LeftRool())	m_wasdPushFlag = true;
	if (KeyboardSingleton::GetInstance()->RightRool())	m_wasdPushFlag = true;

	//コインゲットミッションをtrueにする
	m_pTutorialUI->SetWASDDrawFlag(true);

	if (m_wasdPushFlag == false ||
		GetTimer() <= DRAWING_TIME)
	{
		GetTextLetter()->Update(elapsedTime);
		for (int i = 0; i < 4; i++)
			m_operationUI[i]->Update(elapsedTime);
	
		if (GetTimer() <= DRAWING_TIME)
			SetTimer(GetTimer() + elapsedTime);
		return;
	}

	//コインゲットミッションをtrueにする
	m_pTutorialUI->SetWASDMissionAccomplishedFlag(true);

	SetTimer(GetTimer() + elapsedTime);

	GetTextLetter()->ReduceTransparency(elapsedTime);
	for (int i = 0; i < 4; i++)
		m_operationUI[i]->ReduceTransparency(elapsedTime);

	if (GetTimer() >= DRAWING_TIME + TutorialUI::FADE_TIME)
	{
		m_pTutorialUI->SetNiceUis(TUTORIAl_UIS::SHIFT_STOP);
		m_pTutorialUI->SetCurrentState(m_pTutorialUI->GetTutorialUI()[TUTORIAl_UIS::NICE_LETTER].get());
	}
}

void WASDQEmove::Render()
{
	GetTextLetter()->Render();
	for (int i = 0; i < 4; i++)
		m_operationUI[i]->Render();
}

void WASDQEmove::Finalize()
{
}

void WASDQEmove::Reset()
{
	SetTimer(0);
	m_wasdPushFlag = false;
}
