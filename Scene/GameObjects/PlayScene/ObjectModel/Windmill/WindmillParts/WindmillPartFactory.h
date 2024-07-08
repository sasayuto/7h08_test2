#pragma once
#include "IWindmillComponent.h"
#include "IWindmillPartFactory.h"
struct IWindmillPartFactory;
/// <summary>
/// PlayerPartFactoryのクラスを定義する
/// </summary>
class WindmillPartFactory : public IWindmillPartFactory
{
public:
	/// <summary>
	///　プロペラを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのアドレス</returns>
	static std::unique_ptr<IWindmillComponent> CreateWindmillFoundation(
		IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　プロペラを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのアドレス</returns>
	static std::unique_ptr<IWindmillComponent> CreateWindmillTower(
		IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
	/// <summary>
	///　プロペラを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのアドレス</returns>
	static std::unique_ptr<IWindmillComponent> CreateWindmillRoom(
		IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
	/// <summary>
	///　プロペラを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのアドレス</returns>
	static std::unique_ptr<IWindmillComponent> CreateWindmillBlade_01(
		IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
	/// <summary>
	///　プロペラを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのアドレス</returns>
	static std::unique_ptr<IWindmillComponent> CreateWindmillBlade_02(
		IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
	/// <summary>
	///　プロペラを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>プロペラのアドレス</returns>
	static std::unique_ptr<IWindmillComponent> CreateWindmillStairs(
		IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
};

