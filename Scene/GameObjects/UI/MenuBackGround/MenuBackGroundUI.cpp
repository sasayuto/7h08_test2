//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// �Q�[�W
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "MenuBackGroundUI.h"
#include"Scene/GameTitle.h"

using namespace DirectX;

MenuBackGroundUI::MenuBackGroundUI():
    m_SpaseLetter(nullptr)
{
}

MenuBackGroundUI::~MenuBackGroundUI()
{
}

void MenuBackGroundUI::Initialize()
{
    //�摜�̏����Z�b�g(HP�Q�[�W)
    Add(L"Resources/Textures/MenuBackGroundUI.png"
        , SimpleMath::Vector2(0, 0)
        , SimpleMath::Vector2(1,1)
        , tito::ANCHOR::MIDDLE_CENTER
        , tito::POSITION_ANCHOR::MIDDLE_CENTER
    );
}

void MenuBackGroundUI::Update()
{
}

void MenuBackGroundUI::Render()
{   
    ////�Q�[�W�ƃx�[�X��`�悷��
    m_SpaseLetter->Render();
}

void MenuBackGroundUI::Add(
    const wchar_t* path,
    const DirectX::SimpleMath::Vector2& position,
    const DirectX::SimpleMath::Vector2& scale,
    const tito::ANCHOR& anchor,
    const tito::POSITION_ANCHOR& positionAnchor
)
{
    //�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
    m_SpaseLetter = std::make_unique<tito::UserInterface>();

    //�K�v�ȏ����Z�b�g����
    m_SpaseLetter->Create(
        path
        , position
        , scale
        , anchor
        , positionAnchor
    );
}


