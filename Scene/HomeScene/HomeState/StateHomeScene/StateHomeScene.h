//--------------------------------------------------------------------------------------
// File: StateHomeScene.h
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
//--------------------------------------------------------------------------------------
#pragma once
#include"Scene/HomeScene/HomeScene.h"
#include"ImaseLib/MoveUserInterface.h"
#include"ImaseLib/UserInterface.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
class StateHomeScene : public HomeScene::State
{
public:
	enum  HomeState
	{
		STAGE_SELECT_SCENE,
		PLAYER_CUSTOM_SCENE,
		OPTION_SCENE,
		COUNT,
		RETURN_SCENE,//���ɂ��g��Ȃ��̂�Count�̉�
		NONE_SCENE
	};

	StateHomeScene(HomeScene::FSM* fsm);

	~StateHomeScene();
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

	tito::MoveUserInterface* GetUnderBar()const { return m_underBar.get(); }
public:
	using FSM = FiniteStateMachine<StateHomeScene, HomeState>;
	using State = FSM::IState;

private:
	//
	HomeScene::FSM* m_pParentFsm;

	// ��ԑJ��
	std::unique_ptr<FSM> m_fsm;                //!< �L���X�e�[�g�}�V��
	std::unique_ptr<State> m_StateOptionScene;         //!< [�X�e�[�g]�H�ׂ�
	std::unique_ptr<State> m_StatePlayerCustomScene;         //!< [�X�e�[�g]�H�ׂ�
	std::unique_ptr<State> m_StateStageSelectScene;         //!< [�X�e�[�g]�H�ׂ�
	std::unique_ptr<State> m_StateHomeReturnScene;         //!< [�X�e�[�g]�H�ׂ�
	std::unique_ptr<State> m_StateNoneScene;         //!< [�X�e�[�g]�H�ׂ�


private:
	//�z�[���̕���
	std::unique_ptr <tito::UserInterface> m_homeLetter[HomeState::COUNT];

	//�z�[���̕����̓����蔻��
	std::unique_ptr <Collider::Box2D> m_homeLetterCollision[HomeState::COUNT];

	//�I�𒆂̘g
	std::unique_ptr <tito::MoveUserInterface> m_underBar;
};

