//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// ゲージ
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "SandstormEffect.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Bench/BenchManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/StreetLight/StreetLightManager.h"
const float GENERATION_TIME = 0.05f;
const float SandstormEffect::SPEED=0.05f;
const float SandstormEffect::COLLIDER_ADJUSTMENT=100.0f;

using namespace DirectX;
SandstormEffect::SandstormEffect() :
    m_timer(),
    m_position(),
    m_survival(true)
{
}

SandstormEffect::~SandstormEffect()
{
}

void SandstormEffect::Initialize(BenchManager* benchManager, StreetLightManager* streetLightManager)
{
    m_pStreetLightManager = streetLightManager;
    m_pBenchManager = benchManager;
    m_colloder= std::make_unique<Collider::Box>();
    m_particle = std::make_unique<ParticleSandstorm>();
    m_colloder->SetExtents(SimpleMath::Vector3(18,30,18));
    m_colloder->SetPosition(m_position+SimpleMath::Vector3(0,15,0));
    m_survival = true;
    //必要な情報をセットする
    m_particle->Create(L"Resources/Textures/Sandstorm.png");
}

void SandstormEffect::Update(const float& elapsedTime)
{
    // 3.0秒ごとに生成
    m_timer += elapsedTime;
    if (m_timer >= GENERATION_TIME)
    {
        std::random_device seed;
        std::default_random_engine engine(seed());
        std::uniform_real_distribution<> dist(0, XM_2PI);
        float range = 1.0f;
        float rand = static_cast<float>(dist(engine));

        std::unique_ptr<ParticleUtility> pU = std::make_unique<ParticleUtility>(
            3.0f,
            SimpleMath::Vector3(range * cosf(rand), 0, range * sinf(rand))+ m_position,				// 基準座標
            SimpleMath::Vector3(range*3.0f * cosf(rand), 2.4f, range*3.0f * sinf(rand)),			// 速度
            SimpleMath::Vector3(range*3.0f * cosf(rand), 6, range*3.0f * sinf(rand)),					// 加速度
            SimpleMath::Vector3(10.0f, 10.0f, 10.0f), SimpleMath::Vector3(100.0f, 100.0f, 100.0f),	// 初期スケール、最終スケール
            SimpleMath::Color(1.0f, 1.0f, 1.0f, 0.6f), SimpleMath::Color(1.6f, 1.6f, 1.6f, 0),	// 初期カラー、最終カラー
            SimpleMath::Vector3(10, 0, 0)                                               //回転のスピード（仮で必要であれば書く）
        );
        m_particle->Add(pU.get());
        m_timer = 0.0f;
    }
    m_particle->Update(elapsedTime);
    m_particle->RotateUpdate();

    SimpleMath::Vector3 move(1, 0, -1);
    move.Normalize();
    move *= SPEED;

    m_position += move;
    m_colloder->SetPosition(m_position + SimpleMath::Vector3(0, 15, 0)- (move* COLLIDER_ADJUSTMENT));

    if (m_pBenchManager)
        m_pBenchManager->CheckHitSandstorm(this);
    if (m_pStreetLightManager)
        m_pStreetLightManager->CheckHitSandstorm(this);
}

void SandstormEffect::Render()
{
    Draw::GetInstance()->CreateBillboard(m_particle->GetBillboard());
    m_particle->Render();
    //Draw::GetInstance()->TestCubeModel(m_colloder->GetExtents(), m_colloder->GetPosition());
}
void SandstormEffect::SetpositionRandam(const float& min, const float& max)
{
    std::random_device seed;
    std::default_random_engine engine(seed());
    std::uniform_real_distribution<> distance(min, max);

    float x = static_cast<float>(distance(engine));
    float z = static_cast<float>(distance(engine));

    m_position = SimpleMath::Vector3(x, 0, z);
}
