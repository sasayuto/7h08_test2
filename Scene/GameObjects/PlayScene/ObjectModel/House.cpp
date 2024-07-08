#include "pch.h"
#include"House.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

using namespace DirectX;

House::House() :Objects()
{
	//モデルをセット
	SetObjectsModel(Resources::GetInstance()->GetHouseModel());
}

House::~House()
{

}

void House::Initialize()
{
	Objects::Initialize();

	//当たり判定に位置と半径をセット
	DirectX::SimpleMath::Vector3 Extents = GetObjectsModel()->meshes[0]->boundingBox.Extents;

	GetRoughCollider()->SetPosition(GetPosition());
	GetRoughCollider()->SetRadius(20.f);


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(14.5f, 9.f, 7.4f)));


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(-0.4f, 10.2f, 3.7f),
		DirectX::SimpleMath::Quaternion(0.284015f, 0.f, 0.f, 0.95882f),
		DirectX::SimpleMath::Vector3(15.f, 1.f, 5.f)));


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(-0.4f, 10.2f, -3.7f),
		DirectX::SimpleMath::Quaternion(-0.284015f, 0.f, 0.f, 0.95882f),
		DirectX::SimpleMath::Vector3(15.f, 1.f, 5.f)));


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(-1.f, 10.4f, 4.5f),
		DirectX::SimpleMath::Quaternion(0.f, 0.f, 0.382683f, 0.92388f),
		DirectX::SimpleMath::Vector3(2.f, 2.f, 3.f)));

}

