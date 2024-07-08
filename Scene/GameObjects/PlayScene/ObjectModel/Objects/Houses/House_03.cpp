#include "pch.h"
#include"House_03.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
using namespace DirectX;

House_03::House_03() :Objects()
{
	//モデルをセット
	SetObjectsModel(Resources::GetInstance()->GetHouse_03Model());
}

House_03::~House_03()
{

}

void House_03::Initialize()
{
	Objects::Initialize();

	//当たり判定に位置と半径をセット
	DirectX::SimpleMath::Vector3 Extents = GetObjectsModel()->meshes[0]->boundingBox.Extents;

	//９０度回転

	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(1.5f, 5.6f, 0.f),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(16.2492f, 7.32154f, 10.4168f)));


	GetRoughCollider()->SetPosition(GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.f, 5.f, -1.f), GetRotate()));
	GetRoughCollider()->SetRadius(24.f);


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(1.4f, 13.2f, 5.f),
		DirectX::SimpleMath::Quaternion(-0.551937f, 0.f, 0.f, 0.833886f),
		DirectX::SimpleMath::Vector3(17.1492f, 6.32154f, 2.81683f)));


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(1.4f, 13.2f, -4.4f),
		DirectX::SimpleMath::Quaternion(0.551937f, 0.f, 0.f, 0.833886f),
		DirectX::SimpleMath::Vector3(17.1492f, 6.32154f, 2.81683f)));


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(6.65f, 17.7f, 3.1f),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(0.74921f, 1.92154f, 0.716828f)));


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(-10.55f, 17.7f, 3.1f),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(0.74921f, 1.92154f, 0.716828f)));


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(-4.2f, 16.2f, 6.6f),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(0.74921f, 1.92154f, 0.766828f)));


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(-4.7f, 17.4f, -3.3f),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(0.74921f, 1.92154f, 0.766828f)));


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(7.3f, 16.1f, -6.6f),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(0.74921f, 1.92154f, 0.766828f)));


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(11.5f, 16.2f, 6.6f),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(0.74921f, 1.92154f, 0.766828f)));






}

void House_03::Update()
{

}
