#include "pch.h"
#include"Floor.h"
using namespace DirectX;

#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

Floor::Floor() :
	m_position(SimpleMath::Vector3::Zero),
	m_objectsModel(nullptr),
	m_collider(nullptr),
	m_rotate(DirectX::SimpleMath::Quaternion::Identity)

{
}

Floor::~Floor()
{
	
}

void Floor::Initialize()
{
	//当たり判定を生成
	m_collider = std::make_unique<Collider::OBB>();
}

void Floor::Update()
{	
}

void Floor::Render()
{	
	//スケーリング、位置調整、回転をさせる
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	world *= SimpleMath::Matrix::CreateTranslation(m_position);

	Draw::GetInstance()->ShadowMapRender(GetModel(), world);
	//Draw::GetInstance()->TestCubeModel(m_collider->GetExtents(), m_collider->GetPosition());
}

void Floor::CheckHitPlayer(Player* player)
{
	if (!(m_collider->CheckHitSphere(player->GetCollider())))
		return;
	
	for (auto& playerParts : player->GetParts())
	{
		if (!playerParts->CollisionFloor(this))
			continue;

		player->Damage(player->GetHP());
		return;
	}
}

void Floor::CheckHitEnemy(Enemy* enemy)
{
	if (!(m_collider->CheckHitSphere(enemy->GetCollider())))
		return;

	for (auto& enemyParts : enemy->GetParts())
	{
		if (!enemyParts->CollisionFloor(this))
			continue;

		enemy->Damage(enemy->GetHP());
		return;
	}
}

