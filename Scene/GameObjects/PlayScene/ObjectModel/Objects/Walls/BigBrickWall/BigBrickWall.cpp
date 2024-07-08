#include "pch.h"
#include"BigBrickWall.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

using namespace DirectX;

BigBrickWall::BigBrickWall() :Objects()
{
	//モデルをセット
	SetObjectsModel(Resources::GetInstance()->GetBigBrickWallModel());

}

BigBrickWall::~BigBrickWall()
{

}

void BigBrickWall::Initialize()
{
	Objects::Initialize();

	//当たり判定に位置と半径をセット
	DirectX::SimpleMath::Vector3 Extents = GetObjectsModel()->meshes[0]->boundingBox.Extents;

	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		GetObjectsModel()->meshes[0]->boundingBox.Center,
		DirectX::SimpleMath::Quaternion::Identity,
		GetObjectsModel()->meshes[0]->boundingBox.Extents
	));

	//大まかな当たり判定に位置と半径をセット
	GetRoughCollider()->SetPosition(GetPosition());

	//対角線の半分
	GetRoughCollider()->SetRadius(1000);
}

void BigBrickWall::Update()
{
}
void BigBrickWall::Render()
{
	//スケーリング、位置調整、回転をさせる
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotate());

	world *= SimpleMath::Matrix::CreateTranslation(GetPosition());

	//GetCollider()->Render(GetRotate());
	Draw::GetInstance()->ShadowMapRender(GetObjectsModel(), world);



}
void BigBrickWall::RenderShadowTex()
{
	//スケーリング、位置調整、回転をさせる
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotate());

	world *= SimpleMath::Matrix::CreateTranslation(GetPosition());

	//m_collider->Render(GetRotate());
	Draw::GetInstance()->ShadowMapTexCreate(GetObjectsModel(), world);

}
