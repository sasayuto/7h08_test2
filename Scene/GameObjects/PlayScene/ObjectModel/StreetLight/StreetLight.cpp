#include "pch.h"
#include"StreetLight.h"
#include <math.h>
#include<random>
using namespace DirectX;
#include"StreetLightManager.h"
#include"StreetLightParts/StreetLightPartFactory.h"

const float StreetLight::ANIMATION_TIME(10.0f);//爆発モーションの時間

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
	//当たり判定を生成
	m_roughCollider = std::make_unique<Collider::Sphere>();

	//大まかな当たり判定に位置と半径をセット
	GetRoughCollider()->SetPosition(GetPosition()+DirectX::SimpleMath::Vector3(0,3,0));

	//対角線の半分
	GetRoughCollider()->SetRadius(5);
	for (auto& parts : m_parts)
	{
		parts->Initialize();
	}
	//スケーリング、位置調整、回転をさせる
	
	m_world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	m_survival = true;
}

void StreetLight::Update(const float& elapsedTime)
{	
	//パーツが生きているか
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
	//パーツがすべて死んだらアニメーションの時間を図る
	if (!PartsSurvival)
	{
		//キルカウントしてなかったらする
		if(!m_killCountFlag)
		{
			m_pStreetLightManager->SetStreetLightKillCount(m_pStreetLightManager->GetStreetLightKillCount() + 1);
			//カウントしたらtrueにする
			m_killCountFlag = true;
		}

		m_timer += elapsedTime;
		//アニメーションが終わったらなくす
		if (m_timer >= ANIMATION_TIME)
			m_survival = false;
	}

	//一つでも壊れているか
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
		//視界に入っているか
		if (Draw::GetInstance()->VisibilityRange(GetPosition(), 10))
			return;

		// 飛行機の描画
		Draw::GetInstance()->ShadowMapRenderNoPicture(m_pStreetLight, m_world);
	}
	else
		for (auto& parts : m_parts)
			parts->Render();
}

void StreetLight::RenderShadowTex()
{
	if (m_allSurvivalFlag)
		// 飛行機の描画
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
