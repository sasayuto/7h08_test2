#include "pch.h"
#include"Objects.h"
#include <math.h>
#include<random>

using namespace DirectX;



Objects::Objects() :
	m_position(SimpleMath::Vector3::Zero),
	m_objectsModel(nullptr),
	m_rotate(SimpleMath::Quaternion::Identity),
	m_collider(nullptr),
	m_world(DirectX::SimpleMath::Matrix::Identity)
{
	//“–‚½‚è”»’è‚ğ¶¬
	m_collider = std::make_unique<Collider::MultipleHitDetermination>();

	//“–‚½‚è”»’è‚ğ¶¬
	m_roughCollider = std::make_unique<Collider::Sphere>();
}

Objects::~Objects()
{

}

void Objects::Initialize()
{

	
		m_world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotate());

	m_world *= SimpleMath::Matrix::CreateTranslation(GetPosition());

}

void Objects::Update()
{	
}

void Objects::Render()
{
	//m_collider->Render(GetRotate());
	Draw::GetInstance()->ShadowMapRender(GetObjectsModel(), m_world);


}

void Objects::RenderShadowTex()
{
	//m_collider->Render(GetRotate());
	Draw::GetInstance()->ShadowMapTexCreate(GetObjectsModel(), m_world);

}

void Objects::SetpositionRandam(const float& min, const float& max)
{
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> distance(min, max);

	float x = static_cast<float>(distance(engine));
	float z = static_cast<float>(distance(engine));

	m_position = SimpleMath::Vector3(x, 4, z);
	m_rotate = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, x);
}
