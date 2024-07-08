//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// �Q�[�W
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "TutorialLetter.h"

using namespace DirectX;

const float TutorialLetter::TRANSPARENT_END_TIME(1.0f);

TutorialLetter::TutorialLetter() :
    m_titleName(nullptr),
    m_transparency(0)
{
}

TutorialLetter::~TutorialLetter()
{
}

void TutorialLetter::Initialize(
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
    m_titleName->SetTransparency(m_transparency);
}

void TutorialLetter::Update(const float& elapsedTime)
{
    if (m_transparency >= 1.0f)
        return;

    m_transparency += elapsedTime / TRANSPARENT_END_TIME;
    m_titleName->SetTransparency(m_transparency);

}

void TutorialLetter::ReduceTransparency(const float& elapsedTime)
{
    if (m_transparency <= 0.0f)
        return;

    m_transparency -= elapsedTime / TRANSPARENT_END_TIME;
    m_titleName->SetTransparency(m_transparency);
}

void TutorialLetter::Render()
{
    m_titleName->Render();
}

