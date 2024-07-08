//--------------------------------------------------------------------------------------
// File: ChangeSoundOptionScene.h
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
//--------------------------------------------------------------------------------------
#pragma once
#include"../StateOptionScene.h"
class ChangeSoundOptionScene : public StateOptionScene::State
{
public:


	ChangeSoundOptionScene(StateOptionScene::FSM* fsm);
	~ChangeSoundOptionScene();

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


public:

private:
	//
	StateOptionScene::FSM* m_fsm;

	// �}�E�X�g���b�J�[
	DirectX::Mouse::ButtonStateTracker m_mstracker;

};

