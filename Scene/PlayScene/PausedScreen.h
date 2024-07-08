#pragma once

#include"Scene/GameObjects/UI/TransitionState.h"
#include"ImaseLib/SceneManager.h"
#include"ImaseLib/MoveUserInterface.h"
#include"ImaseLib/UserInterface.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include "Scene/GameObjects/FiniteStateMachine.h"

class PlayScene;
class UserResources;

/// <summary>
/// PausedScreen�̃N���X���`����
/// </summary>
class PausedScreen 
{
public:	
	enum OptionState
	{
		OPTION_SCENE,
		DRAW_OPTION_SCENE,
		SOUND_OPTION_SCENE,
		COUNTs
	};

	enum  PausedState
	{
		RESUME_GAME,
		STAGE_SELECT_SCENE,
		PLAYER_CUSTOM_SCENE,
		COUNT,
	};

	PausedScreen(Imase::Scene<UserResources>* playScene) ;
	~PausedScreen();

	// ������
	void Initialize() ;

	// �X�V
	bool Update(float elapsedTime);

	// �`��
	void Render() ;

	// �I������
	void Finalize() ;

	void Enter();
	void Exit() ;

	// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateDeviceDependentResources() ;

public:
	bool GetMenuFlag()const { return m_menuSceneFlag; };
	void SetMenuFlag(const bool& menuFlag) { m_menuSceneFlag = menuFlag; };

	void MenuInitialize();

	void MenuUpdate();
//menu
private:
	Imase::Scene<UserResources>* m_pPlayScene;
	bool m_menuSceneFlag;
	bool m_menuSceneSelectFlag;
	//�X�e�[�W�Z���N�g�̃|�C���^
	std::unique_ptr<TransitionState> m_transitionState;

	//�X�e�[�W�Z���N�g�̃|�C���^
	std::unique_ptr<TransitionState> m_Translucent;
public:
	using FSM = FiniteStateMachine<PausedScreen, OptionState>;
	using State = FSM::IState;

private:

	// ��ԑJ��
	std::unique_ptr<FSM> m_fsm;                //!< �L���X�e�[�g�}�V��
	std::unique_ptr<State> m_State[OptionState::COUNTs];    //!< [�X�e�[�g]�H����T�� 

private:
	//�z�[���̕���
	std::unique_ptr <tito::UserInterface> m_homeLetter[PausedState::COUNT];

	//�z�[���̕����̓����蔻��
	std::unique_ptr <Collider::Box2D> m_homeLetterCollision[PausedState::COUNT];

	//�I�𒆂̘g
	std::unique_ptr <tito::MoveUserInterface> m_underBar;

};

class StateSoundOnScene : public PausedScreen::State
{

public:
	StateSoundOnScene(PausedScreen::FSM* fsm) :m_fsm(fsm){};
	~StateSoundOnScene() {};
	// ������
	void Initialize() override {};

	// �X�V
	void Update(const float& elapsedTime) override { elapsedTime; };

	// �`��
	void Render() override {};

	// �I������
	void Finalize() override {};

	void Enter()override {};
	void Exit() override {};

	// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateDeviceDependentResources() override {};

private:
	PausedScreen::FSM* m_fsm;
};
