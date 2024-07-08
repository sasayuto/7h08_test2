//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// ゲージ
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
    //画像の情報をセット(HPゲージ)
    Add(L"Resources/Textures/HPGauge.png"
        , L"Resources/Textures/HPGageBase.png"
        , L"Resources/Textures/HPFrame.png"
        , SimpleMath::Vector2(50, -550)
        , SimpleMath::Vector2(1, 1)
        , tito::ANCHOR::TOP_LEFT
        , tito::POSITION_ANCHOR::TOP_LEFT
    );
    //画像の情報をセット(燃料ゲージ)
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
    //プレイヤーのHPの割合計算
    float ratio = m_player->GetHP() / static_cast<float>(Player::PLAYER_MAX_HP);
    m_gaueg[0]->SetRemderRatio(ratio);

    //プレイヤーの燃料の割合計算
    ratio = m_player->GetFuel() / static_cast<float>(Player::PLAYER_MAX_FUEL);
    m_gaueg[1]->SetRemderRatio(ratio);

}

void Gaueg::Render()
{   
    //ゲージとベースを描画する
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
    //ゲージののリスポーンのインスタンスを生成する
    std::unique_ptr<tito::GaugeManager> gaueg = std::make_unique<tito::GaugeManager>();

    //必要な情報をセットする
    gaueg->Create(
        path
        , position
        , scale
        , anchor
        , posotionAnchor
    );

    m_gaueg.push_back(std::move(gaueg));


    std::unique_ptr<tito::GaugeManager> baes = std::make_unique<tito::GaugeManager>();

    //必要な情報をセットする
    baes->Create(
        basePath
        , position
        , scale
        , anchor,
        posotionAnchor
    );

    m_baes.push_back(std::move(baes));

    std::unique_ptr<tito::GaugeManager> frame = std::make_unique<tito::GaugeManager>();

    //必要な情報をセットする
    frame->Create(
        framePath
        , position
        , scale
        , anchor, 
        posotionAnchor
    );

    m_frame.push_back(std::move(frame));


}


