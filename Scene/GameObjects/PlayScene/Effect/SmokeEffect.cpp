//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// �Q�[�W
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "SmokeEffect.h"
#include"Scene/GameObjects/Models/Draw.h"
const float GENERATION_TIME = 0.1f;
#include"Scene/GameObjects/Models/Textures.h"
using namespace DirectX;
SmokeEffect::SmokeEffect():
    m_timer()
{
}

SmokeEffect::~SmokeEffect()
{
}

void SmokeEffect::Initialize()
{
    m_particle = std::make_unique<Particle>();
    //�K�v�ȏ����Z�b�g����
    m_particle->Create(Textures::GetInstance()->GetSmoke());
}

void SmokeEffect::Update(const float& elapsedTime, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate)
{
    // 3.0�b���Ƃɐ���
    m_timer += elapsedTime;
    if (m_timer >= GENERATION_TIME)
    {
        std::random_device seed;
        std::default_random_engine engine(seed());
        std::uniform_real_distribution<> dist(0, XM_2PI);
        float range = 0.2f;
        float rand = static_cast<float>(dist(engine));

        SimpleMath::Vector3 m_position;
        m_position = SimpleMath::Vector3::Transform(
            SimpleMath::Vector3(
                range * cosf(rand), 0.0f, range * sinf(rand)
            ), 
            rotate
        );

        std::unique_ptr<ParticleUtility> pU = std::make_unique<ParticleUtility>(
            4.0f,
            SimpleMath::Vector3(position + m_position),				// ����W
            SimpleMath::Vector3(0.f, -0.8f, 0.f),			// ���x
            SimpleMath::Vector3(0, 0, 0),					// �����x
            SimpleMath::Vector3(3.0f, 3.0f, 3.0f), SimpleMath::Vector3(1.0f, 1.0f, 1.0f),	// �����X�P�[���A�ŏI�X�P�[��
            SimpleMath::Color(1.0f, 1.0f, 1.0f, 0.8f), SimpleMath::Color(1.6f, 1.6f, 1.0f, 0.0f)	// �����J���[�A�ŏI�J���[
        );
        m_particle->Add(pU.get());
            m_timer = 0.0f;
    }
        m_particle->Update(elapsedTime);
}

void SmokeEffect::Render()
{   
    Draw::GetInstance()->CreateBillboard(m_particle->GetBillboard());
    m_particle->Render();
}

