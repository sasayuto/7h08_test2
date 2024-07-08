#include "pch.h"
#include"TutorialLetters.h"
#include<random>
using namespace DirectX;

const float TutorialLetters::FADE_TIME(1);

TutorialLetters::TutorialLetters() :
	m_timer(0),
	m_objectsKillFlag(false),
	m_coinGetFlag(false),
	m_sceneTransitionFlag(false),
	m_adjustedTime(0)
{
}

TutorialLetters::~TutorialLetters()
{

}

void TutorialLetters::Initialize()
{
	m_challengeLimitsLetter = std::make_unique<TutorialLetter>();
	m_CoinGetLtter = std::make_unique<TutorialLetter>();
	m_WelcomeToTownLetter = std::make_unique<TutorialLetter>();
	m_EnemyAndDesScoreLetter = std::make_unique<TutorialLetter>();
	m_niceLetter = std::make_unique<TutorialLetter>();
	m_niceLetter_02 = std::make_unique<TutorialLetter>();
	m_ScoreUpLetter = std::make_unique<TutorialLetter>();
	m_ScoreUpLetter_02 = std::make_unique<TutorialLetter>();
	m_Time3minutesLetter = std::make_unique<TutorialLetter>();
	m_BenchStreetLightGetLtter = std::make_unique<TutorialLetter>();
	m_operationUI[0] = std::make_unique<tito::OperationUI>();

	m_operationUI[0]->Create(
		L"Resources/Textures/WkeyLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		tito::ANCHOR::MIDDLE_CENTER,
		tito::POSITION_ANCHOR::MIDDLE_CENTER);
	m_WelcomeToTownLetter->Initialize(
		L"Resources/Textures/WelcomeToTownLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
	m_CoinGetLtter->Initialize(
		L"Resources/Textures/CoinGetLtter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
	m_challengeLimitsLetter->Initialize(
		L"Resources/Textures/challengeLimitsLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
	m_EnemyAndDesScoreLetter->Initialize(
		L"Resources/Textures/EnemyAndDesScoreLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
	m_niceLetter->Initialize(
		L"Resources/Textures/niceLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
	m_ScoreUpLetter->Initialize(
		L"Resources/Textures/ScoreUpLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
	m_niceLetter_02->Initialize(
		L"Resources/Textures/niceLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
	m_ScoreUpLetter_02->Initialize(
		L"Resources/Textures/ScoreUpLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
	m_Time3minutesLetter->Initialize(
		L"Resources/Textures/Time3minutesLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
	m_BenchStreetLightGetLtter->Initialize(
		L"Resources/Textures/BenchStreetLightGetLtter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
}

void TutorialLetters::Update(const float& elapsedTime)
{
	//前フレーム時間
	float previousTimer = m_timer;
	m_timer += elapsedTime;
	m_adjustedTime = 0;

	if (m_timer > m_adjustedTime && m_timer <= m_adjustedTime + 3.0f)
	{
		m_WelcomeToTownLetter->Update(elapsedTime);
		m_operationUI[0]->Update(elapsedTime);
	}
	else
	{
		m_WelcomeToTownLetter->ReduceTransparency(elapsedTime);
		m_operationUI[0]->ReduceTransparency(elapsedTime);
	}
	m_adjustedTime += 3.0f + FADE_TIME;
	if (m_timer > m_adjustedTime && m_timer <= m_adjustedTime + 0.1f)
	{
		m_CoinGetLtter->Update(elapsedTime);
		//コインをとるまで時間を進めない
		if (!m_coinGetFlag)
			m_timer = previousTimer;
	}
	else
		m_CoinGetLtter->ReduceTransparency(elapsedTime);

	m_adjustedTime += 0.1f + FADE_TIME;

	if (m_timer > m_adjustedTime && m_timer <= m_adjustedTime + 0.9f)
		m_niceLetter->Update(elapsedTime);
	else
		m_niceLetter->ReduceTransparency(elapsedTime);

	m_adjustedTime += 0.9f + FADE_TIME;

	if (m_timer > m_adjustedTime && m_timer <= m_adjustedTime + 1.0f)
		m_ScoreUpLetter->Update(elapsedTime);
	else
		m_ScoreUpLetter->ReduceTransparency(elapsedTime);

	m_adjustedTime += 1.0f + FADE_TIME;

	if (m_timer > m_adjustedTime && m_timer <= m_adjustedTime + 1.0f)
	{
		m_BenchStreetLightGetLtter->Update(elapsedTime);
		//コインをとるまで時間を進めない
		if (!m_objectsKillFlag)
			m_timer = previousTimer;
	}
	else
		m_BenchStreetLightGetLtter->ReduceTransparency(elapsedTime);

	m_adjustedTime += 1.0f + FADE_TIME;

	if (m_timer > m_adjustedTime && m_timer <= m_adjustedTime + 1.0f)
		m_niceLetter_02->Update(elapsedTime);
	else
		m_niceLetter_02->ReduceTransparency(elapsedTime);

	m_adjustedTime += 1.0f + FADE_TIME;

	if (m_timer > m_adjustedTime && m_timer <= m_adjustedTime + 1.0f)
		m_ScoreUpLetter_02->Update(elapsedTime);
	else
		m_ScoreUpLetter_02->ReduceTransparency(elapsedTime);

	m_adjustedTime += 1.0f + FADE_TIME;

	if (m_timer > m_adjustedTime && m_timer <= m_adjustedTime + 2.0f)
		m_EnemyAndDesScoreLetter->Update(elapsedTime);
	else
		m_EnemyAndDesScoreLetter->ReduceTransparency(elapsedTime);

	m_adjustedTime += 2.0f + FADE_TIME;

	if (m_timer > m_adjustedTime && m_timer <= m_adjustedTime + 2.0f)
		m_Time3minutesLetter->Update(elapsedTime);
	else
		m_Time3minutesLetter->ReduceTransparency(elapsedTime);

	m_adjustedTime += 2.0f + FADE_TIME;

	if (m_timer > m_adjustedTime && m_timer <= m_adjustedTime + 2.0f)
		m_challengeLimitsLetter->Update(elapsedTime);
	else
		m_challengeLimitsLetter->ReduceTransparency(elapsedTime);

	m_adjustedTime += 2.0f + FADE_TIME;

	if (m_timer > 23)
		m_sceneTransitionFlag = true;
}

void TutorialLetters::Render()
{
	m_operationUI[0]->Render();
	m_WelcomeToTownLetter->Render();
	m_CoinGetLtter->Render();
	m_niceLetter->Render();
	m_niceLetter_02->Render();
	m_challengeLimitsLetter->Render();
	m_Time3minutesLetter->Render();
	m_ScoreUpLetter_02->Render();
	m_ScoreUpLetter->Render();
	m_BenchStreetLightGetLtter->Render();
	m_niceLetter->Render();
	m_EnemyAndDesScoreLetter->Render();
}

void TutorialLetters::Finalize()
{
}
