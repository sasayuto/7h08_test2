#include "pch.h"
#include "ISelectPlayScene.h"

ISelectPlayScene::ISelectPlayScene():
	m_pStageSelect(nullptr),
	m_pStageSelectScene(nullptr)
{
}

void ISelectPlayScene::Initialize(StageSelect* stageSelect, StageSelectScene* stageSelectScene)
{
	m_SelectFlag = false;
	m_pStageSelect = stageSelect;
	m_pStageSelectScene = stageSelectScene;
}
