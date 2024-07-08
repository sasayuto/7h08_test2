#include "pch.h"
#include "StateMenuScene.h"

StateMenuScene::StateMenuScene():
	m_pMenuSelect(nullptr),
	m_pTitleScene(nullptr)
{
}

void StateMenuScene::Initialize(MenuSelect* menuSelect, TitleScene* titleScene)
{
	m_pMenuSelect = menuSelect;
	m_pTitleScene = titleScene;
}

