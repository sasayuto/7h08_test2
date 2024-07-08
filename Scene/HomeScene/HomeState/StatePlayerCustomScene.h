//--------------------------------------------------------------------------------------
// File: StateHomeScene.h
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
//--------------------------------------------------------------------------------------
#pragma once
#include"Scene/HomeScene/HomeScene.h"

class StatePlayerCustomScene : public HomeScene::State
{
public:

	StatePlayerCustomScene(HomeScene::FSM* fsm);
	~StatePlayerCustomScene();
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
	HomeScene::FSM* m_fsm;
	//�z�[���̕���
	std::unique_ptr <tito::UserInterface> m_Letter;

	//�I�𒆂̘g
	std::unique_ptr <tito::MoveUserInterface> m_underBar;

};

