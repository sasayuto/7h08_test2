//--------------------------------------------------------------------------------------
// File: StateHome.h
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
//--------------------------------------------------------------------------------------
#pragma once
#include"../../OptionScene.h"

class StateOptionScene : public OptionScene::State
{
public:
	enum OptionState
	{
		DRAW_OPTION_SCENE,
		SOUND_OPTION_SCENE,
		COUNT
	};

	StateOptionScene(OptionScene::FSM* fsm);
	~StateOptionScene();
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

	OptionScene::FSM* GetParentFSM() { return m_pParentFsm; }

	tito::MoveUserInterface* GetUnderBar()const { return m_underBar.get(); }

public:
	using FSM = FiniteStateMachine<StateOptionScene, OptionState>;
	using State = FSM::IState;

private:
	//
	OptionScene::FSM* m_pParentFsm;


	// ��ԑJ��
	std::unique_ptr<FSM> m_fsm;                //!< �L���X�e�[�g�}�V��
	std::unique_ptr<State> m_StateDrawOptionScene;         //!< [�X�e�[�g]�H�ׂ�
	std::unique_ptr<State> m_StateSoundOptionScene;         //!< [�X�e�[�g]�H�ׂ�

private:
	//�z�[���̕���
	std::unique_ptr <tito::UserInterface> m_optionLetter[OptionState::COUNT];

	//�z�[���̕����̓����蔻��
	std::unique_ptr <Collider::Box2D> m_optionLetterCollision[OptionState::COUNT];

	std::unique_ptr <tito::MoveUserInterface> m_underBar;

};

