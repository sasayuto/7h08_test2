#pragma once
#include <combaseapi.h>
#ifndef ITURRET_FACTORY_DEFINED
#define ITURRET_FACTORY_DEFINED
#include"IPlayerComponent.h"

/// <summary>
/// IPlayerPartFactoryインタフェースを定義する
/// </summary>
interface  IPlayerPartFactory
{	
	/// <summary>
	///　プロペラを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのアドレス</returns>
	virtual std::unique_ptr<IPlayerComponent> CreatePlayerPro(
		const IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　羽を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>羽のポインタ</returns>
	virtual std::unique_ptr<IPlayerComponent> CreatePlayerWing(
		const IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　ボディーを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>ボディーのポインタ</returns>
	virtual std::unique_ptr<IPlayerComponent> CreatePlayerBody(
		const IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　尻尾を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>尻尾のポインタ</returns>
	virtual std::unique_ptr<IPlayerComponent> CreatePlayerTail(
		const IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　水平尾翼を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>水平尻尾のポインタ</returns>
	virtual std::unique_ptr<IPlayerComponent> CreatePlayerHorizontalStabilizer(
		const IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　右タイヤを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>タイヤのポインタ</returns>
	virtual std::unique_ptr<IPlayerComponent> CreatePlayerLeftTire(
		const IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　左タイヤを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>タイヤのポインタ</returns>
	virtual std::unique_ptr<IPlayerComponent> CreatePlayerRightTire(
		const IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　ホイールを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>ホイールのポインタ</returns>
	virtual std::unique_ptr<IPlayerComponent> CreatePlayerWheelSupport(
		const IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;
};

#endif	// ITURRET_FACTORY_DEFINED