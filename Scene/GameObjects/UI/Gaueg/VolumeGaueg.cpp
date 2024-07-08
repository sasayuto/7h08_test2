//--------------------------------------------------------------------------------------
// File: VolumeGaueg.h
//
// ゲージ
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "VolumeGaueg.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/Models/Textures.h"
using namespace DirectX;

const int VolumeGaueg::TEXTURE_ANCHOR_RATIO_NUM(3);    //画像のアンカーの分割数

VolumeGaueg::VolumeGaueg():
    m_baes(),
    m_BottonPosition(),
    m_initialBottonPosition(),
    m_BottonFlag(),
    m_pressedMousePos_x(),
    m_bottonPosStorage_x(),
    m_ratio()
{
}

VolumeGaueg::~VolumeGaueg()
{
}

void VolumeGaueg::Initialize(const DirectX::SimpleMath::Vector2& position,
    const DirectX::SimpleMath::Vector2& scale,
    const tito::ANCHOR& anchor,
    const tito::POSITION_ANCHOR& positionAnchor,
    const float& ratio
)
{
    //画像の情報をセット(HPゲージ)
    Add(L"Resources/Textures/VolumeGage.png"
        , L"Resources/Textures/VolumeGageBackground.png"
        , position
        , scale
        , anchor
        , positionAnchor
    );

    //画像の位置を求める
    DirectX::SimpleMath::Vector2 framePosition = TexPositionCorrection(
        position,
        m_frame->GetTextureWidth(), m_frame->GetTextureHeight(),
        scale,
        anchor,
        positionAnchor
    );
    m_ratio = ratio;
    float bottonPos = (m_frame->GetTextureWidth() - 5) * ratio;
    m_BottonPosition.x = bottonPos;
    m_bottonPosStorage_x = bottonPos;

    m_collider = std::make_unique<Collider::Box2D>();

    m_collider->Initialize(framePosition, TexSizeCorrection(m_frame->GetTextureWidth(),m_frame->GetTextureHeight()));
}

void VolumeGaueg::Update()
{
    auto mouseTracker = KeyboardTracker::GetInstance()->GetMouseTracker();
    auto ms = KeyboardSingleton::GetInstance()->GetMouseState();

    // マウスの左ボタンが押された
    if (mouseTracker.leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
    {
        if (m_collider->CheckHitPoint(ms.x, ms.y))
        {
            m_BottonFlag = true;
            //マウス座標を保存
            m_pressedMousePos_x = static_cast<float>(ms.x);
        }
    }
    // マウスの左ボタンが押された
    if (mouseTracker.leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
    {
        //動いた距離を保存
        m_BottonFlag = false;
        m_bottonPosStorage_x = m_BottonPosition.x;
    }

    //押されたら移動させる
    if (m_BottonFlag)
        m_BottonPosition.x = (ms.x - m_pressedMousePos_x) + m_bottonPosStorage_x;

    //上限と下限の設定
    m_BottonPosition.x = static_cast<float>(std::max(std::min(static_cast<int>(m_BottonPosition.x), m_frame->GetTextureWidth() - 5), 0));

    //画像の大きさから割合を求める
    m_ratio = m_BottonPosition.x / static_cast<float>(m_frame->GetTextureWidth() - 5);

    m_bottom->SetPosition(m_initialBottonPosition + m_BottonPosition);

    m_frame->SetRemderRatio(m_ratio);
    

}

void VolumeGaueg::Render()
{
    m_baes->Render();
    m_frame->Render();
    m_bottom->Render();
}

void VolumeGaueg::SetRatio(const float& ratio)
{
    m_ratio = ratio;
    float bottonPos = (m_frame->GetTextureWidth() - 5) * ratio;
    m_BottonPosition.x = bottonPos;
    m_bottonPosStorage_x = bottonPos;
}

void VolumeGaueg::Add(const wchar_t* path,const wchar_t* basePath,
    const DirectX::SimpleMath::Vector2& position,const DirectX::SimpleMath::Vector2& scale, const tito::ANCHOR& anchor, const tito::POSITION_ANCHOR& positionAnchor)
{
    m_baes = std::make_unique<tito::GaugeManager>();

    //必要な情報をセットする
    m_baes->Create(
        basePath
        , position
        , scale
        , anchor
        , positionAnchor
    );

    m_frame = std::make_unique<tito::GaugeManager>();

    //必要な情報をセットする
    m_frame->Create(
        path
        , position
        , scale
        , anchor
        , positionAnchor
    );

    m_bottom = std::make_unique<tito::MoveUserInterface>();

    //Buttonの初期値を右へ
    int halfSize = (m_frame->GetTextureWidth() * (static_cast<int>(anchor) % TEXTURE_ANCHOR_RATIO_NUM))/2;
    m_initialBottonPosition = position - DirectX::SimpleMath::Vector2(static_cast<float>(halfSize), 0);

    //Buttonのアンカーをセンターに統一
    int anchorCenter = (static_cast<int>(anchor) / TEXTURE_ANCHOR_RATIO_NUM) * TEXTURE_ANCHOR_RATIO_NUM +1;

    //必要な情報をセットする
    m_bottom->Create(
        L"Resources/Textures/Bottom.png"
        , m_initialBottonPosition
        , scale
        , static_cast<tito::ANCHOR>(anchorCenter)
        , positionAnchor
    );
}

