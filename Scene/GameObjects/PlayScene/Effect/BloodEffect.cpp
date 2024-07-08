//--------------------------------------------------------------------------------------
// File: BloodEffect.h
//
// �Q�[�W
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "BloodEffect.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

using namespace DirectX;

BloodEffect::BloodEffect():
m_bloodEffect()
{
}

BloodEffect::~BloodEffect()
{
}

void BloodEffect::Initialize()
{
    //�摜�̏����Z�b�g(HP�Q�[�W)
    Add(L"Resources/Textures/PinchEffect.png"
        , SimpleMath::Vector2(0, 0)
        , SimpleMath::Vector2(1, 1)
        , tito::ANCHOR::TOP_LEFT
        , tito::POSITION_ANCHOR::TOP_LEFT
    );

    //�ŏ��͓���
    m_bloodEffect->SetTransparency(0);

}

void BloodEffect::Update(int HP)
{
    float pinchHP = static_cast<float>(Player::PLAYER_MAX_HP) / 4.0f;

    float transparency = static_cast<float>(HP) / pinchHP;
    if (transparency>=1)
        transparency = 1;
    transparency = (transparency - 1) * -1;
    m_bloodEffect->SetTransparency(transparency);
}

void BloodEffect::Render()
{   
    m_bloodEffect->Render();
}

void BloodEffect::Add(const wchar_t* path,const DirectX::SimpleMath::Vector2& position,const DirectX::SimpleMath::Vector2& scale,const tito::ANCHOR& anchor,
    const tito::POSITION_ANCHOR& positionAnchor)
{
    //�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
    m_bloodEffect = std::make_unique<tito::GaugeManager>();

    //�K�v�ȏ����Z�b�g����
    m_bloodEffect->Create(
        path
        , position
        , scale
        , anchor
        , positionAnchor
    );
}


