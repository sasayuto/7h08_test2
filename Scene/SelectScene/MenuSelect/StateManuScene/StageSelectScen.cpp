#include "pch.h"
#include "StageSelectScen.h"
#include"Scene/StageSelectScene.h"
#include"Scene/TitleScene.h"
using namespace DirectX;

const float ELAPSED_TIME = 1.0f;

 StageSelectScen::StageSelectScen()
{
}

 StageSelectScen::~StageSelectScen()
{
}

void StageSelectScen::Update(const bool& selectFlag)
{
	if (selectFlag)
		GetTitleScene()->ChangeScene<StageSelectScene>();
}

void StageSelectScen::Render()
{
}

void StageSelectScen::Finalize()
{
}


