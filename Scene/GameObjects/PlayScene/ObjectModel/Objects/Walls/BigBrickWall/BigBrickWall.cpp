#include "pch.h"
#include"BigBrickWall.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

using namespace DirectX;

BigBrickWall::BigBrickWall() :Objects()
{
	//���f�����Z�b�g
	SetObjectsModel(Resources::GetInstance()->GetBigBrickWallModel());

}

BigBrickWall::~BigBrickWall()
{

}

void BigBrickWall::Initialize()
{
	Objects::Initialize();

	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	DirectX::SimpleMath::Vector3 Extents = GetObjectsModel()->meshes[0]->boundingBox.Extents;

	GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
		GetPosition(),
		GetRotate(),
		GetObjectsModel()->meshes[0]->boundingBox.Center,
		DirectX::SimpleMath::Quaternion::Identity,
		GetObjectsModel()->meshes[0]->boundingBox.Extents
	));

	//��܂��ȓ����蔻��Ɉʒu�Ɣ��a���Z�b�g
	GetRoughCollider()->SetPosition(GetPosition());

	//�Ίp���̔���
	GetRoughCollider()->SetRadius(1000);
}

void BigBrickWall::Update()
{
}
void BigBrickWall::Render()
{
	//�X�P�[�����O�A�ʒu�����A��]��������
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotate());

	world *= SimpleMath::Matrix::CreateTranslation(GetPosition());

	//GetCollider()->Render(GetRotate());
	Draw::GetInstance()->ShadowMapRender(GetObjectsModel(), world);



}
void BigBrickWall::RenderShadowTex()
{
	//�X�P�[�����O�A�ʒu�����A��]��������
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotate());

	world *= SimpleMath::Matrix::CreateTranslation(GetPosition());

	//m_collider->Render(GetRotate());
	Draw::GetInstance()->ShadowMapTexCreate(GetObjectsModel(), world);

}
