//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// ゲージ
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "ReturnLetter.h"
#include"Scene/GameTitle.h"

using namespace DirectX;

ReturnLetter::ReturnLetter():
   m_returnLetter(nullptr),
    m_mouseFlag(false)
{
}

ReturnLetter::~ReturnLetter()
{
}

void ReturnLetter::Initialize()
{
    //画像の情報をセット(HPゲージ)
    Add(L"Resources/Textures/returnLetter.png"
        , SimpleMath::Vector2(200, -100)
        , SimpleMath::Vector2(1,1)
        , tito::ANCHOR::MIDDLE_CENTER
        , tito::POSITION_ANCHOR::TOP_LEFT
    );

    m_collider = std::make_unique<Collider::Box2D>();
    m_collider->Initialize(m_returnLetter->TexPositionCalculation(), m_returnLetter->TexSizeCalculation());
}

void ReturnLetter::Update(const float& nowTime)
{
    nowTime;
    auto mouse = KeyboardSingleton::GetInstance()->GetMouseState();

    m_mouseFlag = false;
    if (m_collider->CheckHitPoint(mouse.x, mouse.y))
    {
        m_mouseFlag = true;
    }
    if(m_mouseFlag)
        m_returnLetter->SetScale(DirectX::SimpleMath::Vector2(1.2f,1.2f));
    else
        m_returnLetter->SetScale(DirectX::SimpleMath::Vector2::One);

}

void ReturnLetter::Render()
{   
    ////ゲージとベースを描画する
    m_returnLetter->Render();
}

void ReturnLetter::Add(
    const wchar_t* path,
    const DirectX::SimpleMath::Vector2& position,
    const DirectX::SimpleMath::Vector2& scale,
    const tito::ANCHOR& anchor,
    const tito::POSITION_ANCHOR& positionAnchor
)
{
    //ゲージののリスポーンのインスタンスを生成する
    m_returnLetter = std::make_unique<tito::MoveUserInterface>();

    //必要な情報をセットする
    m_returnLetter->Create(
        path
        , position
        , scale
        , anchor
        , positionAnchor
    );
}


