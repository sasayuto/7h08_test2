//--------------------------------------------------------------------------------------
// File: ChangeStageSelectScene.h
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
//--------------------------------------------------------------------------------------
#pragma once
#include "../StateHomeScene.h"

class ChangeHomeReturnScene : public StateHomeScene::State
{
public:

	ChangeHomeReturnScene(StateHomeScene::FSM* fsm);
	~ChangeHomeReturnScene();

	// ������
	void Initialize() override;

	// �X�V
	void Update(const float& elapsedTime) override;

	// �`��
	void Render() override;

	// �I������
	void Finalize() override;

	void Enter()override;
	void Exit() override;

	// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateDeviceDependentResources() override;

private:
	//
	StateHomeScene::FSM* m_fsm;

};

