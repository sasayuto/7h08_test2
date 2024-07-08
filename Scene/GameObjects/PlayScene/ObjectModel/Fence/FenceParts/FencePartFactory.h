#pragma once
#include "../../MoveObjects/MoveObjectsParts/IMoveObjectsComponent.h"
#include "IFencePartFactory.h"
struct IStreetLightPartFactory;
/// <summary>
/// PlayerPartFactory�̃N���X���`����
/// </summary>
class FencePartFactory : public IFencePartFactory
{
public:
	enum FenceParts
	{
		FENCE_NAIL_PLANK_CENTER_01,
		FENCE_NAIL_PLANK_CENTER_02,
		FENCE_NAIL_PLANK_CENTER_03,
		FENCE_NAIL_PLANK_TOP_01,
		FENCE_NAIL_PLANK_TOP_02,
		FENCE_NAIL_PLANK_TOP_03,
		FENCE_NAIL_PLANK_UNDER_01,
		FENCE_VERTICAL_PLANK_01,
		FENCE_VERTICAL_PLANK_02,
		FENCE_VERTICAL_PLANK_03,
		FENCE_VERTICAL_PLANK_04,
	};

	/// <summary>
	///�@���C�g�𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>���C�g�̃A�h���X</returns>
	static std::unique_ptr<IMoveObjectsComponent> Create(
		FenceParts fenceparts,
		IMoveObjectsComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
};