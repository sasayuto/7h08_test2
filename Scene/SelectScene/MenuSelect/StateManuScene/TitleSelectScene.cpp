#include "pch.h"
#include "TitleSelectScene.h"
#include"Scene/GameTitle.h"
#include"Scene/TitleScene.h"
using namespace DirectX;

const float ELAPSED_TIME = 1.0f;

TitleSelectScene::TitleSelectScene()
{
}

TitleSelectScene::~TitleSelectScene()
{
}

void TitleSelectScene::Update(const bool& selectFlag)
{
	if (selectFlag)
		GetTitleScene()->ChangeScene<GameTitle>();
}

void TitleSelectScene::Render()
{
}

void TitleSelectScene::Finalize()
{
}


