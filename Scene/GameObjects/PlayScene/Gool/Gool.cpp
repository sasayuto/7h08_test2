#include "pch.h"
#include"Gool.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include<random>
using namespace DirectX;



Gool::Gool() :
	m_position(SimpleMath::Vector3::Zero),
	m_scale(SimpleMath::Vector3(10.0f,10.0f,10.0f)),
	m_goolModel(Resources::GetInstance()->GetGoolModel()), 
	m_sceneFlag(false)
{
}

Gool::~Gool()
{

}

void Gool::Initialize()
{
	m_position = SimpleMath::Vector3(0.0f, 0.0f, 50.0f);
}

void Gool::Update(Player* player)
{
	//
	if (HitCheck_Sphere2Sphere(player->GetPosition(), 1))
	{
		m_sceneFlag = true;
	}
}

void Gool::Render()
{
	//�X�P�[�����O�A�ʒu�����A��]��������
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	world *= SimpleMath::Matrix::CreateScale(m_scale);
	world *= SimpleMath::Matrix::CreateTranslation(m_position);

	// ��s�@�̕`��
	Draw::GetInstance()->Render(m_goolModel, world);

}

bool Gool::HitCheck_Sphere2Sphere(const DirectX::SimpleMath::Vector3& Center, const float& Radius)
{
	// 2�̋��̒��S�̊Ԃ̋����̕������v�Z
	SimpleMath::Vector3 d = m_position - Center;
	float distSq = d.Dot(d);
	// �������������������������a�̍��v�����������ꍇ�ɋ��͌������Ă���
	float radiusSum = m_scale.x + Radius;
	return distSq <= radiusSum * radiusSum;
}


