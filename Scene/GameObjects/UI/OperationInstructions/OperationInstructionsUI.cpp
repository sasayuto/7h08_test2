//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// �Q�[�W
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "OperationInstructionsUI.h"
#include"Scene/GameTitle.h"

using namespace DirectX;

OperationInstructionsUI::OperationInstructionsUI():
    m_SpaseLetter(nullptr)
{
}

OperationInstructionsUI::~OperationInstructionsUI()
{
}

void OperationInstructionsUI::Initialize()
{
    //�摜�̏����Z�b�g(HP�Q�[�W)
    Add(L"Resources/Textures/OperationInstructions.png"
        , SimpleMath::Vector2(0, 0)
        , SimpleMath::Vector2(1,1)
        , tito::ANCHOR::MIDDLE_CENTER
        , tito::POSITION_ANCHOR::MIDDLE_CENTER
    );
}

void OperationInstructionsUI::Update()
{
}

void OperationInstructionsUI::Render()
{   
    ////�Q�[�W�ƃx�[�X��`�悷��
    m_SpaseLetter->Render();
}

void OperationInstructionsUI::Add(
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


