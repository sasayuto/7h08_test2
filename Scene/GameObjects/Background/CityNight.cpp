#include "pch.h"
#include "CityNight.h"
#include"pch.h"

using namespace DirectX;

CityNight::CityNight() :
    Background()
{
    SetBackGroundModel(Resources::GetInstance()->GetCloudyBackGroundModel());
}

CityNight::~CityNight()
{

}

