#pragma once
#include "IStreetLightComponent.h"
#include "IStreetLightPartFactory.h"
struct IStreetLightPartFactory;
/// <summary>
/// PlayerPartFactoryのクラスを定義する
/// </summary>
class StreetLightPartFactory : public IStreetLightPartFactory
{
public:
	/// <summary>
	///　繋ぎ目を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>繋ぎ目のアドレス</returns>
	static std::unique_ptr<IStreetLightComponent> CreateStreetLightConnection(
		IStreetLightComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　ライトを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>ライトのアドレス</returns>
	static std::unique_ptr<IStreetLightComponent> CreateStreetLightLight(
		IStreetLightComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　土台を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>土台をのアドレス</returns>
	static std::unique_ptr<IStreetLightComponent> CreateStreetLightFoundation(
		IStreetLightComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
};

