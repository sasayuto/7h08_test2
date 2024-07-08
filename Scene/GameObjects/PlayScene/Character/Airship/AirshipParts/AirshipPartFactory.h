#pragma once
#include "IAirshipComponent.h"
#include "IAirshipPartFactory.h"

/// <summary>
/// PlayerPartFactoryのクラスを定義する
/// </summary>
class AirshipPartFactory : public IAirshipPartFactory
{
public:
	/// <summary>
	///　飛行船のボディーを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>飛行船のボディーのポインタ</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipBody(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);	
	
	/// <summary>
	///　飛行船のElevatorLeftを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>飛行船のElevatorLeftのアドレス</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipElevatorLeft(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
	/// <summary>
	///　飛行船のElevatorRightを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>飛行船のElevatorRightのアドレス</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipElevatorRight(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　飛行船の部屋＿０１を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>飛行船の部屋＿０１のアドレス</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipRoom_01(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　飛行船の部屋＿０２を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>飛行船の部屋＿０２のアドレス</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipRoom_02(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　プロペラサポート右を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラサポート右のアドレス</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipPropellerSupportRight(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　プロペラサポート左を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラサポート左のアドレス</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipPropellerSupportLeft(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　舵を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>舵のアドレス</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipRudder(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
		/// <summary>
	///　プロペラの右を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラの右のアドレス</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipPropellerLeft(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　プロペラの左を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラの左のアドレス</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipPropellerRight(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　プロペラの真ん中を生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラの真ん中のアドレス</returns>
	static std::unique_ptr<IAirshipComponent> CreateAirshipPropellerMiddle(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

};

