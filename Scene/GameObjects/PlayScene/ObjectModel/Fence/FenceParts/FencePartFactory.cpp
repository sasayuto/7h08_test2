#include "pch.h"

#include "FencePartFactory.h"
#include "FenceNailPlank_Center_01.h"
#include "FenceNailPlank_Top_01.h"
#include "FenceNailPlank_Under_01.h"
#include "FenceVerticalPlank_01.h"

std::unique_ptr<IMoveObjectsComponent> FencePartFactory::Create(
	FenceParts fenceparts,
	IMoveObjectsComponent* parent, 
	const DirectX::SimpleMath::Vector3& position, 
	const DirectX::SimpleMath::Quaternion& angle
)
{
	std::unique_ptr<IMoveObjectsComponent> fenceParts;;
	switch (fenceparts)
	{
	case FencePartFactory::FENCE_NAIL_PLANK_CENTER_01:	
		fenceParts = std::make_unique<FenceNailPlank_Center_01>(parent, position, angle);
		break;

	case FencePartFactory::FENCE_NAIL_PLANK_CENTER_02:
		fenceParts = std::make_unique<FenceNailPlank_Center_02>(parent, position, angle);
		break;

	case FencePartFactory::FENCE_NAIL_PLANK_CENTER_03:
		fenceParts = std::make_unique<FenceNailPlank_Center_03>(parent, position, angle);
		break;

	case FencePartFactory::FENCE_NAIL_PLANK_TOP_01:
		fenceParts = std::make_unique<FenceNailPlank_Top_01>(parent, position, angle);
		break;

	case FencePartFactory::FENCE_NAIL_PLANK_TOP_02:
		fenceParts = std::make_unique<FenceNailPlank_Top_02>(parent, position, angle);
		break;

	case FencePartFactory::FENCE_NAIL_PLANK_TOP_03:
		fenceParts = std::make_unique<FenceNailPlank_Top_03>(parent, position, angle);
		break;

	case FencePartFactory::FENCE_NAIL_PLANK_UNDER_01:
		fenceParts = std::make_unique<FenceNailPlank_Under_01>(parent, position, angle);
		break;

	case FencePartFactory::FENCE_VERTICAL_PLANK_01:
		fenceParts = std::make_unique<FenceVerticalPlank_01>(parent, position, angle);
		break;

	case FencePartFactory::FENCE_VERTICAL_PLANK_02:
		fenceParts = std::make_unique<FenceVerticalPlank_02>(parent, position, angle);
		break;

	case FencePartFactory::FENCE_VERTICAL_PLANK_03:
		fenceParts = std::make_unique<FenceVerticalPlank_03>(parent, position, angle);
		break;

	case FencePartFactory::FENCE_VERTICAL_PLANK_04:
		fenceParts = std::make_unique<FenceVerticalPlank_04>(parent, position, angle);
		break;

	default:
		break;
	}
	// 初期化する
	fenceParts->Initialize();
	//プロペラののインスタンスを返す
	return move(fenceParts);
}
