#include "pch.h"
#include"TurretCancer_Middle.h"
#include"TurretPartFactory.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"
#include<random>

const float TurretCancer_Middle::FALL_SPEED_ACCELERATION	(0.12f / 60);	//�����̉����x			(m/s)
const float TurretCancer_Middle::EXPLOSIVE_ROTATE			(120.0f / 60);	//���f���̉�]�̑���	(��/s�j
const float TurretCancer_Middle::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float TurretCancer_Middle::EXPLOSIVE_POWER(2.0f / 60);		//�����̉��̃p���[		(m/s)
const float TurretCancer_Middle::BULLET_COOL_TIME(2.0f);		//���N�[���^�C��	(s)
const int TurretCancer_Middle::MAX_HP(1000);	//HP


TurretCancer_Middle::TurretCancer_Middle(BulletManager* bulletManager,
	ITurretComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	TurretComponent(
		bulletManager,
		parent,
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, -1.55f, -8.33f), angle),
		angle
	),
	m_pBulletManager(bulletManager),
	m_bulletCoolTime(0),
	m_CancerAngle(DirectX::SimpleMath::Quaternion::Identity)
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
			DirectX::SimpleMath::Quaternion::Identity,
			GetPartModel()->meshes[0]->boundingBox.Extents
		)
	);

}

TurretCancer_Middle::~TurretCancer_Middle()
{

}

void TurretCancer_Middle::Initialize()
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
	m_CancerAngle = DirectX::SimpleMath::Quaternion::Identity;
}

void TurretCancer_Middle::Update(const float& elapsedTime, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//HP���O�ȉ���������E��
	if (GetHp() < 0.0f)
		SetSurvival(false);

	//�e�������Ȃ�����X�V���Ȃ�//
	//�e�̈ʒu�ƍ��킹��
	SetPosition(position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, -1.55f, -8.33f), angle));
	
	if (b >= 4) {
		h = false;
	}
	if (b <= -4) {
		h = true;
	}
	if(h)b += 0.05f;
	else b -= 0.05f;
	DirectX::SimpleMath::Quaternion cancerAngleY =
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3::UnitX,
			DirectX::XMConvertToRadians(b)
		);

	m_CancerAngle = cancerAngleY * m_CancerAngle;
	//�e�̉�]�ƍ��킹��
	SetRotate(m_CancerAngle * angle);
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
void TurretCancer_Middle::Explosion(const float& elapsedTime)
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
		GetPosition(),
		GetRotate()
	);

	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Explosion(elapsedTime);
	}
}

void TurretCancer_Middle::Render()
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


void TurretCancer_Middle::Finalize()
{
}