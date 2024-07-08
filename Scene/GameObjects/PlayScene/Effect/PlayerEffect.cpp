//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// �Q�[�W
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "PlayerEffect.h"
#include "Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/Models/Draw.h"
const float GENERATION_TIME = 0.05f;
#include"Scene/GameObjects/Models/Textures.h"
using namespace DirectX;
PlayerEffect::PlayerEffect():
    m_timer()
{
}

PlayerEffect::~PlayerEffect()
{
}

void PlayerEffect::Initialize()
{
    m_particle = std::make_unique<Particle>();
    //�K�v�ȏ����Z�b�g����
    m_particle->Create(Textures::GetInstance()->GetSmoke());
}

void PlayerEffect::Update(
    const float& elapsedTime, 
    const DirectX::SimpleMath::Vector3& position,
    const DirectX::SimpleMath::Quaternion& rotate,
    const int& HP
)
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
                range * cosf(rand), 0.0f, range * sinf(rand) + 1.5f
            ), 
            rotate
        );

        float playerHp = HP / static_cast<float>(Player::PLAYER_MAX_HP);
        std::unique_ptr<ParticleUtility> pU = std::make_unique<ParticleUtility>(
            6.0f,
            SimpleMath::Vector3(position + m_position),				// ����W
            SimpleMath::Vector3(0.f, -0.1f, 0.f),			// ���x
            SimpleMath::Vector3(0, -1.1f, 0),					// �����x
            SimpleMath::Vector3(0.9f, 0.9f, 0.9f), SimpleMath::Vector3(0.2f, 0.2f, 0.2f),	// �����X�P�[���A�ŏI�X�P�[��
            SimpleMath::Color(playerHp * 1.0f, playerHp * 1.0f, playerHp * 1.0f, 0.5f), SimpleMath::Color(playerHp * 1.0f, playerHp * 1.0f, playerHp * 1.0f, 0.0f)	// �����J���[�A�ŏI�J���[
        );
        m_particle->Add(pU.get());
            m_timer = 0.0f;
    }
        m_particle->Update(elapsedTime);
}

void PlayerEffect::Render()
{   
    Draw::GetInstance()->CreateBillboard(m_particle->GetBillboard());
    m_particle->Render();
}

