#include "pch.h"
#include"StreetLight.h"
#include <math.h>
#include<random>
using namespace DirectX;
#include"StreetLightManager.h"
#include"StreetLightParts/StreetLightPartFactory.h"

const float StreetLight::ANIMATION_TIME(10.0f);//�������[�V�����̎���

StreetLight::StreetLight():
	m_position(SimpleMath::Vector3::Zero),
	m_rotate(SimpleMath::Quaternion::Identity),
	m_survival(false),
	m_killCountFlag(false),
	m_allSurvivalFlag(true),
	m_world(DirectX::SimpleMath::Matrix::Identity)
{
}

StreetLight::~StreetLight()
{

}

void StreetLight::Initialize(BulletManager* bulletManager, StreetLightManager* streetLightManager)
{
	m_pStreetLight = Resources::GetInstance()->GetStreetLightModel();
	m_pStreetLightManager = streetLightManager;
	m_pBulletManager = bulletManager;

	AddParts(StreetLightPartFactory::CreateStreetLightFoundation(nullptr, m_position, m_rotate));
	//�����蔻��𐶐�
	m_roughCollider = std::make_unique<Collider::Sphere>();

	//��܂��ȓ����蔻��Ɉʒu�Ɣ��a���Z�b�g
	GetRoughCollider()->SetPosition(GetPosition()+DirectX::SimpleMath::Vector3(0,3,0));

	//�Ίp���̔���
	GetRoughCollider()->SetRadius(5);
	for (auto& parts : m_parts)
	{
		parts->Initialize();
	}
	//�X�P�[�����O�A�ʒu�����A��]��������
	
	m_world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	m_survival = true;
}

void StreetLight::Update(const float& elapsedTime)
{	
	//�p�[�c�������Ă��邩
	bool PartsSurvival = false;
	for (auto& parts : m_parts)
	{
		if (parts->GetSurvival())
		{
			parts->Update(elapsedTime, m_position, m_rotate);
			PartsSurvival = true;
		}
		else
			parts->Explosion(elapsedTime);
	}
	//�p�[�c�����ׂĎ��񂾂�A�j���[�V�����̎��Ԃ�}��
	if (!PartsSurvival)
	{
		//�L���J�E���g���ĂȂ������炷��
		if(!m_killCountFlag)
		{
			m_pStreetLightManager->SetStreetLightKillCount(m_pStreetLightManager->GetStreetLightKillCount() + 1);
			//�J�E���g������true�ɂ���
			m_killCountFlag = true;
		}

		m_timer += elapsedTime;
		//�A�j���[�V�������I�������Ȃ���
		if (m_timer >= ANIMATION_TIME)
			m_survival = false;
	}

	//��ł����Ă��邩
	for (auto& parts : m_parts)
	{
		if (!parts->SurvivalCheck())
		{
			m_allSurvivalFlag = false;
			break;
		}
	}
	if (m_pBulletManager)
		m_pBulletManager->CheckHitDestructionObjects(this);
}

void StreetLight::Render()
{
	if (m_allSurvivalFlag)
	{
		//���E�ɓ����Ă��邩
		if (Draw::GetInstance()->VisibilityRange(GetPosition(), 10))
			return;

		// ��s�@�̕`��
		Draw::GetInstance()->ShadowMapRenderNoPicture(m_pStreetLight, m_world);
	}
	else
		for (auto& parts : m_parts)
			parts->Render();
}

void StreetLight::RenderShadowTex()
{
	if (m_allSurvivalFlag)
		// ��s�@�̕`��
		Draw::GetInstance()->ShadowMapTexCreateNoPicture(m_pStreetLight, m_world);
	else
		for (auto& parts : m_parts)
			parts->RenderShadowTex();
}

void StreetLight::SetpositionRandam(const float& min, const float& max)
{
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> distance(min, max);

	float x = static_cast<float>(distance(engine));
	float z = static_cast<float>(distance(engine));

	m_position = SimpleMath::Vector3(x, 0, z);
	m_rotate = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, x);
}
