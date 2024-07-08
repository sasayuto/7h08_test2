#include "pch.h"
#include"Item.h"
#include<random>
using namespace DirectX;



Item::Item() :
	m_position(SimpleMath::Vector3::Zero),
	m_scale(SimpleMath::Vector3::One),
	m_survival(false),
	m_pSupplyPointModel(nullptr),
	m_rotate(DirectX::SimpleMath::Quaternion::Identity),
	m_world(DirectX::SimpleMath::Matrix::Identity)
{
}

Item::~Item()
{

}

void Item::Initialize()
{

	//�����蔻��𐶐�
	m_collider = std::make_unique<Collider::Sphere>();

	//�G�������Ă��邩
	m_survival = true;

	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	m_collider->SetPosition(m_position);
	m_collider->SetRadius(m_scale.x);

	//�X�P�[�����O�A�ʒu�����A��]��������
	m_world *= SimpleMath::Matrix::CreateScale(m_scale);
	m_world *= SimpleMath::Matrix::CreateFromQuaternion(m_rotate);
	m_world *= SimpleMath::Matrix::CreateTranslation(m_position);

}

void Item::Update(const float& elapsedTime)
{
	elapsedTime;
}

void Item::Render()
{
	//�X�P�[�����O�A�ʒu�����A��]��������
	Draw::GetInstance()->ShadowMapRenderNoPicture(m_pSupplyPointModel, m_world);
}
void Item::RenderShadowTex()
{
	//m_collider->Render(GetRotate());
	Draw::GetInstance()->ShadowMapTexCreateNoPicture(GetSupplyPointModel(), m_world);

}

void Item::Finalize()
{
}

void Item::Recovery(Player* player)
{
	player;
}

void Item::SetpositionRandam(const float& min, const float& max)
{
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> dist(min, max);
	std::uniform_real_distribution<> distY(0, 100);

	float x = static_cast<float>(dist(engine));
	float y = static_cast<float>(distY(engine));
	float z = static_cast<float>(dist(engine));
	m_position = SimpleMath::Vector3(x, y, z);

}
