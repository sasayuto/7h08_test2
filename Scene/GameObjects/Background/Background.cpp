#include "pch.h"
#include "Background.h"

using namespace DirectX;

const float Background::ROTATE_SPEED = 0.2f;

Background::Background() :
    m_scale(SimpleMath::Vector3::One),
    m_position(SimpleMath::Vector3::Zero),
    m_backgroundModel(nullptr),
    m_rotateY()
{
}

Background::~Background()
{
}

void Background::Initialize()
{
    m_backgroundModel->UpdateEffects([](IEffect* effect) {

        //ライトの影響を切る
        auto lit = dynamic_cast<IEffectLights*>(effect);
        if (lit)
        {
            lit->SetLightEnabled(0, false);
            lit->SetLightEnabled(1, false);
            lit->SetLightEnabled(2, false);
            lit->SetAmbientLightColor(Colors::Black);
        }
        //ライトを白にする
        auto basicEfect = dynamic_cast<BasicEffect*>(effect);
        if (basicEfect)
        {
            basicEfect->SetEmissiveColor(Colors::White);
        }
        }
    );
}

void Background::Render()
{
    //スケール、回転、位置の行列変換＆描画
    SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
    world *= SimpleMath::Matrix::CreateScale(m_scale);
    world *= SimpleMath::Matrix::CreateRotationY(XMConvertToRadians(m_rotateY));
    world *= SimpleMath::Matrix::CreateTranslation(m_position);
    Draw::GetInstance()->Rendersss(m_backgroundModel, world);

}

void Background::Finalize()
{
}

void Background::SelectMotion()
{
    //回転させる
    m_rotateY += ROTATE_SPEED;
}

void Background::RotateRender()
{
}

