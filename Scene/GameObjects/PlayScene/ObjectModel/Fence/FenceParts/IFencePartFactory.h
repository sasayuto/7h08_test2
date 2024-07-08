#pragma once
#include <combaseapi.h>

struct IMoveObjectsComponent;
/// <summary>
/// IPlayerPartFactory�C���^�t�F�[�X���`����
/// </summary>
interface IFencePartFactory
{
	/// <summary>
	///�@���C�g�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>���C�g�̃A�h���X</returns>
	virtual std::unique_ptr<IMoveObjectsComponent> Create(
		const IMoveObjectsComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;
};