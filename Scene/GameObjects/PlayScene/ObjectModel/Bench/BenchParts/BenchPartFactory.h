#pragma once
#include "../../MoveObjects/MoveObjectsParts/IMoveObjectsComponent.h"
#include "IBenchPartFactory.h"
class IStreetLightPartFactory;
/// <summary>
/// PlayerPartFactory�̃N���X���`����
/// </summary>
class BenchPartFactory : public IBenchPartFactory
{
public:
	/// <summary>
	///�@���C�g�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>���C�g�̃A�h���X</returns>
	static std::unique_ptr<IMoveObjectsComponent> CreateBenchBackWood(
		IMoveObjectsComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@���C�g�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>���C�g�̃A�h���X</returns>
	static std::unique_ptr<IMoveObjectsComponent> CreateBenchFrame_Left(
		IMoveObjectsComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@���C�g�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>���C�g�̃A�h���X</returns>
	static std::unique_ptr<IMoveObjectsComponent> CreateBenchFrame_Right(
		IMoveObjectsComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	///�@�y��𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�y����̃A�h���X</returns>
	static std::unique_ptr<IMoveObjectsComponent> CreateBenchUnderWood(
		IMoveObjectsComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
};

