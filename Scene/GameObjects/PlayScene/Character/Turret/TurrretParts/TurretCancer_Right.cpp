#include "pch.h"
#include"TurretCancer_Right.h"
#include"TurretPartFactory.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"
#include<random>

const float TurretCancer_Right::FALL_SPEED_ACCELERATION	(0.12f / 60);	//�����̉����x			(m/s)
const float TurretCancer_Right::EXPLOSIVE_ROTATE			(120.0f / 60);	//���f���̉�]�̑���	(��/s�j
const float TurretCancer_Right::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float TurretCancer_Right::EXPLOSIVE_POWER(2.0f / 60);		//�����̉��̃p���[		(m/s)
const float TurretCancer_Right::BULLET_COOL_TIME(2.0f);		//���N�[���^�C��	(s)
const int TurretCancer_Right::MAX_HP(1000);	//HP


TurretCancer_Right::TurretCancer_Right(BulletManager* bulletManager,
	ITurretComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	TurretComponent(
		bulletManager,
		parent,
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(-4.4f, -1.55f, -8.33f), angle),
		angle
	),
	m_pBulletManager(bulletManager),
	m_bulletCoolTime(0)
{

	//���f�����Z�b�g
	SetPartModel(Resources::GetInstance()->GetTurretCancerModel());

		//�����蔻��̏�����
	//����ADD���������Ԃ𓖂��蔻����X�V����Ƃ��Ɏg���̂Ŋo���Ă�����
	GetCollider()->AddCollider(
		Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
			GetPosition(),
			GetRotate(),
			DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center),
			GetRotate(),
			GetPartModel()->meshes[0]->boundingBox.Extents
		)
	);

}

TurretCancer_Right::~TurretCancer_Right()
{

}

void TurretCancer_Right::Initialize()
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

	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Initialize();
	}
}

void TurretCancer_Right::Update(const float& elapsedTime, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//HP���O�ȉ���������E��
	if (GetHp() < 0.0f)
		SetSurvival(false);

	//�e�������Ȃ�����X�V���Ȃ�//
	//�e�̈ʒu�ƍ��킹��
	SetPosition(position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(-4.4f, -1.55f, -8.33f), angle));
	
	if (b >= 90) {
		h = false;
	}
	if (b <= -90) {
		h = true;
	}
	if(h)b += 1;
	else b -= 1;
	DirectX::SimpleMath::Quaternion q =
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3::UnitX,
			DirectX::XMConvertToRadians(b)
		);
	//�e�̉�]�ƍ��킹��
	SetRotate(q * angle);
	//�����蔻��̍X�V
	GetCollider()->AllUpdate(
		GetPosition(),
		GetRotate()
	);

	m_bulletCoolTime += elapsedTime;
	if (m_bulletCoolTime >= BULLET_COOL_TIME)
	{
		m_pBulletManager->Shot(
			Bullet::BulletType::Turret,
			Bullet::BulletParent::EnemyBullet,
			GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, 0, -4), GetRotate()),
			GetRotate()
		);
		m_bulletCoolTime = 0.0f;
	}

	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		if (playerPart->GetSurvival())	playerPart->Update(elapsedTime, GetPosition(), GetRotate());
		else							playerPart->Explosion(elapsedTime);
	}
}
void TurretCancer_Right::Explosion(const float& elapsedTime)
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
	q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(-EXPLOSIVE_ROTATE));
	q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-EXPLOSIVE_ROTATE));

	SetRotate(q * GetRotate());
	SetPosition(position);

	//�����蔻��̍X�V
	GetCollider()->AllUpdate(
		GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		GetRotate()
	);

	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Explosion(elapsedTime);
	}
}

void TurretCancer_Right::Render()
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


void TurretCancer_Right::Finalize()
{
}