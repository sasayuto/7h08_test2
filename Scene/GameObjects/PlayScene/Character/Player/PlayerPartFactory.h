#pragma once
#include "IPlayerComponent.h"
#include "IPlayerPartFactory.h"

/// <summary>
/// PlayerPartFactoryのクラスを定義する
/// </summary>
class PlayerPartFactory : public IPlayerPartFactory
{
public:
	/// <summary>
	///　プロペラを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのポインタ</returns>
	static std::unique_ptr<IPlayerComponent> CreatePlayerPro(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　羽を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>羽のポインタ</returns>
	static std::unique_ptr<IPlayerComponent> CreatePlayerWing(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　ボディーを生成する
	/// </summary>
	/// <param name="parent">親のポインタ</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>ボディーのポインタ</returns>
	static std::unique_ptr<IPlayerComponent> CreatePlayerBody(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　尻尾を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>尻尾のポインタ</returns>
	static std::unique_ptr<IPlayerComponent> CreatePlayerTail(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　水平尾翼を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>水平尻尾のポインタ</returns>
	static std::unique_ptr<IPlayerComponent> CreatePlayerHorizontalStabilizer(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　タイヤを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>タイヤポインタ</returns>
	static std::unique_ptr<IPlayerComponent> CreatePlayerLeftTire(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　タイヤを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>タイヤポインタ</returns>
	static std::unique_ptr<IPlayerComponent> CreatePlayerRightTire(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　ホイールを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>ホイールのポインタ</returns>
	static std::unique_ptr<IPlayerComponent> CreatePlayerWheelSupport(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

};

