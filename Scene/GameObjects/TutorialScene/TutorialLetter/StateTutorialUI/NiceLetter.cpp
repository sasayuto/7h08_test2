#include "pch.h"
#include"NiceLetter.h"
#include<random>
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"

#include"../TutorialUI.h"
using namespace DirectX;

const float TIME(1);
NiceLetter::NiceLetter(TutorialUI* tutorialUI):
	IStateTutorialUI(),
	m_pTutorialUI(tutorialUI)
{

}

void NiceLetter::Initialize()
{
	GetTextLetter()->Initialize(
		L"Resources/Textures/NiceLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
}

void NiceLetter::Update(const float& elapsedTime)
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
		//ナイスの次に指示シーンがあるか
		if (m_pTutorialUI->GetPraiseUis() == TUTORIAl_UIS::NONE)
		{
			//命令文シーンをセット
			m_pTutorialUI->SetCurrentState(m_pTutorialUI->GetTutorialUI()[m_pTutorialUI->GetNiceUis()].get());
			return;
		}
		//ナイスの次の指示シーンへ
		m_pTutorialUI->SetCurrentState(m_pTutorialUI->GetTutorialUI()[m_pTutorialUI->GetPraiseUis()].get());
		
		//使い終わったら初期化しておく
		m_pTutorialUI->SetPraiseUis(TUTORIAl_UIS::NONE);
	}

}

void NiceLetter::Render()
{
	GetTextLetter()->Render();
}

void NiceLetter::Finalize()
{
}
void NiceLetter::Reset()
{
	SetTimer(0);
}
