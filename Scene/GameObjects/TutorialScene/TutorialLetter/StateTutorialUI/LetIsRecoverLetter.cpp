#include "pch.h"
#include"LetIsRecoverLetter.h"
#include<random>
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"

#include"../TutorialUI.h"
using namespace DirectX;

const float TIME(1.5f);
LetIsRecoverLetter::LetIsRecoverLetter(TutorialUI* tutorialUI):
	IStateTutorialUI(),
	m_pTutorialUI(tutorialUI)
{

}

void LetIsRecoverLetter::Initialize()
{
	GetTextLetter()->Initialize(
		L"Resources/Textures/LetIsRecoverLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
}

void LetIsRecoverLetter::Update(const float& elapsedTime)
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

void LetIsRecoverLetter::Render()
{
	GetTextLetter()->Render();
}

void LetIsRecoverLetter::Finalize()
{
}
void LetIsRecoverLetter::Reset()
{
	SetTimer(0);
}
