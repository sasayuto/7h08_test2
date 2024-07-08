#include "pch.h"
#include"StoneStairs.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

using namespace DirectX;

StoneStairs::StoneStairs() :Objects()
{
	//モデルをセット
	SetObjectsModel(Resources::GetInstance()->GetStoneStairsModel());
}

StoneStairs::~StoneStairs()
{

}

void StoneStairs::Initialize()
{
	Objects::Initialize();

	//当たり判定を作る
	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(-32, 30, 0),
		DirectX::SimpleMath::Quaternion(0, 0, -0.382683f, 0.92388f),
		DirectX::SimpleMath::Vector3(46.8505f, 2.41238f, 31.5351f)));


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(-33.6f, 33.9f, -32.8f),
		DirectX::SimpleMath::Quaternion(0, 0, -0.382683f, 0.92388),
		DirectX::SimpleMath::Vector3(46.8505f, 4.21238f, 1.23509f)));


	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(-33.6f, 33.9f, 32.8f),
		DirectX::SimpleMath::Quaternion(0, 0, -0.382683f, 0.92388f),
		DirectX::SimpleMath::Vector3(46.8505f, 4.21238f, 1.23509f)));

	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(2, 4.f, 33),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(1.5f, 4.61238f, 1.53509f)));

	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(2, 4.f, -33),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(1.5f, 4.61238f, 1.53509f)));

	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(-65, 67.f, 33),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(1.5f, 4.61238f, 1.53509f)));

	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		DirectX::SimpleMath::Vector3(-65, 67.f, -33),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(1.5f, 4.61238f, 1.53509f)));

	////大まかな当たり判定に位置と半径をセット
	GetRoughCollider()->SetPosition(GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(-33.0f, 34.0f, 0.0f), GetRotate()));


	GetRoughCollider()->SetRadius(62.0f);
}
