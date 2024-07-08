#include "pch.h"
#include"Palace.h"
#include<random>
using namespace DirectX;



Palace::Palace() :
	m_position(SimpleMath::Vector3::Zero),
	m_pModel(Resources::GetInstance()->GetPalaceModel()),
	m_rotate(DirectX::SimpleMath::Quaternion::Identity)
{
}

Palace::~Palace()
{

}

void Palace::Initialize()
{

}

void Palace::Update(const float& elapsedTime)
{

}

void Palace::Render()
{
	//スケーリング、位置調整、回転をさせる
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	world *= SimpleMath::Matrix::CreateFromQuaternion(m_rotate);
	world *= SimpleMath::Matrix::CreateTranslation(m_position);
	Draw::GetInstance()->ShadowMapRender(m_pModel, world);
}

void Palace::RenderShadowTex()
{
	//スケーリング、位置調整、回転をさせる
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	world *= SimpleMath::Matrix::CreateFromQuaternion(m_rotate);
	world *= SimpleMath::Matrix::CreateTranslation(m_position);
	//m_collider->Render(GetRotate());
	Draw::GetInstance()->ShadowMapTexCreate(m_pModel, world);

}

void Palace::Finalize()
{
}
