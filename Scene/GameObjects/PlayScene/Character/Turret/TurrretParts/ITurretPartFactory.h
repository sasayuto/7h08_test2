#pragma once
#include <combaseapi.h>

#include"ITurretComponent.h"

class BulletManager;
/// <summary>
/// ITurretPartFactoryインタフェースを定義する
/// </summary>
interface ITurretPartFactory
{	
	/// <summary>
	///　タレットの土台を生成する
	/// </summary>
	/// <param name="parent">球の管理者のポインタ</param>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>タレットの土台のアドレス</returns>
	virtual std::unique_ptr<ITurretComponent> CreateTurretBase(
		const BulletManager* bulletManager,
		const ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;
	/// <summary>
	///　タレットの真ん中の大砲を生成する
	/// </summary>
	/// <param name="parent">球の管理者のポインタ</param>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>タレットの真ん中の大砲のアドレス</returns>
	virtual std::unique_ptr<ITurretComponent> CreateTurretCancer_Middle(
		const BulletManager* bulletManager,
		const ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　タレットの左の大砲を生成する
	/// </summary>
	/// <param name="parent">球の管理者のポインタ</param>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>タレットの左の大砲のアドレス</returns>
	virtual std::unique_ptr<ITurretComponent> CreateTurretCancer_Left(
		const BulletManager* bulletManager,
		const ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　タレットの右の大砲を生成する
	/// </summary>
	/// <param name="parent">球の管理者のポインタ</param>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>タレットの右の大砲のアドレス</returns>
	virtual std::unique_ptr<ITurretComponent> CreateTurretCancer_Right(
		const BulletManager* bulletManager,
		const ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///　タレットの頭を生成する
	/// </summary>
	/// <param name="parent">球の管理者のポインタ</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>タレットの頭のアドレス</returns>
	virtual std::unique_ptr<ITurretComponent> CreateTurretHead(
		const BulletManager* bulletManager,
		const ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;
};
