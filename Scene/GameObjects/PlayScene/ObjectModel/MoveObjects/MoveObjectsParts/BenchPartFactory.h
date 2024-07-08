#pragma once
#include "IBenchComponent.h"
#include "IBenchPartFactory.h"
class IStreetLightPartFactory;
/// <summary>
/// PlayerPartFactoryのクラスを定義する
/// </summary>
class BenchPartFactory : public IBenchPartFactory
{
public:
	/// <summary>
	///　ライトを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>ライトのアドレス</returns>
	static std::unique_ptr<IBenchComponent> CreateBenchBackWood(
		IBenchComponent* parent,
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
	static std::unique_ptr<IBenchComponent> CreateBenchFrame_Left(
		IBenchComponent* parent,
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
	static std::unique_ptr<IBenchComponent> CreateBenchFrame_Right(
		IBenchComponent* parent,
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
	static std::unique_ptr<IBenchComponent> CreateBenchUnderWood(
		IBenchComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
};

