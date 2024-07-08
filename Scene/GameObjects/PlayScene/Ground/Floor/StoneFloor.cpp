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
	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	GetCollider()->Initialize(GetPosition(), GetRotate(), GetModel()->meshes[0]->boundingBox.Extents);
}

