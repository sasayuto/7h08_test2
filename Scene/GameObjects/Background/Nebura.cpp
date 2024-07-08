#include"pch.h"
#include"Nebura.h"
#include"Scene/GameObjects/Models/Resources.h"

using namespace DirectX;

Nebura::Nebura() :
    Background()
{
    SetBackGroundModel(Resources::GetInstance()->GetCloudyBackGroundModel());
}
Nebura::~Nebura()
{

}

