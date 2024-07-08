#include "pch.h"
#include"ScoreCalculation.h"
using namespace DirectX;

const int KINDS_SCORE_POS_X(300);
const int KINDS_SCORE_POS_Y(130);
const int KINDS_SCORE_WIDTH(250);
const int KINDS_SCORE_HEIGHT(35);
const DirectX::SimpleMath::Vector2 SCALE(0.3f);
ScoreCalculation::ScoreCalculation() :
	m_scoreCounts{},
	m_score(0),
	m_timer(0),
	m_sceneTransitionFlag(false)
{
	for (int i = 0; i < ScoreCount::KindsScore::COUNT; i++)
	{
		m_scoreCounts[i] = std::make_unique<ScoreCount>( static_cast<ScoreCount::KindsScore>(i), 0);
	}
	//totalスコアのテクスチャ
	m_totalScoreTex = std::make_unique<TimerTex>();

}

ScoreCalculation::~ScoreCalculation()
{
	
}

void ScoreCalculation::Initialize()
{
	m_sceneTransitionFlag = false;
	m_timer = 0;
	//スコアを０にする(念のため)
	m_score = 0;

	for (int i = 0; i < ScoreCount::KindsScore::COUNT; i++)
	{

		std::unique_ptr<tito::UserInterface> UI = std::make_unique<tito::UserInterface>();
		UI->Create(
			L"Resources/Textures/resultscoreLetter.png",
			DirectX::SimpleMath::Vector2(KINDS_SCORE_POS_X-130, -(KINDS_SCORE_POS_Y + i * KINDS_SCORE_HEIGHT)),
			DirectX::SimpleMath::Vector2(1, 1),
			tito::ANCHOR::TOP_RIGHT,
			tito::POSITION_ANCHOR::TOP_LEFT
		);
		m_ResultBaseLetter.push_back(std::move(UI));

		std::unique_ptr<TimerTex> countTex = std::make_unique<TimerTex>();
		countTex->Initialize(
			DirectX::SimpleMath::Vector2(KINDS_SCORE_POS_X, KINDS_SCORE_POS_Y +i* KINDS_SCORE_HEIGHT),
			SCALE,
			static_cast<float>(m_scoreCounts[i]->GetCount()),
			tito::ANCHOR::TOP_CENTER
		);

		m_kindsCountTex.push_back(std::move(countTex));

		std::unique_ptr<TimerTex> OneScoreTex = std::make_unique<TimerTex>();
		OneScoreTex->Initialize(
			DirectX::SimpleMath::Vector2(KINDS_SCORE_POS_X + KINDS_SCORE_WIDTH, KINDS_SCORE_POS_Y + i * KINDS_SCORE_HEIGHT),
			SCALE,
			static_cast<float>(m_scoreCounts[i]->GetScore()),
			tito::ANCHOR::TOP_CENTER
		);
		m_kindsOneScoreTex.push_back(std::move(OneScoreTex));

		std::unique_ptr<TimerTex> ScoreTex = std::make_unique<TimerTex>();
		ScoreTex->Initialize(
			DirectX::SimpleMath::Vector2(KINDS_SCORE_POS_X + KINDS_SCORE_WIDTH * 2 , KINDS_SCORE_POS_Y + i * KINDS_SCORE_HEIGHT),
			SCALE,
			static_cast<float>(m_scoreCounts[i]->GetCount() * m_scoreCounts[i]->GetScore()),
			tito::ANCHOR::TOP_CENTER
		);
		m_kindsScoreTex.push_back(std::move(ScoreTex));

		std::unique_ptr<FreeUi> asterisk = std::make_unique<FreeUi>();
		asterisk->Initialize(
			L"Resources/Textures/AsteriskLetter.png"
			, DirectX::SimpleMath::Vector2(KINDS_SCORE_POS_X, -KINDS_SCORE_POS_Y -i * KINDS_SCORE_HEIGHT+5)
			, DirectX::SimpleMath::Vector2(1, 1)* SCALE*2
			, tito::ANCHOR::TOP_CENTER
			, tito::POSITION_ANCHOR::TOP_LEFT
		);
		m_asterisk.push_back(std::move(asterisk));

		std::unique_ptr<FreeUi> equal = std::make_unique<FreeUi>();
		equal->Initialize(
			L"Resources/Textures/EqualLetter.png"
			, DirectX::SimpleMath::Vector2(KINDS_SCORE_POS_X + 250, -KINDS_SCORE_POS_Y -i * KINDS_SCORE_HEIGHT +5)
			, DirectX::SimpleMath::Vector2(1, 1)*SCALE * 2
			, tito::ANCHOR::TOP_CENTER
			, tito::POSITION_ANCHOR::TOP_LEFT
		);
		m_equal.push_back(std::move(equal));

		//totalのスコアを計算
		m_score += m_scoreCounts[i]->GetCount() * m_scoreCounts[i]->GetScore();

	} 

	m_totalScoreTex->Initialize(
		DirectX::SimpleMath::Vector2(850, 500),
		DirectX::SimpleMath::Vector2(0.8f,1),
		static_cast<float>(m_score),
		tito::ANCHOR::TOP_CENTER
	);


	std::unique_ptr<tito::UserInterface> UI = std::make_unique<tito::UserInterface>();
	UI->Create(
		L"Resources/Textures/resultscoreLetter.png",
		DirectX::SimpleMath::Vector2(200, -500),
		DirectX::SimpleMath::Vector2(1, 1),
		tito::ANCHOR::TOP_CENTER,
		tito::POSITION_ANCHOR::TOP_LEFT
	);
	enum KindsScore
	{
		ENEMY,
		TURRET,
		BENCH,
		STREET_LIGHT,
		COIN,
		FENCE,

		COUNT
	};
	m_ResultBaseLetter.push_back(std::move(UI));
	m_ResultBaseLetter[0]->LoadTexture(L"Resources/Textures/EnemyLetter.png");
	m_ResultBaseLetter[1]->LoadTexture(L"Resources/Textures/HouseLetter.png");
	m_ResultBaseLetter[2]->LoadTexture(L"Resources/Textures/BentiLetter.png");
	m_ResultBaseLetter[3]->LoadTexture(L"Resources/Textures/SteLetter.png");
	m_ResultBaseLetter[4]->LoadTexture(L"Resources/Textures/CoinLetter.png");
	m_ResultBaseLetter[5]->LoadTexture(L"Resources/Textures/fenceLetter.png");

}

void ScoreCalculation::Update(const float& elapsedTime)
{	
	m_timer += elapsedTime;
}

void ScoreCalculation::PlaySceneUpdate()
{
	m_score = 0;
	for (int i = 0; i < ScoreCount::KindsScore::COUNT; i++)
	{
		//totalのスコアを計算
		m_score += m_scoreCounts[i]->GetCount() * m_scoreCounts[i]->GetScore();
	}
}

void ScoreCalculation::Render()
{
	int MaxTime = 0;
	for (int i = 0; i < m_kindsScoreTex.size(); i++)
	{
		if (m_timer >= 0.5f + (i + 1) * 2.0f)
			m_ResultBaseLetter[i]->Render();
		if (m_timer >= 1.0f + (i + 1) * 2.0f)
			m_kindsCountTex[i]->Render();
		if (m_timer >= 1.5f + (i + 1) * 2.0f)
			m_kindsOneScoreTex[i]->Render();
		if (m_timer >= 2.0f + (i + 1) * 2.0f)
			m_kindsScoreTex[i]->Render();
		
		MaxTime = static_cast<int>(2.0f + (i + 1) * 2.0f);
		m_asterisk[i]->Render();
		m_equal[i]->Render();
	}
	if (m_timer >= MaxTime + 1.f)
	{
		m_ResultBaseLetter[6]->Render();
	}
	if (m_timer >= MaxTime + 2.0f)
	{
		m_sceneTransitionFlag = true;
		m_totalScoreTex->Render();
	}
}

void ScoreCalculation::Finalize()
{
	m_score = 0;
	m_kindsCountTex.clear();
	m_kindsOneScoreTex.clear();
	m_kindsScoreTex.clear();
	m_asterisk.clear();
	m_equal.clear();
	m_totalScoreTex->Finalize();
	for (int i = 0; i < ScoreCount::KindsScore::COUNT; i++)
	{
		m_scoreCounts[i]->SetCount(0);
	}
}


