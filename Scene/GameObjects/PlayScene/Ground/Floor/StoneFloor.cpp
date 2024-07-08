#include "pch.h"
#include"StoneFloor.h"
using namespace DirectX;

StoneFloor::StoneFloor():
	Floor()
{
}

StoneFloor::~StoneFloor()
{
	
}

void StoneFloor::Initialize()
{
	SetModel(Resources::GetInstance()->GetStoneFloorModel());

	Floor::Initialize();
	//当たり判定に位置と半径をセット
	GetCollider()->Initialize(GetPosition(), GetRotate(), GetModel()->meshes[0]->boundingBox.Extents);
}

