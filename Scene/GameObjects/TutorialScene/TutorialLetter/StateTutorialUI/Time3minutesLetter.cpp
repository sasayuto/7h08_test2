#include "pch.h"
#include"Time3minutesLetter.h"
#include<random>
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"

#include"../TutorialUI.h"
using namespace DirectX;

const float TIME(2);
Time3minutesLetter::Time3minutesLetter(TutorialUI* tutorialUI):
	IStateTutorialUI(),
	m_pTutorialUI(tutorialUI)
{

}

void Time3minutesLetter::Initialize()
{
	GetTextLetter()->Initialize(
		L"Resources/Textures/Time3minutesLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
}

void Time3minutesLetter::Update(const float& elapsedTime)
{
	SetTimer(GetTimer() + elapsedTime);
	if (GetTimer() <= TIME)
	{
		GetTextLetter()->Update(elapsedTime);
		return;
	}
	GetTextLetter()->ReduceTransparency(elapsedTime);

	if (GetTimer() >= TIME + TutorialUI::FADE_TIME)
		m_pTutorialUI->SetCurrentState(m_pTutorialUI->GetTutorialUI()[TUTORIAl_UIS::CHALLENGE_LIMITS_LETTER].get());
}

void Time3minutesLetter::Render()
{
	GetTextLetter()->Render();
}

void Time3minutesLetter::Finalize()
{
}
void Time3minutesLetter::Reset()
{
	SetTimer(0);
}
