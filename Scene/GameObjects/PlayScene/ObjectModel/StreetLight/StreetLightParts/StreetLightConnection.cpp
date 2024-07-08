#include "pch.h"
#include"StreetLightConnection.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"StreetLightPartFactory.h"
#include<random>

const float StreetLightConnection::FALL_SPEED_ACCELERATION	(0.12f / 60);	//�����̉����x			(m/s)
const float StreetLightConnection::EXPLOSIVE_ROTATE			(120.0f / 60);	//���f���̉�]�̑���	(��/s�j
const float StreetLightConnection::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float StreetLightConnection::EXPLOSIVE_POWER(2.0f / 60);		//�����̉��̃p���[		(m/s)

StreetLightConnection::StreetLightConnection(IStreetLightComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	StreetLightComponent(
		parent,
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.66f, 3.66f, 0), angle),
		angle
	)
{
	AddPart(StreetLightPartFactory::CreateStreetLightLight(nullptr, GetPosition(), GetRotate()));

	//���f�����Z�b�g
	SetPartModel(Resources::GetInstance()->GetStreetLightConnectionModel());
}

StreetLightConnection::~StreetLightConnection()
{

}

void StreetLightConnection::Initialize()
{	
	//360�x�����_���ȕ������擾
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> dist(0, 6.28f);
	float explosionSpeedX = static_cast<float>(dist(engine));

	//�����_���ȉ�]���Z�b�g
	SetRandomRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, explosionSpeedX));

	//�����͂������_���ɂ���
	std::uniform_real_distribution<> power(5, 10);
	float explosionPower = static_cast<float>(power(engine)) / 60;

	//�����͂��d�͂ɕt����
	SetGravity(-explosionPower);

	//�����蔻��̏�����
	GetCollider()->Initialize(
		GetPosition(),
		GetRotate(),
		GetPartModel()->meshes[0]->boundingBox.Extents
	);
	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Initialize();
	}
}

void StreetLightConnection::Update(const float& elapsedTime, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
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
		if (playerPart->GetSurvival())	playerPart->Update(elapsedTime, GetPosition(), GetRotate());
		else							playerPart->Explosion(elapsedTime);
	}
}
void StreetLightConnection::Explosion(const float& elapsedTime)
{
	//�A�j���[�V�����𒴂�����X�V���Ȃ�
	if (GetTimer() >= Bench::ANIMATION_TIME)
		return;

	//���Ԃ��v��
	SetTimer(GetTimer() + elapsedTime);
	DirectX::SimpleMath::Vector3 position = GetPosition();

	//�����_���ȕ���
	position += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, 0, EXPLOSIVE_RANDOM_POWER), GetRandomRotate());

	////�j�󂳂������ɔ�΂�(���˃x�N�g��)
	//position += -GetReflectionVector() * EXPLOSIVE_POWER;

	//�d�͂�����
	SetGravity(GetGravity() + FALL_SPEED_ACCELERATION);

	//�L�����W�ɏd�͂�����
	position.y -= GetGravity();

	//�����̃N�I�[�^�j�I����]
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::Identity;
	q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(EXPLOSIVE_ROTATE));
	q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(EXPLOSIVE_ROTATE));

	SetPosition(position);

	//�����蔻��̍X�V
	GetCollider()->Update(
		GetPosition(),
		GetRotate()
	);
	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Explosion(elapsedTime);
	}

	//if (GetPosition().y <= 0)
	//	SetPosition(DirectX::SimpleMath::Vector3(GetPosition().x, 0, GetPosition().z));
	//else
	SetRotate(q * GetRotate());

}

void StreetLightConnection::Render()
{
	//�A�j���[�V�����𒴂�����`�悵�Ȃ�
	if (GetTimer() >= Bench::ANIMATION_TIME)
		return;

	//���E�ɓ����Ă��邩
	if (Draw::GetInstance()->VisibilityRange(GetPosition(), 10))
		return;

	//�X�P�[�����O�A�ʒu�����A��]��������
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

	// ��s�@�̕`��
	Draw::GetInstance()->ShadowMapRenderNoPicture(GetPartModel(), world);

	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Render();
	}
}


void StreetLightConnection::Finalize()
{
}
