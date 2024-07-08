#include "pch.h"
#include"EnemyAndDesScoreLetter.h"
#include<random>
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"

#include"../TutorialUI.h"
using namespace DirectX;

const float TIME(2);
EnemyAndDesScoreLetter::EnemyAndDesScoreLetter(TutorialUI* tutorialUI):
	IStateTutorialUI(),
	m_pTutorialUI(tutorialUI)
{

}

void EnemyAndDesScoreLetter::Initialize()
{
	GetTextLetter()->Initialize(
		L"Resources/Textures/EnemyAndDesScoreLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
}

void EnemyAndDesScoreLetter::Update(const float& elapsedTime)
{
	SetTimer(GetTimer() + elapsedTime);
	if (GetTimer() <= TIME)
	{
		GetTextLetter()->Update(elapsedTime);
		return;
	}
	GetTextLetter()->ReduceTransparency(elapsedTime);

	if (GetTimer() >= TIME + TutorialUI::FADE_TIME)
		m_pTutorialUI->SetCurrentState(m_pTutorialUI->GetTutorialUI()[TUTORIAl_UIS::RECOVERY_ITEMS_GET].get());
}

void EnemyAndDesScoreLetter::Render()
{
	GetTextLetter()->Render();
}

void EnemyAndDesScoreLetter::Finalize()
{
}
void EnemyAndDesScoreLetter::Reset()
{
	SetTimer(0);
}
