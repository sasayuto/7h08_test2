#pragma once
#include <combaseapi.h>

#include"IWindmillComponent.h"

/// <summary>
/// IPlayerPartFactoryインタフェースを定義する
/// </summary>
interface IWindmillPartFactory
{	
	/// <summary>
	///　プロペラを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのアドレス</returns>
	virtual std::unique_ptr<IWindmillComponent> CreateWindmillBlade_01(
		const IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　プロペラを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのアドレス</returns>
	virtual std::unique_ptr<IWindmillComponent> CreateWindmillBlade_02(
		const IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　プロペラを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのアドレス</returns>
	virtual std::unique_ptr<IWindmillComponent> CreateWindmillFoundation(
		const IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　プロペラを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのアドレス</returns>
	virtual std::unique_ptr<IWindmillComponent> CreateWindmillRoom(
		const IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　プロペラを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのアドレス</returns>
	virtual std::unique_ptr<IWindmillComponent> CreateWindmillTower(
		const IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　プロペラを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのアドレス</returns>
	virtual std::unique_ptr<IWindmillComponent> CreateWindmillStairs(
		const IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;
};
