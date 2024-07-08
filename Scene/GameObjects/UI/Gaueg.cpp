//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// �Q�[�W
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Gaueg.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

using namespace DirectX;

Gaueg::Gaueg(Player* player):
    m_gaueg()
    ,m_baes()
    ,m_player(player)
{
}

Gaueg::~Gaueg()
{
}

void Gaueg::Initialize()
{
    //�摜�̏����Z�b�g(HP�Q�[�W)
    Add(L"Resources/Textures/HPGauge.png"
        , L"Resources/Textures/HPGageBase.png"
        , L"Resources/Textures/HPFrame.png"
        , SimpleMath::Vector2(50, -550)
        , SimpleMath::Vector2(1, 1)
        , tito::ANCHOR::TOP_LEFT
        , tito::POSITION_ANCHOR::TOP_LEFT
    );
    //�摜�̏����Z�b�g(�R���Q�[�W)
    Add(L"Resources/Textures/FuelGauge.png"
        , L"Resources/Textures/FuelGaugeBase.png"
        , L"Resources/Textures/FuelGaugeFrame.png"
        , SimpleMath::Vector2(300, -550)
        , SimpleMath::Vector2(1, 1)
        , tito::ANCHOR::TOP_LEFT
        , tito::POSITION_ANCHOR::TOP_LEFT
    );



}

void Gaueg::Update()
{
    //�v���C���[��HP�̊����v�Z
    float ratio = m_player->GetHP() / static_cast<float>(Player::PLAYER_MAX_HP);
    m_gaueg[0]->SetRemderRatio(ratio);

    //�v���C���[�̔R���̊����v�Z
    ratio = m_player->GetFuel() / static_cast<float>(Player::PLAYER_MAX_FUEL);
    m_gaueg[1]->SetRemderRatio(ratio);

}

void Gaueg::Render()
{   
    //�Q�[�W�ƃx�[�X��`�悷��
    for (int i = 0; i < m_gaueg.size(); i++)
    {
        m_baes[i]->Render();
        m_gaueg[i]->Render();
        m_frame[i]->Render();
    }
}

void Gaueg::Add(const wchar_t* path,const wchar_t* basePath, const wchar_t* framePath,
    const DirectX::SimpleMath::Vector2& position,const DirectX::SimpleMath::Vector2& scale,const tito::ANCHOR& anchor,
    const tito::POSITION_ANCHOR& posotionAnchor)
{
    //�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
    std::unique_ptr<tito::GaugeManager> gaueg = std::make_unique<tito::GaugeManager>();

    //�K�v�ȏ����Z�b�g����
    gaueg->Create(
        path
        , position
        , scale
        , anchor
        , posotionAnchor
    );

    m_gaueg.push_back(std::move(gaueg));


    std::unique_ptr<tito::GaugeManager> baes = std::make_unique<tito::GaugeManager>();

    //�K�v�ȏ����Z�b�g����
    baes->Create(
        basePath
        , position
        , scale
        , anchor,
        posotionAnchor
    );

    m_baes.push_back(std::move(baes));

    std::unique_ptr<tito::GaugeManager> frame = std::make_unique<tito::GaugeManager>();

    //�K�v�ȏ����Z�b�g����
    frame->Create(
        framePath
        , position
        , scale
        , anchor, 
        posotionAnchor
    );

    m_frame.push_back(std::move(frame));


}


