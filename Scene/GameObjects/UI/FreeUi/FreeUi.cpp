//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// ゲージ
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "FreeUi.h"

using namespace DirectX;

FreeUi::FreeUi() :
    m_titleName(nullptr)
{
}

FreeUi::~FreeUi()
{
}

void FreeUi::Initialize(
    const wchar_t* path,
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
}

void FreeUi::Update()
{
    //プレイヤーのHPの割合計算

}

void FreeUi::Render()
{
    m_titleName->Render();
}

