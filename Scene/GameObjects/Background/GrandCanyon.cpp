#include"pch.h"
#include"GrandCanyon.h"

using namespace DirectX;

GrandCanyon::GrandCanyon() :
    Background()
{
    SetBackGroundModel(Resources::GetInstance()->GetCloudyBackGroundModel());
}

GrandCanyon::~GrandCanyon()
{
}
