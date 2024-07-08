#include "pch.h"
#include"MoveObjects.h"
#include <math.h>
#include<random>
using namespace DirectX;
#include"MoveObjectsManager.h"

#include"../Bench/BenchParts/BenchPartFactory.h"
const float MoveObjects::ANIMATION_TIME(10.0f);//爆発モーションの時間

MoveObjects::MoveObjects():
	m_position(SimpleMath::Vector3::Zero),
	m_rotate(SimpleMath::Quaternion::Identity),
	m_survival(false),
	m_timer(0),
	m_killCountFlag(false),
	m_allSurvivalFlag(true),
	m_pPartModel(nullptr),
	m_world()
{
}

MoveObjects::~MoveObjects()
{

}

void MoveObjects::Initialize(BulletManager* bulletManager, MoveObjectsManager* benchManager)
{
	m_pBulletManager = bulletManager;

	m_pBenchManager = benchManager;
	//当たり判定を生成
	m_roughCollider = std::make_unique<Collider::Sphere>();
	m_timer = 0;
	//大まかな当たり判定に位置と半径をセット
	GetRoughCollider()->SetPosition(GetPosition()+DirectX::SimpleMath::Vector3(0,3,0));


	//スケーリング、位置調整、回転をさせる
	m_world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

	//対角線の半分
	GetRoughCollider()->SetRadius(12);
	for (auto& parts : m_parts)
	{
		parts->Initialize();
	}
	m_survival = true;
}

void MoveObjects::Update(const float& elapsedTime)
{	
	//パーツが生きているか
	bool PartsSurvival = false;
	for (auto& parts : m_parts)
	{
		if (parts->GetSurvival())
		{
			parts->Update(elapsedTime,m_position, m_rotate);
			PartsSurvival = true;
		}
		else
			parts->Explosion(elapsedTime);
	}
	//パーツがすべて死んだらアニメーションの時間を図る
	if (!PartsSurvival)
	{
		m_timer += elapsedTime;
		//キルカウントしてなかったらする
		if (!m_killCountFlag)
		{
			m_pBenchManager->SetBenchKillCount(m_pBenchManager->GetBenchKillCount() + 1);
			//カウントしたらtrueにする
			m_killCountFlag = true;
		}

		//アニメーションが終わったらなくす
		if (m_timer >= ANIMATION_TIME)
			m_survival = false;
	}
	if (m_pBulletManager)
		m_pBulletManager->CheckHitDestructionObjects(this);

	//一つでも壊れているか
	for (auto& parts : m_parts)
	{
		if (!parts->SurvivalCheck())
		{
			m_allSurvivalFlag = false;
			break;
		}
	}
}

void MoveObjects::Render()
{
	if (m_allSurvivalFlag)
	{
		//視界に入っているか
		if (Draw::GetInstance()->VisibilityRange(GetPosition(), GetModel()->meshes[0]->boundingSphere.Radius))
			return;

		// 飛行機の描画
		Draw::GetInstance()->ShadowMapRender(m_pPartModel, m_world);
	}
	else
		for (auto& parts : m_parts)
			parts->Render();

		//Draw::GetInstance()->TestSphereModel(GetRoughCollider()->GetRadius(), GetRoughCollider()->GetPosition());
}

void MoveObjects::RenderShadowTex()
{
	if (m_allSurvivalFlag)
	{
		// 飛行機の描画
		Draw::GetInstance()->ShadowMapTexCreate(m_pPartModel, m_world);
	}
	else
		for (auto& parts : m_parts)
			parts->RenderShadowTex();
}

void MoveObjects::SetpositionRandam(const float& min, const float& max)
{
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> distance(min, max);

	float x = static_cast<float>(distance(engine));
	float z = static_cast<float>(distance(engine));

	m_position = SimpleMath::Vector3(x, 0, z);
	m_rotate = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, x);
}
