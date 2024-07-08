#pragma once
#include "ITurretComponent.h"
#include "ITurretPartFactory.h"

class BulletManager;
/// <summary>
/// PlayerPartFactoryのクラスを定義する
/// </summary>
class TurretPartFactory : public ITurretPartFactory
{
public:
	/// <summary>
	///　タレットの土台を生成する
	/// </summary>
	/// <param name="parent">球の管理者のポインタ</param>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>タレットの土台のアドレス</returns>
	static std::unique_ptr<ITurretComponent> CreateTurretBase(
		BulletManager* bulletManager,
		ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　タレットの真ん中の大砲を生成する
	/// </summary>
	/// <param name="parent">球の管理者のポインタ</param>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>タレットの真ん中の大砲のアドレス</returns>
	static std::unique_ptr<ITurretComponent> CreateTurretCancer_Middle(
		BulletManager* bulletManager,
		ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　タレットの左の大砲を生成する
	/// </summary>
	/// <param name="parent">球の管理者のポインタ</param>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>タレットの左の大砲のアドレス</returns>
	static std::unique_ptr<ITurretComponent> CreateTurretCancer_Left(
		BulletManager* bulletManager,
		ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　タレットの右の大砲を生成する
	/// </summary>
	/// <param name="parent">球の管理者のポインタ</param>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>タレットの右の大砲のアドレス</returns>
	static std::unique_ptr<ITurretComponent> CreateTurretCancer_Right(
		BulletManager* bulletManager,
		ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///　タレットの頭を生成する
	/// </summary>
	/// <param name="parent">球の管理者のポインタ</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>タレットの頭のアドレス</returns>
	static std::unique_ptr<ITurretComponent> CreateTurretHead(
		BulletManager* bulletManager,
		ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

};

