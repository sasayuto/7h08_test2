#include "pch.h"
#include"ScoreUpLetter.h"
#include<random>
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"

#include"../TutorialUI.h"
using namespace DirectX;

const float TIME(1);
ScoreUpLetter::ScoreUpLetter(TutorialUI* tutorialUI):
	IStateTutorialUI(),
	m_pTutorialUI(tutorialUI)
{

}

void ScoreUpLetter::Initialize()
{
	GetTextLetter()->Initialize(
		L"Resources/Textures/ScoreUpLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
}

void ScoreUpLetter::Update(const float& elapsedTime)
{
	SetTimer(GetTimer() + elapsedTime);
	if (GetTimer() <= TIME)
	{
		GetTextLetter()->Update(elapsedTime);
		return;
	}
	GetTextLetter()->ReduceTransparency(elapsedTime);

	if (GetTimer() >= TIME + TutorialUI::FADE_TIME)
	{
		m_pTutorialUI->SetCurrentState(m_pTutorialUI->GetTutorialUI()[m_pTutorialUI->GetNiceUis()].get());

		//Žg‚¢I‚í‚Á‚½‚ç‰Šú‰»
		m_pTutorialUI->SetNiceUis(TUTORIAl_UIS::NONE);
	}
}

void ScoreUpLetter::Render()
{
	GetTextLetter()->Render();
}

void ScoreUpLetter::Finalize()
{
}
void ScoreUpLetter::Reset()
{
	SetTimer(0);
}
