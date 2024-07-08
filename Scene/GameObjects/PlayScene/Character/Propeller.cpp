#include "pch.h"
#include"Propeller.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include<random>


using namespace DirectX;

const float Propeller::FALL_SPEED_ACCELERATION(0.08f / 60);	//�����̉����x			(m/s)
const float Propeller::PROPELLER_ACCELERATION(60.0f / 60);//�v���y���̉�]�̉����x(��/s�j
const float Propeller::PROPELLER_COOL_TIME(0.95f);	//��C��R
const float Propeller::EXPLOSIVE_ROTATE(120.0f / 60);		//���f���̉�]�̑���(��/s�j
const float Propeller::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float Propeller::EXPLOSIVE_POWER(5.0f / 60);			//�����̉��̃p���[		(m/s)


Propeller::Propeller(IPlayerComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	PlayerComponent(parent, position, angle),
	m_angle(angle),
	m_velcity(SimpleMath::Vector3::Zero)
{
	//���f�����Z�b�g
	SetPartModel(Resources::GetInstance()->GetPropellerModel());

	//�����蔻��̏�����
	GetCollider()->Initialize(
		GetPosition(),
		GetRotate(),
		GetPartModel()->meshes[0]->boundingBox.Extents
	);
}

Propeller::~Propeller()
{

}

void Propeller::Initialize(const DirectX::SimpleMath::Vector3& reflectionVector)
{
	//�e�̔��˃x�N�g�����Z�b�g�i�ŏ��͔��˃x�N�g���������Ȃ̂Łj
	SetReflectionVector(reflectionVector);

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

}

void Propeller::Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�����x�ɋ�C��R��������
	m_velcity.z *= PROPELLER_COOL_TIME;

	//�v���y�����̊p�x�ɑ��x�𑫂�
	m_angle.z += m_velcity.z;

	//���f���ʒu����
	SetPosition(SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.10f, -0.76f), angle));

	//�e�̈ʒu�ƍ��킹��
	SetPosition(position + GetPosition());

	//�N�I�[�^�j�I����]�����
	SimpleMath::Quaternion q;
	q = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, XMConvertToRadians(m_angle.z));
	//�e�̉�]�ƍ��킹��
	SetRotate(q * angle);

	//�����蔻��̍X�V
	GetCollider()->Update(
		GetPosition(),
		GetRotate()
	);
}


void Propeller::Render()
{
	//�X�P�[�����O�A�ʒu�����A��]��������
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	world *= SimpleMath::Matrix::CreateTranslation(GetPosition());

	// ��s�@�̕`��
	Draw::GetInstance()->ShadowMapRenderNoPicture(GetPartModel(), world);

	//Draw::GetInstance()->TestCubeModel(
	//	GetPartModel()->meshes[0]->boundingBox.Extents,
	//	GetPosition(),
	//	GetRotate()
	//);
}

void Propeller::Explosion()
{
	SimpleMath::Vector3 position = GetPosition();
	DirectX::SimpleMath::Vector3 move = DirectX::SimpleMath::Vector3::Zero;
	//�����_���ȕ���
	move += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0, 0, EXPLOSIVE_RANDOM_POWER), GetRandomRotate());

	//�j�󂳂������ɔ�΂�(���˃x�N�g��)
	move += -GetReflectionVector() * EXPLOSIVE_POWER;

	//�d�͂�����
	SetGravity(GetGravity() + FALL_SPEED_ACCELERATION);

	//�L�����W�ɏd�͂�����
	move.y -= GetGravity();

	SetMove(move);
	position += move;

	//�����̃N�I�[�^�j�I����]
	SimpleMath::Quaternion q = SimpleMath::Quaternion::Identity;
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, XMConvertToRadians(EXPLOSIVE_ROTATE));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(EXPLOSIVE_ROTATE));

	SetRotate(q * GetRotate());
	SetPosition(position);

	//�����蔻��̍X�V
	GetCollider()->Update(
		GetPosition(),
		GetRotate()
	);
}

void Propeller::Finalize()
{
}

void Propeller::Speed()
{
	//�����x�v�Z
	m_velcity.z += PROPELLER_ACCELERATION;
}


