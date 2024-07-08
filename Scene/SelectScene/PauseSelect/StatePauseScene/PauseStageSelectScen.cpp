#include "pch.h"
#include "PauseStageSelectScen.h"
#include"Scene/StageSelectScene.h"
#include"Scene/PlayScene/PlayScene.h"
using namespace DirectX;

const float ELAPSED_TIME = 1.0f;

 PauseStageSelectScen::PauseStageSelectScen()
{
}

 PauseStageSelectScen::~PauseStageSelectScen()
{
}

void PauseStageSelectScen::Update(const bool& selectFlag,  const bool& animationFlag)
{
	if (selectFlag)
		GetPlayScene()->ChangeScene<StageSelectScene>();
}

void PauseStageSelectScen::Render()
{
}

void PauseStageSelectScen::Finalize()
{
}


