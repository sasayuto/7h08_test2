#pragma once
#include "../../MoveObjects/MoveObjectsParts/IMoveObjectsComponent.h"
#include "IFencePartFactory.h"
struct IStreetLightPartFactory;
/// <summary>
/// PlayerPartFactoryのクラスを定義する
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
	///　ライトを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>ライトのアドレス</returns>
	static std::unique_ptr<IMoveObjectsComponent> Create(
		FenceParts fenceparts,
		IMoveObjectsComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
};