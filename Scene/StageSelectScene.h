#pragma once

#include "ImaseLib/SceneManager.h"
#include "UserResources.h"
#include"Scene/GameObjects/UI/TransitionState.h"
#include"Scene/GameObjects/UI/Letter/StageSelectLetter.h"
#include"Scene/GameObjects/UI/Letter/returnLetter/ReturnLetter.h"
#include"Scene/GameObjects/Camera/TitleCamera.h"
#include"Scene/GameObjects/PlayScene/Sun/Sun.h"
#include"Scene/GameObjects/SelectScene/SelectPlayer.h"
#include"Scene/StageSelect/StageSelect.h"
#include"Scene/GameObjects/SelectScene/Palace/Palace.h"
class StageSelectScene : public Imase::Scene<UserResources>
{
public:

	static const float TRANSITION_TIME;
public:
	StageSelectScene();
	~StageSelectScene() override;

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
		/// <summary>
	/// �e�ɂȂ�I�u�W�F�N�g�̕`��
	/// </summary>
	void ShadowMapRender();

private:
	std::unique_ptr<TransitionState> m_transitionState;

	std::unique_ptr <StageSelect> m_stageSelect;

	std::unique_ptr <TitleCamera> m_titleCamera;

	std::unique_ptr <ReturnLetter> m_returnLetter;
	std::unique_ptr <Sun> m_sun;
	std::unique_ptr <StageSelectLetter> m_stageSelectLetter;
	std::unique_ptr <tito::MoveUserInterface> m_decision;
	std::unique_ptr <Collider::Box2D> m_decisionCol;
	bool m_m_decisionFlag;

	//�{�a�̃|�C���^
	std::unique_ptr <Palace> m_palace;

	//�v���C���[�̃|�C���^
	std::unique_ptr <SelectPlayer> m_player;


	//���肵�Ă���J�ڂ���܂ł̎���
	float m_decisionStopTimer;

	//���肵�����̃t���O
	bool m_decisionFlag;

	//�߂�̌��肵�����̃t���O
	bool m_ReturnDecisionFlag;
	float m_timerShadowSpeed;

	/// <summary>
	/// �J�ڂ���Ƃ��̏���
	/// </summary>
	/// <param name="transitionTime">���肪������Ă���J�ڂ���܂ł̎���</param>
	void TransitionProcessing(const float& elapsedTime,const float& transitionTime);



};

