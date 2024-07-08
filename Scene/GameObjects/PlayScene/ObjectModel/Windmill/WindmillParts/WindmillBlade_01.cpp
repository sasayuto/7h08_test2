#include "pch.h"
#include"WindmillBlade_01.h"
#include"WindmillPartFactory.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include<random>

const float WindmillBlade_01::FALL_SPEED_ACCELERATION	(0.12f / 60);	//�����̉����x			(m/s)
const float WindmillBlade_01::EXPLOSIVE_ROTATE			(120.0f / 60);	//���f���̉�]�̑���	(��/s�j
const float WindmillBlade_01::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float WindmillBlade_01::EXPLOSIVE_POWER(2.0f / 60);		//�����̉��̃p���[		(m/s)

const float PROPELLER_ACCELERATION(2.0f / 60);//�v���y���̉�]�̉����x(��/s�j
const float PROPELLER_COOL_TIME(0.95f);	//��C��R

WindmillBlade_01::WindmillBlade_01(IWindmillComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	WindmillComponent(
		parent,
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(-6, 12.6f, 0), angle),
		angle
	),
	m_angle(),
	m_velcity()
{
	//���f�����Z�b�g
	SetPartModel(Resources::GetInstance()->GetWindmillBladeModel());
}

WindmillBlade_01::~WindmillBlade_01()
{

}

void WindmillBlade_01::Initialize()
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

void WindmillBlade_01::Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{	
	//�����x�v�Z
	m_velcity.z += PROPELLER_ACCELERATION;

	//�����x�ɋ�C��R��������
	m_velcity.z *= PROPELLER_COOL_TIME;

	//�v���y�����̊p�x�ɑ��x�𑫂�
	m_angle.z += m_velcity.z;

	//�e�������Ȃ�����X�V���Ȃ�//

	//�N�I�[�^�j�I����]�����
	SetRotate(
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3::UnitX,
			DirectX::XMConvertToRadians(m_angle.z)
		) *
		angle
	);

	//�����蔻��̍X�V
	GetCollider()->Update(
		GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		GetRotate()
		);

	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Update(GetPosition(), GetRotate());
	}

}

void WindmillBlade_01::Render()
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

void WindmillBlade_01::Finalize()
{
}

