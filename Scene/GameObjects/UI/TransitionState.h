#pragma once

#include "ImaseLib/Transition.h"

/// <summary>
/// �V�[���J�ڂ̃A�j���[�V�����̃N���X���`����
/// </summary>
class TransitionState
{
public:
	//�V�[���J�ڃt���O�̃Q�b�^�[
	bool GetStageSelct() const { return m_stageSelct; }

	//�V�[���J�ڃt���O�̃Q�b�^�[
	bool GetStageReturnSelct() const { return m_stageReturnSelct; }

	//�A�j���[�V�����t���O�̃Q�b�^�[�A�Z�b�^�[
	bool GetAnimationFlag() const { return m_animationFlag; }
	void SetAnimationFlag(const bool& animationFlag) { m_animationFlag = animationFlag; }

	void SetAnimationReturnFlag(const bool& animationreturnFlag) { m_animationReturnFlag = animationreturnFlag; }

	//�A�j���[�V�����^�C���̃Q�b�^�[
	float GetAnimationTime() const { return m_animationTime; }
	void SetAnimationTime(const float& animationTime) {
		m_animationTime = animationTime;
		m_transition->SetRemderRatio(m_animationTime);
	}

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TransitionState();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TransitionState();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
	void Update(const float& elapsedTime);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

private:
	//�V�[���J�ڂ̃A�j���[�V�����̃|�C���^
	std::unique_ptr<tito::Transition> m_transition;

	//�A�j���[�V�����̎���
	float m_animationTime;

	//�V�[���J�ڃA�j���[�V�������J�n����t���O
	bool m_animationFlag;

	//�V�[���J�ڃt���O
	bool m_stageSelct;

	//�߂�V�[���J�ڃA�j���[�V�������J�n����t���O
	bool m_animationReturnFlag;

	//�߂�V�[���J�ڃt���O
	bool m_stageReturnSelct;

	bool m_startFade;
};