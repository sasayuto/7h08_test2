#include "pch.h"
#include"WindmillTower.h"
#include"WindmillPartFactory.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include<random>

const float WindmillTower::FALL_SPEED_ACCELERATION	(0.12f / 60);	//�����̉����x			(m/s)
const float WindmillTower::EXPLOSIVE_ROTATE			(120.0f / 60);	//���f���̉�]�̑���	(��/s�j
const float WindmillTower::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float WindmillTower::EXPLOSIVE_POWER(2.0f / 60);		//�����̉��̃p���[		(m/s)


WindmillTower::WindmillTower(IWindmillComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	WindmillComponent(parent, position, angle)
{
	AddPart(WindmillPartFactory::CreateWindmillBlade_01(parent, position, angle));
	AddPart(WindmillPartFactory::CreateWindmillBlade_02(parent, position, angle));
	//���f�����Z�b�g
	SetPartModel(Resources::GetInstance()->GetWindmillTowerModel());
}

WindmillTower::~WindmillTower()
{

}

void WindmillTower::Initialize()
{	

	//�����蔻��̏�����
	GetCollider()->Initialize(
		GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		GetRotate(),
		GetPartModel()->meshes[0]->boundingBox.Extents
	);
	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Initialize();
	}

}

void WindmillTower::Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{	
	//�e�������Ȃ�����X�V���Ȃ�//
	////�e�̈ʒu�ƍ��킹��
	//SetPosition(position);
	////�e�̉�]�ƍ��킹��
	//SetRotate(angle);
	////�����蔻��̍X�V
	//GetCollider()->Update(
	//	GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
	//	GetRotate()
	//	);

	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Update(GetPosition(), GetRotate());
	}

}

void WindmillTower::Render()
{

	//�X�P�[�����O�A�ʒu�����A��]��������
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

	world = rotate * translation;

	// ��s�@�̕`��
	Draw::GetInstance()->ShadowMapRenderNoPicture(GetPartModel(), world);

	//Draw::GetInstance()->TestCubeModel(
	//	GetPartModel()->meshes[0]->boundingBox.Extents, 
	//	GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
	//	GetRotate()
	//);

		// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Render();
	}
}


void WindmillTower::Finalize()
{
}
