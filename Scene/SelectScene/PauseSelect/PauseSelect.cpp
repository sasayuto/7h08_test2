#include "pch.h"
#include "PauseSelect.h"
using namespace DirectX;

#include"StatePauseScene/PauseSelectStart.h"
#include"StatePauseScene/PauseStageSelectScen.h"
#include"StatePauseScene/StatePauseScene.h"
PauseSelect::PauseSelect():
	m_selectNum(0),
	m_gameStop(false)
{
}

PauseSelect::~PauseSelect()
{
}

void PauseSelect::Initialize(PlayScene* playScene)
{
	CreateDeviceDependentResources();
	for (int i = 0; i < Pause::PAUSE_COUNT; i++)
	{
		m_object[i]->Initialize(
			DirectX::SimpleMath::Vector2(0, static_cast<float>(-(i * WIDTH)))
			, DirectX::SimpleMath::Vector2(1, 1)
			, tito::ANCHOR::MIDDLE_CENTER
			, tito::POSITION_ANCHOR::MIDDLE_CENTER
		);
	}

	m_underBar->Initialize(
		DirectX::SimpleMath::Vector2(0, 0)
		, DirectX::SimpleMath::Vector2(1, 1)
		, tito::ANCHOR::MIDDLE_CENTER
		, tito::POSITION_ANCHOR::MIDDLE_CENTER
	);

	m_select[Pause::STAGE_SELECT]->Initialize(this, playScene);
	m_select[Pause::TITLE]->Initialize(this, playScene);

	m_pCurrentState = m_select[Pause::STAGE_SELECT].get();
	m_selectNum = static_cast<int>(Pause::STAGE_SELECT);

}

void PauseSelect::Update(const bool& selectFlag, const bool& animationFlag)
{

	if (!animationFlag)
	{
		//選択
		if (KeyboardTracker::GetInstance()->Up()) m_selectNum--;
		if (KeyboardTracker::GetInstance()->Down())m_selectNum++;

		//惑星の外に出たら調整
		if (m_selectNum < 0) m_selectNum++;
		if (m_selectNum >= Pause::PAUSE_COUNT) m_selectNum--;

		m_underBar->Update(m_selectNum);

		//更新前のステージ番号
		m_pCurrentState = m_select[m_selectNum].get();
	}
	//ステージの更新
	m_pCurrentState->Update(selectFlag, animationFlag);


}

void PauseSelect::Render()
{
	for (int i = 0; i < Pause::PAUSE_COUNT; i++)
	{
		m_object[i]->Render();
	}
	m_underBar->Render();

	m_pCurrentState->Render();
}

void PauseSelect::Finalize()
{
	m_pCurrentState->Finalize();
}

void PauseSelect::CreateDeviceDependentResources()
{	
	//惑星を生成
	m_object[Pause::STAGE_SELECT] = std::make_unique<StageSelectLetter>();
	m_object[Pause::TITLE] = std::make_unique<StageSelectLetter>();

	m_object[Pause::STAGE_SELECT]->SetPath(L"Resources/Textures/StageSelectLetter.png");
	m_object[Pause::TITLE]->SetPath(L"Resources/Textures/TaitoruheLetter.png");

	m_select[Pause::STAGE_SELECT] = std::make_unique<PauseStageSelectScen>();
	m_select[Pause::TITLE] = std::make_unique<PauseSelectStart>();

	
	m_underBar = std::make_unique<UnderBar>();
}

