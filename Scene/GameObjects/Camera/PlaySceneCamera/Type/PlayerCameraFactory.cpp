#include "pch.h"

#include"PlayerCameraFactory.h"

#include"NormalCamera.h"
#include"DeathCamera.h"
std::unique_ptr<StatePlaySceneCamera> PlayerCameraFactory::CreateNormalCamera(PlaySceneCamera* parent)
{
	//通常のカメラのインスタンスを生成する
	std::unique_ptr<StatePlaySceneCamera> normalCamera = std::make_unique<NormalCamera>();

	//初期化する
	normalCamera->Initialize(parent);

	//通常のカメラのインスタンスを返す
	return move(normalCamera);
}

std::unique_ptr<StatePlaySceneCamera> PlayerCameraFactory::CreateDeathCamera(PlaySceneCamera* parent)
{
	//デスのカメラのインスタンスを生成する
	std::unique_ptr<StatePlaySceneCamera> deathCamera = std::make_unique<DeathCamera>();

	//初期化する
	deathCamera->Initialize(parent);

	//デスのカメラのインスタンスを返す
	return move(deathCamera);
}
