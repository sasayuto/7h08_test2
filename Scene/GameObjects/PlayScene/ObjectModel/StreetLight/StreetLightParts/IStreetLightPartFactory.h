#pragma once
#include <combaseapi.h>

#include"IStreetLightComponent.h"

/// <summary>
/// IPlayerPartFactory�C���^�t�F�[�X���`����
/// </summary>
interface IStreetLightPartFactory
{	
	/// <summary>
	///�@�q���ڂ𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�q���ڂ̃A�h���X</returns>
	virtual std::unique_ptr<IStreetLightComponent> CreateStreetLightConnection(
		const IStreetLightComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@���C�g�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>���C�g�̃A�h���X</returns>
	virtual std::unique_ptr<IStreetLightComponent> CreateStreetLightLight(
		const IStreetLightComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	///�@�y��𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�y����̃A�h���X</returns>
	virtual std::unique_ptr<IStreetLightComponent> CreateStreetLightFoundation(
		const IStreetLightComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

};
