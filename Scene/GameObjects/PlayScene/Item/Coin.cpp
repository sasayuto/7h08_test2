#include "pch.h"
#include"Coin.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include<random>

using namespace DirectX;

Coin::Coin() :Item(),
m_lightEffect(nullptr)
{
	SetSupplyPointModel(Resources::GetInstance()->GetCoinModel());
}

Coin::~Coin()
{
}

void Coin::Initialize()
{
	m_lightEffect = std::make_unique<LightEffect>();
	m_lightEffect->Initialize();

	//スケーリング
	SetScale(SimpleMath::Vector3(1.0f, 1.0f, 1.0f));

	//親クラスの初期化
	Item::Initialize();
}

void Coin::Update(const float& elapsedTime)
{
	m_lightEffect->Update(elapsedTime, GetPosition());
}

void Coin::Render()
{
	m_lightEffect->Render();
	//スケーリング、位置調整、回転をさせる
	Draw::GetInstance()->ShadowMapRenderNoPicture(GetSupplyPointModel(), GetWorld());
}

void Coin::Finalize()
{
}
