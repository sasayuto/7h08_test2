#include "pch.h"
#include"HpSupplyPoint.h"
#include<random>
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

using namespace DirectX;
//ƒvƒŒƒCƒ„[‚Ì3Š„
const int HpSupplyPoint::REPLENISHMENT_HP(static_cast<int>(Player::PLAYER_MAX_HP * (3 * 0.1f)));



HpSupplyPoint::HpSupplyPoint() :Item()
{
	SetSupplyPointModel(Resources::GetInstance()->GetHPSupplyPointModel());
}

HpSupplyPoint::~HpSupplyPoint()
{

}

void HpSupplyPoint::Initialize()
{
	SetScale(SimpleMath::Vector3(5.0f, 5.0f, 5.0f));
	Item::Initialize();
}

void HpSupplyPoint::Update(const float& elapsedTime)
{
	elapsedTime;
}



void HpSupplyPoint::Recovery(Player* player)
{
	int PlayerHp = player->GetHP() + REPLENISHMENT_HP;

	if (PlayerHp>=Player::PLAYER_MAX_HP)		PlayerHp = Player::PLAYER_MAX_HP;

	player->SetHP(PlayerHp);
}


