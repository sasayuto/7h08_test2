#pragma 
#include <combaseapi.h>

class StatePlaySceneCamera;
class PlaySceneCamera;
/// <summary>
/// IStatePlayerFactoryインターフェイスのクラスを定義する
/// </summary>
interface IPlayerCameraFactory
{
	/// <summary>
	/// 通常のカメラを生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <returns>通常のカメラのポインタ</returns>
	virtual std::unique_ptr<StatePlaySceneCamera> CreateNormalCamera(
		const PlaySceneCamera* parent
	) = 0;

	/// <summary>
	/// デスのカメラを生成
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <returns>デスのカメラのポインタ</returns>
	virtual std::unique_ptr<StatePlaySceneCamera> CreateDeathCamera(
		const PlaySceneCamera* parent
	) = 0;

};

