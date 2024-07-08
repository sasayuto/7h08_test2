//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// ゲージ
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
        //遷移が開始したら終わりのアニメーション
        if (m_animationFlag)
        {
            m_animationTime += elapsedTime;
            m_transition->SetRemderRatio(m_animationTime);

            //アニメーションが終了したら遷移する
            if (m_animationTime >= 1.0f)  m_stageSelct = true;

            //遷移のアニメーション中だったら終わり
            return;
        }
    }

    //遷移の始まりのアニメーション
    if (m_startFade)
    {
        //戻る遷移が開始したら終わりのアニメーション
        if (m_animationReturnFlag)
        {
            m_animationTime += elapsedTime;
            m_transition->SetRemderRatio(m_animationTime);

            //アニメーションが終了したら遷移する
            if (m_animationTime >= 1.0f)  m_stageReturnSelct = true;

            //遷移のアニメーション中だったら終わり
            return;
        }
    }

    //遷移の始まりのアニメーション
    if (m_animationTime >= 0)
    {
        m_animationTime -= elapsedTime;
        m_transition->SetRemderRatio(m_animationTime);
    }
    else m_startFade = true;
}

void TransitionState::Render()
{
    //透明だったら描画しない
    if (m_transition->GetRemderRatio() >= 0)
        m_transition->Render();
}


