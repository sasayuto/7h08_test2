#pragma once
#include <combaseapi.h>

#include"IStreetLightComponent.h"

/// <summary>
/// IPlayerPartFactoryインタフェースを定義する
/// </summary>
interface IStreetLightPartFactory
{	
	/// <summary>
	///　繋ぎ目を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>繋ぎ目のアドレス</returns>
	virtual std::unique_ptr<IStreetLightComponent> CreateStreetLightConnection(
		const IStreetLightComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　ライトを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>ライトのアドレス</returns>
	virtual std::unique_ptr<IStreetLightComponent> CreateStreetLightLight(
		const IStreetLightComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　土台を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>土台をのアドレス</returns>
	virtual std::unique_ptr<IStreetLightComponent> CreateStreetLightFoundation(
		const IStreetLightComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

};
