//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// ゲージ
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "StageSelectLetter.h"

using namespace DirectX;

StageSelectLetter::StageSelectLetter() :
    m_titleName(nullptr),
    m_path(nullptr)
{
}

StageSelectLetter::~StageSelectLetter()
{
}

void StageSelectLetter::Initialize(
    const DirectX::SimpleMath::Vector2& position,
    const DirectX::SimpleMath::Vector2& scale,
    const tito::ANCHOR& anchor,
    const tito::POSITION_ANCHOR& positionAnchor
)
{
    ////画像の情報をセット(HPゲージ)
    //Add(L"Resources/Textures/StageSelectLetter.png"
    //    , L"Resources/Textures/FrameLetter2.png"
    //    , position
    //    , scale
    //    , anchor
    //    , positionAnchor
    //);
    // 
        //ゲージののリスポーンのインスタンスを生成する
    m_titleName = std::make_unique<tito::UserInterface>();

    //必要な情報をセットする
    m_titleName->Create(
        m_path
        , position
        , scale
        , anchor
        , positionAnchor
    );
}

void StageSelectLetter::Update()
{
    //プレイヤーのHPの割合計算

}

void StageSelectLetter::Render()
{
    ////ゲージとベースを描画する
    //m_titleNameBase->Render();
    m_titleName->Render();
}

void StageSelectLetter::Add(
    const wchar_t* path,
    const wchar_t* basePath,
    const DirectX::SimpleMath::Vector2& position,
    const DirectX::SimpleMath::Vector2& scale,
    const tito::ANCHOR& anchor,
    const tito::POSITION_ANCHOR& positionAnchor
)
{
    //ゲージののリスポーンのインスタンスを生成する
    m_titleName = std::make_unique<tito::UserInterface>();

    //必要な情報をセットする
    m_titleName->Create(
        path
        , position
        , scale
        , anchor
        , positionAnchor
    );

    ////ゲージののリスポーンのインスタンスを生成する
    //m_titleNameBase = std::make_unique<tito::UserInterface>();

    ////必要な情報をセットする
    //m_titleNameBase->Create(
    //    basePath
    //    , position
    //    , scale*DirectX::SimpleMath::Vector2(8,1)
    //    , anchor
    //    , positionAnchor
    //);
}




