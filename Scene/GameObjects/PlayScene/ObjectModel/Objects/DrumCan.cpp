#include "pch.h"
#include"House.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

using namespace DirectX;

House::House() :Objects()
{
	//���f�����Z�b�g
	SetObjectsModel(Resources::GetInstance()->GetHouseModel());
}

House::~House()
{

}

void House::Initialize()
{
	Objects::Initialize();

	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	DirectX::SimpleMath::Vector3 Extents = GetObjectsModel()->meshes[0]->boundingBox.Extents;

	//�����蔻������
	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		Extents
	));

	//��܂��ȓ����蔻��Ɉʒu�Ɣ��a���Z�b�g
	GetRoughCollider()->SetPosition(GetPosition());

	//�Ίp���̔���
	GetRoughCollider()->SetRadius(sqrt(Extents.LengthSquared()));
}

void House::Update()
{
}
