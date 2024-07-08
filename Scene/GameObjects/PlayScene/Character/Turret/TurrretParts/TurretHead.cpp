#include "pch.h"
#include"TurretHead.h"
#include"TurretPartFactory.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include<random>

const float TurretHead::FALL_SPEED_ACCELERATION	(0.12f / 60);	//�����̉����x			(m/s)
const float TurretHead::EXPLOSIVE_ROTATE			(120.0f / 60);	//���f���̉�]�̑���	(��/s�j
const float TurretHead::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float TurretHead::EXPLOSIVE_POWER(2.0f / 60);		//�����̉��̃p���[		(m/s)
const int TurretHead::MAX_HP(5000);	//HP


TurretHead::TurretHead(BulletManager* bulletManager,
	ITurretComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	TurretComponent(
		bulletManager,
		parent,
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, 14.67f, -1.4f), angle),
		angle
	),
	m_headAngle(DirectX::SimpleMath::Quaternion::Identity)
{

	//���f�����Z�b�g
	SetPartModel(Resources::GetInstance()->GetTurretHeadModel());
	AddPart(TurretPartFactory::CreateTurretCancer_Middle(bulletManager, this, GetPosition(), GetRotate()));
	AddPart(TurretPartFactory::CreateTurretCancer_Right(bulletManager, this, GetPosition(), GetRotate()));
	AddPart(TurretPartFactory::CreateTurretCancer_Left(bulletManager, this, GetPosition(), GetRotate()));
	//�����蔻��̏�����
	//����ADD���������Ԃ𓖂��蔻����X�V����Ƃ��Ɏg���̂Ŋo���Ă�����
	GetCollider()->AddCollider(
		Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
			GetPosition(),
			GetRotate(),
			DirectX::SimpleMath::Vector3::Zero,
			DirectX::SimpleMath::Quaternion::Identity,
			GetPartModel()->meshes[0]->boundingBox.Extents
		)
	);
	GetCollider()->AddCollider(
		Collider::MultipleHitDeterminationFactory::CreateSphereCollider(
			GetPosition(),
			DirectX::SimpleMath::Vector3(0, -5, 0),
			14
		)
	);

}

TurretHead::~TurretHead()
{

}

void TurretHead::Initialize()
{
	//360�x�����_���ȕ������擾
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> dist(0, 6.28f);
	float explosionSpeedX = static_cast<float>(dist(engine));

	//�����_���ȉ�]���Z�b�g
	SetRandomRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, explosionSpeedX));
	
	//HP���Z�b�g
	SetHp(MAX_HP);
	//�����͂������_���ɂ���
	std::uniform_real_distribution<> power(5, 10);
	float explosionPower = static_cast<float>(power(engine)) / 60;

	//�����͂��d�͂ɕt����
	SetGravity(-explosionPower);

	//�����Ă��Ԃɂ���
	SetSurvival(true);

	//timer��������
	SetTimer(0.0f);

	////�����蔻��̏�����
	//GetCollider()->Initialize(
	//	GetPosition(),
	//	GetRotate(),
	//	GetPartModel()->meshes[0]->boundingBox.Extents
	//);

	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Initialize();
	}
	m_AngleSpeed = 0;
}

void TurretHead::Update(const float& elapsedTime, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//HP���O�ȉ���������E��
	if (GetHp() < 0.0f)
		SetSurvival(false);

	//�e�������Ȃ�����X�V���Ȃ�//
	//�e�̈ʒu�ƍ��킹��
	SetPosition(position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, 14.67f, -1.4f), angle));
	
	m_AngleSpeed += 0.001f;
	m_AngleSpeed *= 0.99f;
	//����X����]�����
	DirectX::SimpleMath::Quaternion headAngleX =
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3::UnitY,
			DirectX::XMConvertToRadians(m_AngleSpeed)
		);
	m_headAngle = headAngleX * m_headAngle;

	//�e�̉�]�ƍ��킹��
	SetRotate(m_headAngle * angle);

	//�����蔻��̍X�V
	GetCollider()->AllUpdate(
		GetPosition(),
		GetRotate()
	);

	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		if (playerPart->GetSurvival())	playerPart->Update(elapsedTime, GetPosition(), GetRotate());
		else							playerPart->Explosion(elapsedTime);
	}
}
void TurretHead::Explosion(const float& elapsedTime)
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

	SetRotate(q * GetRotate());
	SetPosition(position);

	//�����蔻��̍X�V
	GetCollider()->AllUpdate(
		GetPosition(),
		GetRotate()
	);
	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Explosion(elapsedTime);
	}
}

void TurretHead::Render()
{
	//�A�j���[�V�����𒴂�����`�悵�Ȃ�
	if (GetTimer() >= Bench::ANIMATION_TIME)
		return;

	//�X�P�[�����O�A�ʒu�����A��]��������
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

	// ��s�@�̕`��
	Draw::GetInstance()->Render(GetPartModel(), world);
	GetCollider()->Render(GetRotate());
	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Render();
	}
}


void TurretHead::Finalize()
{
}