//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// ÉQÅ[ÉW
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "TransitionEnd.h"

using namespace DirectX;

TransitionEnd::TransitionEnd() :
    m_state(1),
    m_transition(nullptr)
{
}

TransitionEnd::~TransitionEnd()
{
}

void TransitionEnd::Initalize()
{
    m_transition = std::make_unique<tito::Transition>();
    m_transition->Create();
}

void TransitionEnd::Update(const float& elapsedTime)
{
    if (m_state>=0)
    {
        m_state -= elapsedTime;
        m_transition->SetRemderRatio(m_state);
    }
}

void TransitionEnd::Render()
{
    m_transition->Render();
}

