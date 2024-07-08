#include "pch.h"
#include"WelcomeToTownLetter.h"
#include<random>
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"

#include"../TutorialUI.h"
using namespace DirectX;

const float TIME(2);
WelcomeToTownLetter::WelcomeToTownLetter(TutorialUI* tutorialUI):
	IStateTutorialUI(),
	m_pTutorialUI(tutorialUI)
{
}

void WelcomeToTownLetter::Initialize()
{
	GetTextLetter()->Initialize(
		L"Resources/Textures/WelcomeToTownLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
}

void WelcomeToTownLetter::Update(const float& elapsedTime)
{
	SetTimer(GetTimer() + elapsedTime);
	if (GetTimer() <= TIME)
	{
		GetTextLetter()->Update(elapsedTime);
		return;
	}
	GetTextLetter()->ReduceTransparency(elapsedTime);

	if (GetTimer() >= TIME + TutorialUI::FADE_TIME)
		m_pTutorialUI->SetCurrentState(m_pTutorialUI->GetTutorialUI()[TUTORIAl_UIS::WASDQE_MOVE].get());
}

void WelcomeToTownLetter::Render()
{
	GetTextLetter()->Render();
}

void WelcomeToTownLetter::Finalize()
{
}

void WelcomeToTownLetter::Reset()
{
	SetTimer(0);
}
