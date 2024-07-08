#include "pch.h"
#include "PauseSelectStart.h"
#include"Scene/GameTitle.h"
#include"Scene/PlayScene/PlayScene.h"
#include"../PauseSelect.h"
using namespace DirectX;

const float ELAPSED_TIME = 1.0f;

PauseSelectStart::PauseSelectStart()
{
}

PauseSelectStart::~PauseSelectStart()
{
}

void PauseSelectStart::Update(const bool& selectFlag,  const bool& animationFlag)
{
	if (animationFlag)
		GetPauseSelect()->SetGameStop(false);
}

void PauseSelectStart::Render()
{
}

void PauseSelectStart::Finalize()
{
}


