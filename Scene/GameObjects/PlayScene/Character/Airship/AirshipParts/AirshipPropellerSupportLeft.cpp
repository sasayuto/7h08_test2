#include "pch.h"
#include"AirshipPropellerSupportLeft.h"
#include"AirshipPartFactory.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include<random>

const float AirshipPropellerSupportLeft::FALL_SPEED_ACCELERATION	(0.12f / 60);	//�����̉����x			(m/s)
const float AirshipPropellerSupportLeft::EXPLOSIVE_ROTATE			(120.0f / 60);	//���f���̉�]�̑���	(��/s�j
const float AirshipPropellerSupportLeft::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float AirshipPropellerSupportLeft::EXPLOSIVE_POWER(2.0f / 60);		//�����̉��̃p���[		(m/s)


AirshipPropellerSupportLeft::AirshipPropellerSupportLeft(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	AirshipComponent(parent, position, angle)
{
	AddPart(AirshipPartFactory::CreateAirshipPropellerLeft(parent, position, angle));
	//���f�����Z�b�g
	SetPartModel(Resources::GetInstance()->GetAirshipPropellerSupportLeftModel());
}

AirshipPropellerSupportLeft::~AirshipPropellerSupportLeft()
{

}

void AirshipPropellerSupportLeft::Initialize()
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

	//�����蔻��̏�����
	GetCollider()->Initialize(
		GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		GetRotate(),
		GetPartModel()->meshes[0]->boundingBox.Extents
	);
}

void AirshipPropellerSupportLeft::Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{	
	//���f���ʒu����
	SetPosition(DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(-4.65f, -2.8f, 18.6f), angle));

	//�e�̈ʒu�ƍ��킹��
	SetPosition(position + GetPosition());

	//�e�̉�]�ƍ��킹��
	SetRotate(angle);

	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Update(GetPosition(), GetRotate());
	}

	//�����蔻��̍X�V
	GetCollider()->Update(
		GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		GetRotate()
		);
}

void AirshipPropellerSupportLeft::Render()
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
}

void AirshipPropellerSupportLeft::Explosion()
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

void AirshipPropellerSupportLeft::Finalize()
{
}

void AirshipPropellerSupportLeft::Speed()
{
	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Speed();
	}
}

