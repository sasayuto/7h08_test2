//--------------------------------------------------------------------------------------
// File: ChangeStateGunCustom.h
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
//--------------------------------------------------------------------------------------
#pragma once
#include "../StateHomeScene.h"

class ChangePlayerCustomScene : public StateHomeScene::State
{
public:

	ChangePlayerCustomScene(StateHomeScene::FSM* fsm);
	~ChangePlayerCustomScene();

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

