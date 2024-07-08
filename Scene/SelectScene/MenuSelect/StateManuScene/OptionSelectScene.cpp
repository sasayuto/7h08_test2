#include "pch.h"
#include "OptionSelectScene.h"
#include"Scene/OperationInstructions/OperationInstructionsScene.h"
#include"Scene/TitleScene.h"
using namespace DirectX;

const float ELAPSED_TIME = 1.0f;

 OptionSelectScene::OptionSelectScene()
{
}

 OptionSelectScene::~OptionSelectScene()
{
}

void OptionSelectScene::Update(const bool& selectFlag)
{
	if (selectFlag)
		GetTitleScene()->ChangeScene<OperationInstructionsScene>();
}

void OptionSelectScene::Render()
{
}

void OptionSelectScene::Finalize()
{
}


