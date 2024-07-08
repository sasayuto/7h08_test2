#include "pch.h"
#include"Ground.h"
using namespace DirectX;

#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

Ground::Ground() :
	Floor()
{
}

Ground::~Ground()
{
	
}

void Ground::Initialize()
{
	SetModel(Resources::GetInstance()->GetMinStoneStairsModel());
	Floor::Initialize();
	//当たり判定に位置と半径をセット
	GetCollider()->Initialize(GetPosition()-DirectX::SimpleMath::Vector3(0,5,0), GetRotate(), GetModel()->meshes[0]->boundingBox.Extents);
}
