#include"pch.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"

#include"Bullet.h"
using namespace DirectX;

#define BULLET_MAX_SPEED		(150.0f / 60)		//���̍ő�X�s�[�h		(m/s)



Bullet::Bullet(const float& speed, const int& offensivePower, const float& scale):
	m_bulletparent(),
	m_position(SimpleMath::Vector3::Zero),
	m_isActive(),
	m_bulletModel(Resources::GetInstance()->GetBurretModel()),
	m_scale(SimpleMath::Vector3::One* scale),
	m_speed(speed),
	m_offensivePower(offensivePower), m_move()
{
}

Bullet::~Bullet()
{
}


void Bullet::Initialize(const BulletParent& shooterType, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate)
{
	//�I�����ꂽ�L����
	m_bulletparent = shooterType;

	//�ݒ肳�ꂽ�L�����̃|�W�V����������
	m_position = position;

	m_isActive = true;

	//�{�[���̕���
	m_rotate = rotate;

	//�����蔻��𐶐�
	m_collider = std::make_unique<Collider::Sphere>();

	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	m_collider->SetPosition(m_position);
	m_collider->SetRadius(m_scale.x);

}

void Bullet::Update()
{
	//���˂���Ă��邩

	//���̎�ނɂ���čX�V�𕪂���
	//�����x�v�Z

	//�O���ɒ���������
	m_move = SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.0f, -m_speed), m_rotate);

	//�{�[���̈ړ�
	m_position += m_move;

	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	m_collider->SetPosition(m_position);
}

void Bullet::Render()
{
	//�X�P�[�����O�A�ʒu�����A��]��������
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	world *= SimpleMath::Matrix::CreateFromQuaternion(m_rotate);
	world *= SimpleMath::Matrix::CreateScale(m_scale);
	world *= SimpleMath::Matrix::CreateTranslation(m_position);

	// ��s�@�̕`��
	Draw::GetInstance()->ShadowMapRenderNoPicture(m_bulletModel, world);
	//Draw::GetInstance()->TestSphereModel(m_collider->GetRadius(), m_collider->GetPosition());
}
void Bullet::RenderShadowTex()
{
	//�X�P�[�����O�A�ʒu�����A��]��������
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotate());

	world *= SimpleMath::Matrix::CreateTranslation(GetPosition());

	//m_collider->Render(GetRotate());
	Draw::GetInstance()->ShadowMapTexCreateNoPicture(m_bulletModel, world);

}

void Bullet::Finalize()
{


}

