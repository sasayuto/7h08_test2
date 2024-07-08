#include "pch.h"
#include"Body.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Player/PlayerPartFactory.h"
#include<random>
const float Body::FALL_SPEED_ACCELERATION	(0.12f / 60);	//�����̉����x			(m/s)
const float Body::EXPLOSIVE_ROTATE			(120.0f / 60);	//���f���̉�]�̑���	(��/s�j
const float Body::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float Body::EXPLOSIVE_POWER		(5.0f / 60);		//�����̉��̃p���[		(m/s)


Body::Body(IPlayerComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	PlayerComponent(parent, position, angle)
{
	//�{�f�B�[�ɉH��ǉ�����
	AddPart(PlayerPartFactory::CreatePlayerWing(this, GetPosition(), GetRotate()));
	//�{�f�B�[�Ƀv���y����ǉ�����
	AddPart(PlayerPartFactory::CreatePlayerPro(this, GetPosition(), GetRotate()));
	//�{�f�B�[�ɐK����ǉ�����
	AddPart(PlayerPartFactory::CreatePlayerTail(this, GetPosition(), GetRotate()));
	//�{�f�B�[�ɐK����ǉ�����
	AddPart(PlayerPartFactory::CreatePlayerHorizontalStabilizer(this, GetPosition(), GetRotate()));
	//�{�f�B�[�Ƀz�C�[���T�|�[�g��ǉ�����
	AddPart(PlayerPartFactory::CreatePlayerWheelSupport(this, GetPosition(), GetRotate()));

	//���f�����Z�b�g
	SetPartModel(Resources::GetInstance()->GetBodyModel());

	//�����蔻��̏�����
	GetCollider()->Initialize(
		GetPosition(),
		GetRotate(),
		GetPartModel()->meshes[0]->boundingBox.Extents
	);


}

Body::~Body()
{

}

void Body::Initialize(const DirectX::SimpleMath::Vector3& reflectionVector)
{	
	SetMove(DirectX::SimpleMath::Vector3::Zero);
	//�e�̔��˃x�N�g�����Z�b�g�i�ŏ��͔��˃x�N�g���������Ȃ̂Łj
	SetReflectionVector(reflectionVector);

	//360�x�����_���ȕ������擾
	std::random_device seed;
	std::default_random_engine engine(seed());

	//�����_���ȕ��������
	std::uniform_real_distribution<> dist(0, 6.28f);
	float explosionSpeedX = static_cast<float>(dist(engine));

	//�����_���ȉ�]���Z�b�g
	SetRandomRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, explosionSpeedX));

	//�����͂������_���ɂ���
	std::uniform_real_distribution<> power(5, 10);
	float explosionPower = static_cast<float>(power(engine)) / 60;

	//�����͂��d�͂ɕt����
	SetGravity(-explosionPower);


	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Initialize(reflectionVector);
	}
}

void Body::Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
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
		GetPosition(),
		GetRotate()
	);
}

void Body::Render()
{
	//�X�P�[�����O�A�ʒu�����A��]��������
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

	// ��s�@�̕`��
	Draw::GetInstance()->ShadowMapRenderNoPicture(GetPartModel(), world);

	//Draw::GetInstance()->TestCubeModel(
	//	GetPartModel()->meshes[0]->boundingBox.Extents, 
	//	GetPosition(),
	//	GetRotate()
	//);

		// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Render();
	}
}

void Body::Explosion()
{
	using namespace DirectX;

	SimpleMath::Vector3 position = GetPosition();
	DirectX::SimpleMath::Vector3 move=DirectX::SimpleMath::Vector3::Zero;
	//�����_���ȕ���
	//move += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0, 0, EXPLOSIVE_RANDOM_POWER), GetRandomRotate());

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

	//
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

void Body::Finalize()
{
}

void Body::Speed()
{
	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Speed();
	}
}


