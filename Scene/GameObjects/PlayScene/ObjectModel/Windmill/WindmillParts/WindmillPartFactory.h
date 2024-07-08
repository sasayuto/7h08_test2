#pragma once
#include "IWindmillComponent.h"
#include "IWindmillPartFactory.h"
struct IWindmillPartFactory;
/// <summary>
/// PlayerPartFactory�̃N���X���`����
/// </summary>
class WindmillPartFactory : public IWindmillPartFactory
{
public:
	/// <summary>
	///�@�v���y���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃A�h���X</returns>
	static std::unique_ptr<IWindmillComponent> CreateWindmillFoundation(
		IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�v���y���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃A�h���X</returns>
	static std::unique_ptr<IWindmillComponent> CreateWindmillTower(
		IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
	/// <summary>
	///�@�v���y���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃A�h���X</returns>
	static std::unique_ptr<IWindmillComponent> CreateWindmillRoom(
		IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
	/// <summary>
	///�@�v���y���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃A�h���X</returns>
	static std::unique_ptr<IWindmillComponent> CreateWindmillBlade_01(
		IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
	/// <summary>
	///�@�v���y���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃A�h���X</returns>
	static std::unique_ptr<IWindmillComponent> CreateWindmillBlade_02(
		IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
	/// <summary>
	///�@�v���y���𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃A�h���X</returns>
	static std::unique_ptr<IWindmillComponent> CreateWindmillStairs(
		IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
};

