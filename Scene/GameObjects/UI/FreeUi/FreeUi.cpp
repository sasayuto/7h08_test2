//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// �Q�[�W
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
        //�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
    m_titleName = std::make_unique<tito::UserInterface>();

    //�K�v�ȏ����Z�b�g����
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
    //�v���C���[��HP�̊����v�Z

}

void FreeUi::Render()
{
    m_titleName->Render();
}

