#include "pch.h"
#include"AirshipBody.h"
#include"AirshipPartFactory.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include<random>

const float AirshipBody::FALL_SPEED_ACCELERATION	(0.12f / 60);	//�����̉����x			(m/s)
const float AirshipBody::EXPLOSIVE_ROTATE			(120.0f / 60);	//���f���̉�]�̑���	(��/s�j
const float AirshipBody::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float AirshipBody::EXPLOSIVE_POWER(2.0f / 60);		//�����̉��̃p���[		(m/s)


AirshipBody::AirshipBody(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	AirshipComponent(parent, position, angle)
{
	AddPart(AirshipPartFactory::CreateAirshipElevatorLeft(parent, position, angle));
	AddPart(AirshipPartFactory::CreateAirshipElevatorRight(parent, position, angle));
	AddPart(AirshipPartFactory::CreateAirshipRoom_01(parent, position, angle));
	AddPart(AirshipPartFactory::CreateAirshipRoom_02(parent, position, angle));
	AddPart(AirshipPartFactory::CreateAirshipPropellerSupportLeft(parent, position, angle));
	AddPart(AirshipPartFactory::CreateAirshipPropellerSupportRight(parent, position, angle));
	AddPart(AirshipPartFactory::CreateAirshipRudder(parent, position, angle));
	//���f�����Z�b�g
	SetPartModel(Resources::GetInstance()->GetAirshipBodyModel());
}

AirshipBody::~AirshipBody()
{

}

void AirshipBody::Initialize()
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

void AirshipBody::Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�e�̈ʒu�ƍ��킹��
	SetPosition(position);

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

void AirshipBody::Render()
{

	//�X�P�[�����O�A�ʒu�����A��]��������
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

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

void AirshipBody::Explosion()
{
	using namespace DirectX;

	//�ʒu���擾
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

	//��]���Z�b�g
	SetRotate(q * GetRotate());

	//�ʒu���Z�b�g
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

void AirshipBody::Finalize()
{
}

void AirshipBody::Speed()
{
	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Speed();
	}
}

