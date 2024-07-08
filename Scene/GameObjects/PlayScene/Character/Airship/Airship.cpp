#include "pch.h"
#include"Airship.h"
#include <math.h>
#include<random>
#include"AirshipParts/AirshipPartFactory.h"
#include"AirshipParts/AirshipBody.h"

using namespace DirectX;
Airship::Airship(const int& Hp, const int& Fuel, const int& offensivePower) :
	m_survival(false),
	//m_pCurrentState(nullptr),
	//m_AirshipKillMotion(nullptr),
	//m_AirshipMotion(nullptr),
	m_position(SimpleMath::Vector3::Zero),
	m_velcity(SimpleMath::Vector3::Zero),
	m_rotate(SimpleMath::Quaternion::Identity),
	m_bulletCoolTime(),
	m_HP(Hp),
	m_fuel(Fuel),
	m_offensivePower(offensivePower),
	m_speed(),
	m_angle(SimpleMath::Vector3::Zero),
	//m_bulletParent(Bullet::BulletParent::None),
	//m_bulletType(Bullet::BulletType::None),
	m_pBulletManager(nullptr),
	m_gravity()
{
}

Airship::~Airship()
{
}

void Airship::Initialize(
	BulletManager* bulletManager,
	ObjectsManager* objectsManager,
	Player* player
)
{
	player;
	//// �v���C���[�Ƀv���y����ǉ�����
	AddParts(AirshipPartFactory::CreateAirshipBody(nullptr, m_position, m_rotate));

	//��܂��ȓ����蔻��𐶐�
	m_roughCollider = std::make_unique<Collider::Sphere>();

	//�Ίp���̔���
	m_roughCollider->SetRadius(1000);
	m_roughCollider->SetPosition(GetPosition());

	//���̃|�C���^���擾
	m_pBulletManager = bulletManager;

	//�I�u�W�F�N�g�̃|�C���^���擾
	m_pObjectsManager = objectsManager;

	//�G�������Ă��邩
	SetSurvival(true);
}

void Airship::Update(const float& elapsedTime)
{
	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	m_roughCollider->SetPosition(m_position);

	////�����蔻��
	//if (m_pObjectsManager)
	//	m_pObjectsManager->CheckHitAirship(this);

	//if (m_pTreeManager)
	//	m_pTreeManager->CheckHitAirship(this);

	if (m_pBulletManager)
		m_pBulletManager->CheckHitDamegeObjects(this,Bullet::BulletParent::EnemyBullet);

	//���݂̏�Ԃ̍X�V
	m_pCurrentState->Update(elapsedTime);
}

void Airship::Render()
{
	//���݂̏�Ԃ̕`��
	m_pCurrentState->Render();
	//Draw::GetInstance()->TestSphereModel(m_roughCollider->GetRadius(), m_roughCollider->GetPosition(), m_rotate);
}

void Airship::RenderShadowTex()
{
	for (auto& parts : m_parts)
	{
		// �p�[�c���X�V����
		parts->RenderShadowTex();
	}
}

void Airship::Finalize()
{
	//���݂̏�Ԃ̌�n��
	m_pCurrentState->Finalize();
}

void Airship::Damage(const int& damage)
{
	//�_���[�W����
	SetHP(GetHP() - damage);
}

void Airship::SetpositionRandam(const float& min,const float& max)
{
	//�����_���Ȑ��l
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> distance(min, max);

	float x = static_cast<float>(distance(engine));
	float z = static_cast<float>(distance(engine));

	m_position = SimpleMath::Vector3(x, 200, z);
}

void Airship::Reset()
{
}

void Airship::Shot(const float& maxBulletCoolTime)
{
	//�N�[���^�C����
	if (m_bulletCoolTime == 0.0f)
	{
		//����ł�
		m_pBulletManager->Shot(Bullet::BulletType::Type1, Bullet::BulletParent::EnemyBullet, m_position, m_rotate);
		
		//�N�[���^�C�����Z�b�g
		m_bulletCoolTime = maxBulletCoolTime;
	}
}

void Airship::PartsInitialize()
{
	//�p�[�c�̏�����
	for (auto& parts : m_parts)
	{
		// �p�[�c��������
		parts->Initialize();
	}

}

void Airship::PartsUpdate()
{
	//�p�[�c�̍X�V
	for (auto& parts : m_parts)
	{
		// �p�[�c���X�V����
		parts->Update(m_position, m_rotate);
	}
}

void Airship::PartsExplosion()
{
	//�p�[�c�̔���
	for (auto& parts : m_parts)
	{
		// �p�[�c���X�V����
		parts->Explosion();
	}
}

void Airship::PartsMotion()
{
	//�}�[�c�̔R���ɂ�����铮��
	for (auto& parts : m_parts)
	{
		// �p�[�c���X�V����
		parts->Speed();
	}
}

void Airship::PartsCollision()
{
	//for (auto& playerPart : m_PlayerPropellerParts)
	//{
	//	// �p�[�c���X�V����
	//	playerPart->Collision();
	//}

}

void Airship::PartsRender()
{
	//�p�[�c�̕`��
	for (auto& part : m_parts)
	{
		//�p�[�c���X�V����
		part->Render();
	}
}
