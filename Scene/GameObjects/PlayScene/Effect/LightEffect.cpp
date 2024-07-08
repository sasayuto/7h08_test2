//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// �Q�[�W
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "LightEffect.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Textures.h"
using namespace DirectX;
const float GENERATION_TIME = 0.5f;

LightEffect::LightEffect() :
    m_timer()
{
}

LightEffect::~LightEffect()
{
}

void LightEffect::Initialize()
{
    m_particle = std::make_unique<Particle>();
    //�K�v�ȏ����Z�b�g����
    m_particle->Create(Textures::GetInstance()->GetCoinlight());
}

void LightEffect::Update(const float& elapsedTime, const DirectX::SimpleMath::Vector3& position)
{
    // 3.0�b���Ƃɐ���
    m_timer += elapsedTime;
    if (m_timer >= GENERATION_TIME)
    {
        std::random_device seed;
        std::default_random_engine engine(seed());
        std::uniform_real_distribution<> dist(0, XM_2PI);
        float rand = static_cast<float>(dist(engine));
        float range = 1.0f;

        std::unique_ptr<ParticleUtility> pU = std::make_unique<ParticleUtility>(
            0.3f,
            SimpleMath::Vector3(range * cosf(rand), 0.f, range * sinf(rand)) + position,				// ����W
            SimpleMath::Vector3(range * cosf(rand), 2.f, range * sinf(rand)),			// ���x
            SimpleMath::Vector3(0, -1.1f, 0),					// �����x
            SimpleMath::Vector3(2, 2, 2), SimpleMath::Vector3(0.4f, 0.4f, 0.4f),	// �����X�P�[���A�ŏI�X�P�[��
            SimpleMath::Color(1.f, 1.f, 1.f, 1.f), SimpleMath::Color(1, 0, 0, 1.f)	// �����J���[�A�ŏI�J���[
        );
        m_particle->Add(pU.get());
        m_timer = 0.0f;
    }
    m_particle->Update(elapsedTime);
    m_particle->SetBrightness(1);
    m_particle->SetEmissiveColor(DirectX::SimpleMath::Vector3(1,1,1));

}

void LightEffect::Render()
{

    Draw::GetInstance()->CreateBillboard(m_particle->GetBillboard());

    m_particle->Render();
}

