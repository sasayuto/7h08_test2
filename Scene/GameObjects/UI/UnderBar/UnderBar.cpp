//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// ゲージ
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "UnderBar.h"

#include"Scene/SelectScene/MenuSelect/MenuSelect.h"
using namespace DirectX;

UnderBar::UnderBar() :
    m_underBar(nullptr),
    m_position(DirectX::SimpleMath::Vector2::Zero)
{
}

UnderBar::~UnderBar()
{
}

void UnderBar::Initialize(
    const DirectX::SimpleMath::Vector2& position,
    const DirectX::SimpleMath::Vector2& scale,
    const tito::ANCHOR& anchor,
    const tito::POSITION_ANCHOR& positionAnchor
)
{
    //画像の情報をセット(HPゲージ)
    Add(L"Resources/Textures/LetterBase.png"
        , L"Resources/Textures/FrameLetter2.png"
        , position
        , scale
        , anchor
        , positionAnchor
    );
}

void UnderBar::Update(int selectNum)
{

    int select = selectNum * MenuSelect::WIDTH;
    //プレイヤーのHPの割合計算
    m_underBar->SetPosition(m_position+DirectX::SimpleMath::Vector2(0, static_cast<float>(-select)));
}

void UnderBar::Render()
{
    //ゲージとベースを描画する
    m_underBar->Render();
}

void UnderBar::Add(
    const wchar_t* path,
    const wchar_t* basePath,
    const DirectX::SimpleMath::Vector2& position,
    const DirectX::SimpleMath::Vector2& scale,
    const tito::ANCHOR& anchor,
    const tito::POSITION_ANCHOR& positionAnchor
)
{
    //ゲージののリスポーンのインスタンスを生成する
    m_underBar = std::make_unique<tito::MoveUserInterface>();

    //必要な情報をセットする
    m_underBar->Create(
        path
        , position
        , scale
        , anchor
        , positionAnchor
    );
    m_position = position;
}




