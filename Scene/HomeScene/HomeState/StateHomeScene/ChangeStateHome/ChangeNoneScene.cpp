//--------------------------------------------------------------------------------------
// File: ChangeNoneScene.cpp
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "ChangeNoneScene.h"

using namespace DirectX;

ChangeNoneScene::ChangeNoneScene(StateHomeScene::FSM* fsm)
{
	m_fsm = fsm;
}

ChangeNoneScene::~ChangeNoneScene()
{
}

// ������
void ChangeNoneScene::Initialize()
{
	CreateDeviceDependentResources();

}

// �X�V
void ChangeNoneScene::Update(const float& elapsedTime)
{
}

// �`��
void ChangeNoneScene::Render()
{
}

// �I������
void ChangeNoneScene::Finalize()
{
}

void ChangeNoneScene::Enter()
{
	//�����g�̈ʒu���ړ�(�Ԃ���΂��[)
	m_fsm->GetOwner()->GetUnderBar()->SetPosition(DirectX::SimpleMath::Vector2(10000,10000));
}

void ChangeNoneScene::Exit()
{
}

void ChangeNoneScene::CreateDeviceDependentResources()
{
}
