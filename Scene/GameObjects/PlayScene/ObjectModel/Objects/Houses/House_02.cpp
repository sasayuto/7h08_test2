#include "pch.h"
#include"House_02.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

using namespace DirectX;

House_02::House_02() :Objects()
{
	//モデルをセット
	SetObjectsModel(Resources::GetInstance()->GetHouse_02Model());
}

House_02::~House_02()
{

}

void House_02::Initialize()
{
	Objects::Initialize();

	//当たり判定に位置と半径をセット

	GetRoughCollider()->SetPosition(GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.f, 4.5f, 0.f), GetRotate()));
	GetRoughCollider()->SetRadius(9.f);


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(-0.5f, 2.6f, 0.f),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(5.65821f, 2.45688f, 5.53764f)));


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(-0.5f, 6.5f, 3.1f),
		DirectX::SimpleMath::Quaternion(-0.522499f, 0.f, 0.f, 0.85264f),
		DirectX::SimpleMath::Vector3(6.15821f, 3.35688f, -0.0623608f)));


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(-0.5f, 6.5f, -3.1f),
		DirectX::SimpleMath::Quaternion(0.522499f, 0.f, 0.f, 0.85264f),
		DirectX::SimpleMath::Vector3(6.15821f, 3.35688f, -0.0623608f)));


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(5.89f, 5.f, -0.1f),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(0.658208f, 5.05688f, 0.737639f)));

}

void House_02::Update()
{
}
