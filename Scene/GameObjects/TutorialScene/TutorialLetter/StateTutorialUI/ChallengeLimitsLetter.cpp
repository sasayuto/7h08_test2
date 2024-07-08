#include "pch.h"
#include"ChallengeLimitsLetter.h"
#include<random>
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"

#include"../TutorialUI.h"
using namespace DirectX;

const float TIME(2);
ChallengeLimitsLetter::ChallengeLimitsLetter(TutorialUI* tutorialUI):
	IStateTutorialUI(),
	m_pTutorialUI(tutorialUI)
{

}

void ChallengeLimitsLetter::Initialize()
{
	GetTextLetter()->Initialize(
		L"Resources/Textures/challengeLimitsLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
}

void ChallengeLimitsLetter::Update(const float& elapsedTime)
{
	SetTimer(GetTimer() + elapsedTime);
	if (GetTimer() <= TIME)
	{
		GetTextLetter()->Update(elapsedTime);
		return;
	}
	GetTextLetter()->ReduceTransparency(elapsedTime);

	if (GetTimer() >= TIME + TutorialUI::FADE_TIME)
		m_pTutorialUI->SetSceneTransitionFlag(true);
}

void ChallengeLimitsLetter::Render()
{
	GetTextLetter()->Render();
}

void ChallengeLimitsLetter::Finalize()
{
}
void ChallengeLimitsLetter::Reset()
{
	SetTimer(0);
}
