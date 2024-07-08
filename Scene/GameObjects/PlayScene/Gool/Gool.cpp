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
	//スケーリング、位置調整、回転をさせる
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	world *= SimpleMath::Matrix::CreateScale(m_scale);
	world *= SimpleMath::Matrix::CreateTranslation(m_position);

	// 飛行機の描画
	Draw::GetInstance()->Render(m_goolModel, world);

}

bool Gool::HitCheck_Sphere2Sphere(const DirectX::SimpleMath::Vector3& Center, const float& Radius)
{
	// 2つの球の中心の間の距離の平方を計算
	SimpleMath::Vector3 d = m_position - Center;
	float distSq = d.Dot(d);
	// 平方した距離が平方した半径の合計よりも小さい場合に球は交差している
	float radiusSum = m_scale.x + Radius;
	return distSq <= radiusSum * radiusSum;
}


