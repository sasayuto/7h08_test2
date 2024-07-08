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
		//�i�C�X�̎��Ɏw���V�[�������邩
		if (m_pTutorialUI->GetPraiseUis() == TUTORIAl_UIS::NONE)
		{
			//���ߕ��V�[�����Z�b�g
			m_pTutorialUI->SetCurrentState(m_pTutorialUI->GetTutorialUI()[m_pTutorialUI->GetNiceUis()].get());
			return;
		}
		//�i�C�X�̎��̎w���V�[����
		m_pTutorialUI->SetCurrentState(m_pTutorialUI->GetTutorialUI()[m_pTutorialUI->GetPraiseUis()].get());
		
		//�g���I������珉�������Ă���
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
