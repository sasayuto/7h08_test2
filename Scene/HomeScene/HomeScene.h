//--------------------------------------------------------------------------------------
// File: MenuScene.h
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
//--------------------------------------------------------------------------------------
#pragma once
#include "ImaseLib/SceneManager.h"
#include "UserResources.h"
#include "Scene/StageSelectScene.h"
#include "Scene/GameObjects/FiniteStateMachine.h"
#include"Scene/GameObjects/UI/MenuBackGround/MenuBackGroundUI.h"
#include"Scene/GameObjects/Camera/TitleCamera.h"
#include"Scene/GameObjects/Background/CloudyBackGround.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/StoneFloor.h"

class HomeScene : public Imase::Scene<UserResources>
{
	// �N���X�萔
public:

	//UI�̏c��
	static const int LETTER_WIDTH = 90;


	enum HomeState
	{
		STAGE_SELECT_SCENE,
		PLAYER_CUSTOM_SCENE,
		OPTION_SCENE,
		HOME_SCENE,
		COUNT
	};

public:
	// ������
	void Initialize() override;

	// �X�V
	void Update(float elapsedTime) override;

	// �`��
	void Render() override;

	// �I������
	void Finalize() override;

	// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateDeviceDependentResources() override;

	// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateWindowSizeDependentResources() override;

	// �f�o�C�X���X�g�������ɌĂяo�����֐�
	void OnDeviceLost() override;

	TransitionState* GetTransitionState() { return m_transitionState.get(); }
	ReturnLetter* GetReturnLetter() { return m_returnLetter.get(); }
	// �G�C���A�X�錾
public:
	using FSM = FiniteStateMachine<HomeScene, HomeState>;
	using State = FSM::IState;

private:
	/// <summary>
	/// 
	/// </summary>
	void SaveGunData();

private:

	// ��ԑJ��
	std::unique_ptr<FSM> m_fsm;                //!< �L���X�e�[�g�}�V��
	std::unique_ptr<State> m_State[COUNT];    //!< [�X�e�[�g]�H����T�� 

private:
	std::unique_ptr<TransitionState> m_transitionState;
	std::unique_ptr<ReturnLetter> m_returnLetter;
	std::unique_ptr<TitleCamera> m_camera;
	std::unique_ptr<CloudyBackGround> m_CloudyBackGround;
	//�w�i���f��
	std::unique_ptr<StoneFloor> m_stoneFloor;

};
