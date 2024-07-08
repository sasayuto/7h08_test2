//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// �Q�[�W
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
    //�摜�̏����Z�b�g(HP�Q�[�W)
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
    //�v���C���[��HP�̊����v�Z
    m_underBar->SetPosition(m_position+DirectX::SimpleMath::Vector2(0, static_cast<float>(-select)));
}

void UnderBar::Render()
{
    //�Q�[�W�ƃx�[�X��`�悷��
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
    //�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
    m_underBar = std::make_unique<tito::MoveUserInterface>();

    //�K�v�ȏ����Z�b�g����
    m_underBar->Create(
        path
        , position
        , scale
        , anchor
        , positionAnchor
    );
    m_position = position;
}




