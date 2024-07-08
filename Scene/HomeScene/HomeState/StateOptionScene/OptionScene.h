//--------------------------------------------------------------------------------------
// File: StateIteme.h
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
//--------------------------------------------------------------------------------------
#pragma once
#include"Scene/HomeScene/HomeScene.h"

class OptionScene : public HomeScene::State
{
public:
	enum class OptionState
	{
		OPTION_SCENE,
		DRAW_OPTION_SCENE,
		SOUND_OPTION_SCENE
	};

	OptionScene(HomeScene::FSM* fsm);
	~OptionScene();
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

	HomeScene::FSM* GetParentFSM() { return m_pParentFsm; }

public:
	using FSM = FiniteStateMachine<OptionScene, OptionState>;
	using State = FSM::IState;

private:
	HomeScene::FSM* m_pParentFsm;


	// ��ԑJ��
	std::unique_ptr<FSM> m_fsm;                //!< �L���X�e�[�g�}�V��
	std::unique_ptr<State> m_StateDrawOptionScene;         //!< [�X�e�[�g]�H�ׂ�
	std::unique_ptr<State> m_StateSoundOptionScene;         //!< [�X�e�[�g]�H�ׂ�
	std::unique_ptr<State> m_StateOptionScene;         //!< [�X�e�[�g]�H�ׂ�

};

