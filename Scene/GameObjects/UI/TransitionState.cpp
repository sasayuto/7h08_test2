//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// �Q�[�W
// 
//-------------------------------------------------------------------------------------
#include "pch.h"
#include "TransitionState.h"

using namespace DirectX;

TransitionState::TransitionState() :
    m_animationTime(1),
    m_transition(nullptr),
    m_stageSelct(false),
    m_animationFlag(false),
    m_animationReturnFlag(false),
    m_stageReturnSelct(false),
    m_startFade(false)
{
}

TransitionState::~TransitionState()
{
}

void TransitionState::Initialize()
{
    m_transition = std::make_unique<tito::Transition>();
    m_transition->Create();
}

void TransitionState::Update(const float& elapsedTime)
{
    if (m_startFade)
    {
        //�J�ڂ��J�n������I���̃A�j���[�V����
        if (m_animationFlag)
        {
            m_animationTime += elapsedTime;
            m_transition->SetRemderRatio(m_animationTime);

            //�A�j���[�V�������I��������J�ڂ���
            if (m_animationTime >= 1.0f)  m_stageSelct = true;

            //�J�ڂ̃A�j���[�V��������������I���
            return;
        }
    }

    //�J�ڂ̎n�܂�̃A�j���[�V����
    if (m_startFade)
    {
        //�߂�J�ڂ��J�n������I���̃A�j���[�V����
        if (m_animationReturnFlag)
        {
            m_animationTime += elapsedTime;
            m_transition->SetRemderRatio(m_animationTime);

            //�A�j���[�V�������I��������J�ڂ���
            if (m_animationTime >= 1.0f)  m_stageReturnSelct = true;

            //�J�ڂ̃A�j���[�V��������������I���
            return;
        }
    }

    //�J�ڂ̎n�܂�̃A�j���[�V����
    if (m_animationTime >= 0)
    {
        m_animationTime -= elapsedTime;
        m_transition->SetRemderRatio(m_animationTime);
    }
    else m_startFade = true;
}

void TransitionState::Render()
{
    //������������`�悵�Ȃ�
    if (m_transition->GetRemderRatio() >= 0)
        m_transition->Render();
}


