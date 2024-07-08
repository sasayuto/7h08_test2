#include "pch.h"
#include "StatePauseScene.h"

StatePauseScene::StatePauseScene():
	m_pPauseSelect(nullptr),
	m_pPlayScene(nullptr)
{
}

void StatePauseScene::Initialize(PauseSelect* menuSelect, PlayScene* titleScene)
{
	m_pPauseSelect = menuSelect;
	m_pPlayScene = titleScene;
}

