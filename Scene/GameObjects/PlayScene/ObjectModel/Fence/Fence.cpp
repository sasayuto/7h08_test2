#include "pch.h"
#include"Fence.h"
#include <math.h>
#include<random>
using namespace DirectX;
#include"FenceManager.h"

#include"FenceParts/FencePartFactory.h"

Fence::Fence():
	MoveObjects()
{
	SetModel(Resources::GetInstance()->GetFenceModel());

	AddParts(FencePartFactory::Create(FencePartFactory::FenceParts::FENCE_VERTICAL_PLANK_01, nullptr, GetPosition(), GetRotate()));
	AddParts(FencePartFactory::Create(FencePartFactory::FenceParts::FENCE_VERTICAL_PLANK_02, nullptr, GetPosition(), GetRotate()));
	AddParts(FencePartFactory::Create(FencePartFactory::FenceParts::FENCE_VERTICAL_PLANK_03, nullptr, GetPosition(), GetRotate()));
	AddParts(FencePartFactory::Create(FencePartFactory::FenceParts::FENCE_VERTICAL_PLANK_04, nullptr, GetPosition(), GetRotate()));
}

