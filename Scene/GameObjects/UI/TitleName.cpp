//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// ゲージ
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "TitleName.h"
#include"Scene/GameTitle.h"

using namespace DirectX;

TitleName::TitleName():
   m_titleName(nullptr),
    m_transparency(0)
{
}

TitleName::~TitleName()
{
}

void TitleName::Initialize()
{
    //画像の情報をセット(HPゲージ)
    Add(L"Resources/Textures/GameTitleLetter_01.png"
        , SimpleMath::Vector2(0, 120)
        , SimpleMath::Vector2(0.6f,0.7f)
        , tito::ANCHOR::MIDDLE_CENTER
        , tito::POSITION_ANCHOR::MIDDLE_CENTER
    );
}

void TitleName::Update(const float& nowTime)
{
    if (nowTime >= GameTitle::SELECT_TINE)
    {
        m_transparency += 0.01f;
    }
    //プレイヤーのHPの割合計算
    m_titleName->SetTransparency(m_transparency);

}

void TitleName::Render()
{   
    ////ゲージとベースを描画する
    m_titleName->Render();
}

void TitleName::Add(
    const wchar_t* path,
    const DirectX::SimpleMath::Vector2& position,
    const DirectX::SimpleMath::Vector2& scale,
    const tito::ANCHOR& anchor,
    const tito::POSITION_ANCHOR& positionAnchor
)
{
    //ゲージののリスポーンのインスタンスを生成する
    m_titleName = std::make_unique<tito::MoveUserInterface>();

    //必要な情報をセットする
    m_titleName->Create(
        path
        , position
        , scale
        , anchor
        , positionAnchor
    );
}


