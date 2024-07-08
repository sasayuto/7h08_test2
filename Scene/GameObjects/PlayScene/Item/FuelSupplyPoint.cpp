#include "pch.h"
#include"FuelSupplyPoint.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include<random>

using namespace DirectX;

const int REPLENISHMENT_FUEL = 800;		//回復燃料



FuelSupplyPoint::FuelSupplyPoint() :Item()
{
	SetSupplyPointModel(Resources::GetInstance()->GetSupplyPointModel());
}

FuelSupplyPoint::~FuelSupplyPoint()
{

}

void FuelSupplyPoint::Initialize()
{
	//スケーリング
	SetScale(SimpleMath::Vector3(5.0f, 5.0f, 5.0f));

	//親クラスの初期化
	Item::Initialize();
}

void FuelSupplyPoint::Update(const float& elapsedTime)
{
	elapsedTime;
}
void FuelSupplyPoint::Recovery(Player* player)
{
	////元の燃料から回復分を足す
	//int PlayerFuel = player->GetFuel() + REPLENISHMENT_FUEL;

	////燃料がマックス以上になったら調整
	//if (PlayerFuel > Player::PLAYER_MAX_FUEL)		PlayerFuel = Player::PLAYER_MAX_FUEL;

	//燃料セット
	player->SetFuel(Player::PLAYER_MAX_FUEL);
}
