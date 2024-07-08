#include "pch.h"
#include"WheelSupport.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include<random>
#include"Player/PlayerPartFactory.h"


using namespace DirectX;

const float WheelSupport::FALL_SPEED_ACCELERATION	(0.12f / 60);	//�����̉����x			(m/s)
const float WheelSupport::EXPLOSIVE_ROTATE			(120.0f / 60);	//���f���̉�]�̑���	(��/s�j
const float WheelSupport::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float WheelSupport::EXPLOSIVE_POWER(5.0f / 60);				//�����̉��̃p���[		(m/s)


WheelSupport::WheelSupport(IPlayerComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	PlayerComponent(parent, position, angle)
{ 
	//���f�����Z�b�g
	SetPartModel(Resources::GetInstance()->GetWheelSupportModel());

	//�����蔻��̏�����
	GetCollider()->Initialize(
		GetPosition(),
		GetRotate(),
		GetPartModel()->meshes[0]->boundingBox.Extents
	);
	//�v���C���[�ɉH��ǉ�����
	AddPart(PlayerPartFactory::CreatePlayerLeftTire(this, GetPosition(), GetRotate()));
	//�v���C���[�ɉH��ǉ�����
	AddPart(PlayerPartFactory::CreatePlayerRightTire(this, GetPosition(), GetRotate()));

}

WheelSupport::~WheelSupport()
{

}

void WheelSupport::Initialize(const DirectX::SimpleMath::Vector3& reflectionVector)
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

	for (auto& playerPart : GetParts())
	{
		// �p�[�c���X�V����
		playerPart->Initialize(reflectionVector);
	}
}

void WheelSupport::Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//���f���ʒu����
	SetPosition(SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, -0.135f, -0.31f), angle));

	//�e�̈ʒu�ƍ��킹��
	SetPosition(position+GetPosition());

	//�e�̉�]�ƍ��킹��
	SetRotate(angle);
	for (auto& playerPart : GetParts())
	{
		// �p�[�c���X�V����
		playerPart->Update(GetPosition(), GetRotate());
	}

	//�����蔻��̍X�V
	GetCollider()->Update(
		GetPosition(),
		GetRotate()
	);
}

void WheelSupport::Render()
{
	//�X�P�[�����O�A�ʒu�����A��]��������
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	world *= SimpleMath::Matrix::CreateTranslation(GetPosition());

	// ��s�@�̕`��
	Draw::GetInstance()->ShadowMapRenderNoPicture(GetPartModel(), world);

	SimpleMath::Vector3 a(GetPartModel()->meshes[0]->boundingBox.Center);
	//Draw::GetInstance()->TestCubeModel(
	//	GetPartModel()->meshes[0]->boundingBox.Extents, 
	//	GetPosition(),
	//	GetRotate()
	//);

	for (auto& playerPart : GetParts())
	{
		// �p�[�c���X�V����
		playerPart->Render();
	}
}

void WheelSupport::Explosion()
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

	for (auto& playerPart : GetParts())
	{
		// �p�[�c���X�V����
		playerPart->Explosion();
	}

	//�����蔻��̍X�V
	GetCollider()->Update(
		GetPosition(),
		GetRotate()
	);
}
void WheelSupport::Finalize()
{
}

void WheelSupport::Speed()
{
	for (auto& playerPart : GetParts())
	{
		// �p�[�c���X�V����
		playerPart->Speed();
	}
}


