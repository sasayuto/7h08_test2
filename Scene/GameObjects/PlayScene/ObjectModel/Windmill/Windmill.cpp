#include "pch.h"
#include"Windmill.h"
#include <math.h>
#include<random>
using namespace DirectX;

#include"WindmillParts/WindmillPartFactory.h"


Windmill::Windmill():
	m_position(SimpleMath::Vector3::Zero),
	m_rotate(SimpleMath::Quaternion::Identity)
{
}

Windmill::~Windmill()
{
}

void Windmill::Initialize()
{
	AddParts(WindmillPartFactory::CreateWindmillFoundation(nullptr,m_position,m_rotate));
	//当たり判定を生成
	m_roughCollider = std::make_unique<Collider::Sphere>();

	//大まかな当たり判定に位置と半径をセット
	GetRoughCollider()->SetPosition(GetPosition()+SimpleMath::Vector3(0,12,0));

	//対角線の半分
	GetRoughCollider()->SetRadius(15);
	for (auto& parts : m_parts)
	{
		parts->Initialize();
	}
}

void Windmill::Update()
{	
	for (auto& parts : m_parts)
	{
		parts->Update(m_position,m_rotate);
	}

}

void Windmill::Render()
{		//スケーリング、位置調整、回転をさせる
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotate());

	world *= SimpleMath::Matrix::CreateTranslation(GetPosition());

	////Draw::GetInstance()->TestSphereModel(m_roughCollider->GetRadius(), m_roughCollider->GetPosition(), GetRotate());

	for (auto& parts : m_parts)
	{
		parts->Render();
	}
}

void Windmill::RenderShadowTex()
{		//スケーリング、位置調整、回転をさせる
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotate());

	world *= SimpleMath::Matrix::CreateTranslation(GetPosition());

	////Draw::GetInstance()->TestSphereModel(m_roughCollider->GetRadius(), m_roughCollider->GetPosition(), GetRotate());

	for (auto& parts : m_parts)
	{
		parts->RenderShadowTex();
	}
}

void Windmill::SetpositionRandam(const float& min, const float& max)
{
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> distance(min, max);

	float x = static_cast<float>(distance(engine));
	float z = static_cast<float>(distance(engine));

	m_position = SimpleMath::Vector3(x, 0, z);
	m_rotate = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, x);
}
