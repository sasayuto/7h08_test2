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
	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	GetCollider()->Initialize(GetPosition(),GetRotate(), GetModel()->meshes[0]->boundingBox.Extents);
}

