#include "pch.h"
#include"AirshipPropellerRight.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include<random>

const float AirshipPropellerRight::FALL_SPEED_ACCELERATION	(0.12f / 60);	//�����̉����x			(m/s)
const float AirshipPropellerRight::EXPLOSIVE_ROTATE			(120.0f / 60);	//���f���̉�]�̑���	(��/s�j
const float AirshipPropellerRight::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float AirshipPropellerRight::EXPLOSIVE_POWER(2.0f / 60);		//�����̉��̃p���[		(m/s)

const float PROPELLER_ACCELERATION(60.0f / 60);//�v���y���̉�]�̉����x(��/s�j
const float PROPELLER_COOL_TIME(0.95f);	//��C��R


AirshipPropellerRight::AirshipPropellerRight(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	AirshipComponent(parent, position, angle),
	m_velcity(DirectX::SimpleMath::Vector3::Zero),
	m_angle(DirectX::SimpleMath::Vector3::Zero),
	m_smokeEffect(nullptr)
{

	//���f�����Z�b�g
	SetPartModel(Resources::GetInstance()->GetAirshipPropellerLeftModel());
}

AirshipPropellerRight::~AirshipPropellerRight()
{

}

void AirshipPropellerRight::Initialize()
{	
	//360�x�����_���ȕ������擾
	std::random_device seed;
	std::default_random_engine engine(seed());

	//�����_���ȕ��������
	std::uniform_real_distribution<> dist(0, 6.28f);
	float explosionSpeedX = static_cast<float>(dist(engine));

	//�����_���ȉ�]���Z�b�g
	SetRandomRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, explosionSpeedX));

	//�L���̉�]���Z�b�g
	SetKillRotate(GetRotate());

	//�����͂������_���ɂ���
	std::uniform_real_distribution<> power(5, 10);
	float explosionPower = static_cast<float>(power(engine)) / 60;

	//�����͂��d�͂ɕt����
	SetGravity(-explosionPower);

	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Initialize();
	}
	m_smokeEffect = std::make_unique<SmokeEffect>();

	m_smokeEffect->Initialize();

	//�����蔻��̏�����
	GetCollider()->Initialize(
		GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		GetRotate(),
		GetPartModel()->meshes[0]->boundingBox.Extents
	);
}

void AirshipPropellerRight::Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{	
	//�����x�ɋ�C��R��������
	m_velcity.z *= PROPELLER_COOL_TIME;

	//�v���y�����̊p�x�ɑ��x�𑫂�
	m_angle.z += m_velcity.z;

	//���f���ʒu����
	SetPosition(DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(1.14f, -1.0f, 1.6f), angle));

	//�e�̈ʒu�ƍ��킹��
	SetPosition(position + GetPosition());

	//�N�I�[�^�j�I����]�����
	DirectX::SimpleMath::Quaternion q;
	q = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(m_angle.z));
	//�e�̉�]�ƍ��킹��
	SetRotate(q * angle);

	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Update(GetPosition(), GetRotate());
	}

	m_smokeEffect->Update(0.0166f, GetPosition(), GetRotate());
	//�����蔻��̍X�V
	GetCollider()->Update(
		GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		GetRotate()
		);
}

void AirshipPropellerRight::Render()
{

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
	m_smokeEffect->Render();

}

void AirshipPropellerRight::Explosion()
{
	using namespace DirectX;

	SimpleMath::Vector3 position = GetPosition();

	//�����_���ȕ���
	position += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0, 0, EXPLOSIVE_RANDOM_POWER), GetRandomRotate());

	//�j�󂳂������ɔ�΂�
	position += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0, 0, EXPLOSIVE_POWER), GetKillRotate());

	//�d�͂�����
	SetGravity(GetGravity() + FALL_SPEED_ACCELERATION);

	//�L�����W�ɏd�͂�����
	position.y -= GetGravity();

	//�����̃N�I�[�^�j�I����]
	SimpleMath::Quaternion q = SimpleMath::Quaternion::Identity;
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, XMConvertToRadians(EXPLOSIVE_ROTATE));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(EXPLOSIVE_ROTATE));

	SetRotate(q * GetRotate());
	SetPosition(position);

	for (auto& playerPart : GetParts())
	{
		// �p�[�c���X�V����
		playerPart->Explosion();
	}

	//�����蔻��̍X�V
	GetCollider()->Update(
		GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		GetRotate()
	);

}

void AirshipPropellerRight::Finalize()
{
}

void AirshipPropellerRight::Speed()
{
	//�����x�v�Z
	m_velcity.z += PROPELLER_ACCELERATION;
	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Speed();
	}
}


