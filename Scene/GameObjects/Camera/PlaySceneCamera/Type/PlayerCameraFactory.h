#pragma once
#include "../StatePlaySceneCamera.h"
#include "IPlayerCameraFactory.h"

/// <summary>
/// StatePlayerFactoryのクラスを定義する
/// </summary>
class PlayerCameraFactory : public IPlayerCameraFactory
{
public:
	/// <summary>
	/// 通常のカメラを生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <returns>通常のカメラのポインタ</returns>
	static std::unique_ptr<StatePlaySceneCamera> CreateNormalCamera(
		PlaySceneCamera* parent
	);

	/// <summary>
	/// デスのカメラを生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <returns>デスのカメラのポインタ</returns>
	static std::unique_ptr<StatePlaySceneCamera> CreateDeathCamera(
		PlaySceneCamera* parent
	);

};

