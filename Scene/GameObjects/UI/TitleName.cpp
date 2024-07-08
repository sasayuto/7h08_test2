//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// �Q�[�W
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
    //�摜�̏����Z�b�g(HP�Q�[�W)
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
    //�v���C���[��HP�̊����v�Z
    m_titleName->SetTransparency(m_transparency);

}

void TitleName::Render()
{   
    ////�Q�[�W�ƃx�[�X��`�悷��
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
    //�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
    m_titleName = std::make_unique<tito::MoveUserInterface>();

    //�K�v�ȏ����Z�b�g����
    m_titleName->Create(
        path
        , position
        , scale
        , anchor
        , positionAnchor
    );
}


