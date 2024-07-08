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

	//当たり判定を作る
	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		Extents
	));

	//大まかな当たり判定に位置と半径をセット
	GetRoughCollider()->SetPosition(GetPosition());

	//対角線の半分
	GetRoughCollider()->SetRadius(sqrt(Extents.LengthSquared()));
}

void House::Update()
{
}
