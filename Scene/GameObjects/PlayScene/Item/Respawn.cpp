#include "pch.h"
#include"Respawn.h"
#include<random>
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

using namespace DirectX;

Respawn::Respawn() :Item()
{
	SetSupplyPointModel(Resources::GetInstance()->GetRespawnModel());
}

Respawn::~Respawn()
{

}

void Respawn::Initialize()
{
	SetScale(SimpleMath::Vector3(5.0f, 5.0f, 5.0f));
	Item::Initialize();
}

void Respawn::Update(const float& elapsedTime)
{
	elapsedTime;
	if (!GetSurvival()) 
	{
		SetScale(SimpleMath::Vector3::One);
	}
}

void Respawn::Render()
{
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	world *= SimpleMath::Matrix::CreateScale(GetScale());
	world *= SimpleMath::Matrix::CreateTranslation(GetPosition());

	Draw::GetInstance()->Render(Item::GetSupplyPointModel(), world);
}

void Respawn::Recovery(Player* player)
{
	//燃料マックス
	player->SetHP(Player::PLAYER_MAX_HP);
	player->SetFuel(Player::PLAYER_MAX_FUEL);

}

