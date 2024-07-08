#pragma once
#include <combaseapi.h>

#include"IBenchComponent.h"

/// <summary>
/// IPlayerPartFactoryインタフェースを定義する
/// </summary>
interface IBenchPartFactory
{	
	/// <summary>
	///　ライトを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>ライトのアドレス</returns>
	virtual std::unique_ptr<IBenchComponent> CreateBenchBackWood(
		const IBenchComponent* parent,
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
	virtual std::unique_ptr<IBenchComponent> CreateBenchFrame_Left(
		const IBenchComponent* parent,
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
	virtual std::unique_ptr<IBenchComponent> CreateBenchFrame_Right(
		const IBenchComponent* parent,
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
	virtual std::unique_ptr<IBenchComponent> CreateBenchUnderWood(
		const IBenchComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

};
