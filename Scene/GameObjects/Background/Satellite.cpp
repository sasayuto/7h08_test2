#include "pch.h"
#include "Satellite.h"
#include"pch.h"

using namespace DirectX;

Satellite::Satellite() :
    Background()
{
    SetBackGroundModel(Resources::GetInstance()->GetCloudyBackGroundModel());
}

Satellite::~Satellite()
{

}

