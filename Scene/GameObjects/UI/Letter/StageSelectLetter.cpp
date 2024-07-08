//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// �Q�[�W
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "StageSelectLetter.h"

using namespace DirectX;

StageSelectLetter::StageSelectLetter() :
    m_titleName(nullptr),
    m_path(nullptr)
{
}

StageSelectLetter::~StageSelectLetter()
{
}

void StageSelectLetter::Initialize(
    const DirectX::SimpleMath::Vector2& position,
    const DirectX::SimpleMath::Vector2& scale,
    const tito::ANCHOR& anchor,
    const tito::POSITION_ANCHOR& positionAnchor
)
{
    ////�摜�̏����Z�b�g(HP�Q�[�W)
    //Add(L"Resources/Textures/StageSelectLetter.png"
    //    , L"Resources/Textures/FrameLetter2.png"
    //    , position
    //    , scale
    //    , anchor
    //    , positionAnchor
    //);
    // 
        //�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
    m_titleName = std::make_unique<tito::UserInterface>();

    //�K�v�ȏ����Z�b�g����
    m_titleName->Create(
        m_path
        , position
        , scale
        , anchor
        , positionAnchor
    );
}

void StageSelectLetter::Update()
{
    //�v���C���[��HP�̊����v�Z

}

void StageSelectLetter::Render()
{
    ////�Q�[�W�ƃx�[�X��`�悷��
    //m_titleNameBase->Render();
    m_titleName->Render();
}

void StageSelectLetter::Add(
    const wchar_t* path,
    const wchar_t* basePath,
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

    ////�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
    //m_titleNameBase = std::make_unique<tito::UserInterface>();

    ////�K�v�ȏ����Z�b�g����
    //m_titleNameBase->Create(
    //    basePath
    //    , position
    //    , scale*DirectX::SimpleMath::Vector2(8,1)
    //    , anchor
    //    , positionAnchor
    //);
}




