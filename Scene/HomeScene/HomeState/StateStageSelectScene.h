//--------------------------------------------------------------------------------------
// File: StateIteme.h
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
//--------------------------------------------------------------------------------------
#pragma once
#include"Scene/HomeScene/HomeScene.h"
#include"../HomeState/StateHomeScene/StateHomeScene.h"
class StateStageSelectScene : public HomeScene::State
{
public:

	StateStageSelectScene(HomeScene::FSM* fsm);
	~StateStageSelectScene();
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
	std::unique_ptr <tito::UserInterface> m_homeLetter[StateHomeScene::HomeState::COUNT];


};

