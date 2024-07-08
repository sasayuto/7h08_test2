#include "pch.h"
#include"BenchStreetLightGet.h"
#include<random>
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"

#include"../TutorialUI.h"
using namespace DirectX;

const float DRAWING_TIME(1);

BenchStreetLightGet::BenchStreetLightGet(TutorialUI* tutorialUI):
	IStateTutorialUI(),
	m_pTutorialUI(tutorialUI),
	m_wasdPushFlag(false),
	m_operationUI(nullptr),
	m_brightnessFlag(false)
{
}

void BenchStreetLightGet::Initialize()
{
	m_operationUI = std::make_unique<tito::OperationUI>();

	for (int i = 0; i < 2; i++)
		m_freeUi[i] = std::make_unique<TutorialLetter>();

	GetTextLetter()->Initialize(
		L"Resources/Textures/BenchStreetLightGetLtter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);

	m_operationUI->Create(
		L"Resources/Textures/LeftMouse.png",
		DirectX::SimpleMath::Vector2(-100, 100),
		tito::ANCHOR::BOTTOM_RIGHT,
		tito::POSITION_ANCHOR::BOTTOM_RIGHT);
	m_operationUI->SetBrightness(0);

	m_freeUi[0]->Initialize(
		L"Resources/Textures/RightMouse.png",
		DirectX::SimpleMath::Vector2(-100, 100),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_RIGHT,
		tito::POSITION_ANCHOR::BOTTOM_RIGHT);

	m_freeUi[1]->Initialize(
		L"Resources/Textures/MouseFrame.png",
		DirectX::SimpleMath::Vector2(-100, 100),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_RIGHT,
		tito::POSITION_ANCHOR::BOTTOM_RIGHT);

}

void BenchStreetLightGet::Update(const float& elapsedTime)
{
	//コインゲットミッションをtrueにする
	m_pTutorialUI->SetObjectKillDrawFlag(true);

	if (m_pTutorialUI->GetObjectsKillFlag())
		m_wasdPushFlag = true;
	if (m_wasdPushFlag == false ||
		GetTimer() <= DRAWING_TIME)
	{
		GetTextLetter()->Update(elapsedTime);

		if (m_operationUI->GetBrightness() >= 0.4f) m_brightnessFlag = false;
		if (m_operationUI->GetBrightness() <= 0.0f) m_brightnessFlag = true;
		if (m_brightnessFlag)m_operationUI->SetBrightness(m_operationUI->GetBrightness() + elapsedTime/2);
		else                 m_operationUI->SetBrightness(m_operationUI->GetBrightness() - elapsedTime/2);
		if (m_operationUI->GetTransparency() <= 1.0f)
			m_operationUI->SetTransparency(m_operationUI->GetTransparency() + elapsedTime);

		for (int i = 0; i < 2; i++)
			m_freeUi[i]->Update(elapsedTime);

		if (GetTimer() <= DRAWING_TIME)
			SetTimer(GetTimer() + elapsedTime);
		return;
	}

	//コインゲットミッションをtrueにする
	m_pTutorialUI->SetObjectKillMissionAccomplishedFlag(true);

	SetTimer(GetTimer() + elapsedTime);

	GetTextLetter()->ReduceTransparency(elapsedTime);
	m_operationUI->ReduceTransparency(elapsedTime);
	for (int i = 0; i < 2; i++)
		m_freeUi[i]->ReduceTransparency(elapsedTime);


	if (GetTimer() >= DRAWING_TIME + TutorialUI::FADE_TIME)
	{
		m_pTutorialUI->SetNiceUis(TUTORIAl_UIS::ENEMY_AND_DES_SCORE_LETTER);
		m_pTutorialUI->SetPraiseUis(TUTORIAl_UIS::SCORE_UP_LETTER);
		m_pTutorialUI->SetCurrentState(m_pTutorialUI->GetTutorialUI()[TUTORIAl_UIS::NICE_LETTER].get());
	}
}
void BenchStreetLightGet::Render()
{
	GetTextLetter()->Render();
	m_operationUI->Render();
	for (int i = 0; i < 2; i++)
		m_freeUi[i]->Render();

}

void BenchStreetLightGet::Finalize()
{
}

void BenchStreetLightGet::Reset()
{
	SetTimer(0);
	m_wasdPushFlag = false;
}
