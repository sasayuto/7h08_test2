#pragma once
#include "IStreetLightComponent.h"
#include "IStreetLightPartFactory.h"
struct IStreetLightPartFactory;
/// <summary>
/// PlayerPartFactory�̃N���X���`����
/// </summary>
class StreetLightPartFactory : public IStreetLightPartFactory
{
public:
	/// <summary>
	///�@�q���ڂ𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�q���ڂ̃A�h���X</returns>
	static std::unique_ptr<IStreetLightComponent> CreateStreetLightConnection(
		IStreetLightComponent* parent,
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
	static std::unique_ptr<IStreetLightComponent> CreateStreetLightLight(
		IStreetLightComponent* parent,
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
	static std::unique_ptr<IStreetLightComponent> CreateStreetLightFoundation(
		IStreetLightComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
};

