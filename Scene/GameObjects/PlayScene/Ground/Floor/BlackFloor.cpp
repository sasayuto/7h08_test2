#include "pch.h"
#include"BlackFloor.h"
using namespace DirectX;

BlackFloor::BlackFloor():
	Floor()
{
}

BlackFloor::~BlackFloor()
{
	
}

void BlackFloor::Initialize()
{
	SetModel(Resources::GetInstance()->GetStoneFloorModel());

	Floor::Initialize();
	//当たり判定に位置と半径をセット
	GetCollider()->Initialize(GetPosition(),GetRotate(), GetModel()->meshes[0]->boundingBox.Extents);
}

