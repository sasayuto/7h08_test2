#include "pch.h"
#include"FuelSupplyPoint.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include<random>

using namespace DirectX;

const int REPLENISHMENT_FUEL = 800;		//�񕜔R��



FuelSupplyPoint::FuelSupplyPoint() :Item()
{
	SetSupplyPointModel(Resources::GetInstance()->GetSupplyPointModel());
}

FuelSupplyPoint::~FuelSupplyPoint()
{

}

void FuelSupplyPoint::Initialize()
{
	//�X�P�[�����O
	SetScale(SimpleMath::Vector3(5.0f, 5.0f, 5.0f));

	//�e�N���X�̏�����
	Item::Initialize();
}

void FuelSupplyPoint::Update(const float& elapsedTime)
{
	elapsedTime;
}
void FuelSupplyPoint::Recovery(Player* player)
{
	////���̔R������񕜕��𑫂�
	//int PlayerFuel = player->GetFuel() + REPLENISHMENT_FUEL;

	////�R�����}�b�N�X�ȏ�ɂȂ����璲��
	//if (PlayerFuel > Player::PLAYER_MAX_FUEL)		PlayerFuel = Player::PLAYER_MAX_FUEL;

	//�R���Z�b�g
	player->SetFuel(Player::PLAYER_MAX_FUEL);
}
