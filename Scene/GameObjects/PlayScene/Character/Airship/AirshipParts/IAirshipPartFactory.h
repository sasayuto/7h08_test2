#pragma once
#include <combaseapi.h>

#include"IAirshipComponent.h"

/// <summary>
/// IPlayerPartFactoryインタフェースを定義する
/// </summary>
interface IAirshipPartFactory
{	
	/// <summary>
	///　プロペラを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのアドレス</returns>
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipBody(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipElevatorLeft(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipElevatorRight(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipRoom_01(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipRoom_02(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipPropellerSupportRight(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipPropellerSupportLeft(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipRudder(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipPropellerLeft(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipPropellerRight(
		const IAirshipComponent* parent,
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
	virtual std::unique_ptr<IAirshipComponent> CreateAirshipPropellerMiddle(
		const IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;
};
