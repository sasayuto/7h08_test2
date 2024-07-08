#include "pch.h"
#include"MinStoneFloor.h"
using namespace DirectX;

MinStoneFloor::MinStoneFloor() :
	Floor()
{
	SetModel(Resources::GetInstance()->GetMinStoneStairsModel());
}

MinStoneFloor::~MinStoneFloor()
{
}

void MinStoneFloor::Initialize()
{
	Floor::Initialize();
	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	GetCollider()->Initialize(GetPosition(), GetRotate(), GetModel()->meshes[0]->boundingBox.Extents);
}

void MinStoneFloor::Update()
{
	GetCollider()->Update(GetPosition(), GetRotate());
}

void MinStoneFloor::Render()
{
	//�X�P�[�����O�A�ʒu�����A��]��������
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotate());

	world *= SimpleMath::Matrix::CreateTranslation(GetPosition());
	Draw::GetInstance()->ShadowMapRender(GetModel(), world);
}

