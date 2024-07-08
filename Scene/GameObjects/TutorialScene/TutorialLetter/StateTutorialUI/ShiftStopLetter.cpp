#include "pch.h"
#include"ShiftStopLetter.h"
#include<random>
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"

#include"../TutorialUI.h"
using namespace DirectX;

const float DRAWING_TIME(1);

ShiftStopLetter::ShiftStopLetter(TutorialUI* tutorialUI):
	IStateTutorialUI(),
	m_pTutorialUI(tutorialUI),
	m_wasdPushFlag(false),
	m_operationUI(nullptr)
{
}

void ShiftStopLetter::Initialize()
{
	m_operationUI = std::make_unique<tito::OperationUI>();

	GetTextLetter()->Initialize(
		L"Resources/Textures/ShiftStopLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);

	m_operationUI->Create(
		L"Resources/Textures/Shift.png",
		DirectX::SimpleMath::Vector2(-120, 150),
		tito::ANCHOR::BOTTOM_RIGHT,
		tito::POSITION_ANCHOR::BOTTOM_RIGHT);

}

void ShiftStopLetter::Update(const float& elapsedTime)
{

	//コインゲットミッションをtrueにする
	m_pTutorialUI->SetShiftDrawFlag(true);

	if (KeyboardSingleton::GetInstance()->GetKeyboardState().LeftShift)	m_wasdPushFlag = true;

	if (m_wasdPushFlag == false ||
		GetTimer() <= DRAWING_TIME)
	{
		GetTextLetter()->Update(elapsedTime);
		m_operationUI->Update(elapsedTime);
		if (GetTimer() <= DRAWING_TIME)
			SetTimer(GetTimer() + elapsedTime);
		return;
	}
	//コインゲットミッションをtrueにする
	m_pTutorialUI->SetShiftMissionAccomplishedFlag(true);

	SetTimer(GetTimer() + elapsedTime);

	GetTextLetter()->ReduceTransparency(elapsedTime);
	m_operationUI->ReduceTransparency(elapsedTime);

	if (GetTimer() >= DRAWING_TIME + TutorialUI::FADE_TIME)
	{
		m_pTutorialUI->SetNiceUis(TUTORIAl_UIS::COIN_GET);
		m_pTutorialUI->SetCurrentState(m_pTutorialUI->GetTutorialUI()[TUTORIAl_UIS::NICE_LETTER].get());
	}
}

void ShiftStopLetter::Render()
{
	GetTextLetter()->Render();
	m_operationUI->Render();
}

void ShiftStopLetter::Finalize()
{
}

void ShiftStopLetter::Reset()
{
	SetTimer(0);
	m_wasdPushFlag = false;
}
