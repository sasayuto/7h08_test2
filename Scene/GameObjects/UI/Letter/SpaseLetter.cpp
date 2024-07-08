//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// ゲージ
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "SpaseLetter.h"
#include"Scene/GameTitle.h"

using namespace DirectX;

SpaseLetter::SpaseLetter():
   m_SpaseLetter(nullptr),
    m_timer(0),
    m_transparency(0),
    m_transparencyFlag(true)
{
}

SpaseLetter::~SpaseLetter()
{
}

void SpaseLetter::Initialize()
{
    //画像の情報をセット(HPゲージ)
    Add(L"Resources/Textures/StateLetter.png"
        , SimpleMath::Vector2(0, 130)
        , SimpleMath::Vector2(1,1)
        , tito::ANCHOR::MIDDLE_CENTER
        , tito::POSITION_ANCHOR::BOTTOM_CENTER
    );
}

void SpaseLetter::Update(const float& nowTime)
{
    if (nowTime >= GameTitle::SELECT_TINE)
    {
        if (m_transparency >= 1.0f)
            m_transparencyFlag = false;

        if (m_transparency <= 0.0f)
            m_transparencyFlag = true;

        if (m_transparencyFlag)
            m_transparency += 0.01f;
        else
            m_transparency -= 0.01f;
    }

    //プレイヤーのHPの割合計算
    m_SpaseLetter->SetTransparency(m_transparency);

}

void SpaseLetter::Render()
{   
    ////ゲージとベースを描画する
    m_SpaseLetter->Render();
}

void SpaseLetter::Add(
    const wchar_t* path,
    const DirectX::SimpleMath::Vector2& position,
    const DirectX::SimpleMath::Vector2& scale,
    const tito::ANCHOR& anchor,
    const tito::POSITION_ANCHOR& positionAnchor
)
{
    //ゲージののリスポーンのインスタンスを生成する
    m_SpaseLetter = std::make_unique<tito::MoveUserInterface>();

    //必要な情報をセットする
    m_SpaseLetter->Create(
        path
        , position
        , scale
        , anchor
        , positionAnchor
    );
}


