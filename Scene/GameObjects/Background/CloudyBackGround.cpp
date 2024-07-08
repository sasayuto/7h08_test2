#include "pch.h"
#include "CloudyBackGround.h"
#include"pch.h"

using namespace DirectX;

CloudyBackGround::CloudyBackGround() :
    Background()
{
    SetBackGroundModel(Resources::GetInstance()->GetCloudyBackGroundModel());
}

CloudyBackGround::~CloudyBackGround()
{

}

