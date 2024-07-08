//--------------------------------------------------------------------------------------
// File: UserResources.h
//
// �V�[���֓n�����[�U�[���\�[�X�N���X�i�T���v���j
//
// Date: 2023.4.13
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "StepTimer.h"
#include "ImaseLib/DebugFont.h"
#include"Scene/GameObjects/ScoreCalculation/ScoreCalculation.h"
// �e�V�[���ɓn�����ʃ��\�[�X���L�q���Ă�������
class UserResources
{
private:

	// �X�e�b�v�^�C�}�[
	DX::StepTimer* m_timer;

	ScoreCalculation* m_scoreCalculation;
	// ���ʃX�e�[�g
	DirectX::CommonStates* m_states;

public:

	// �R���X�g���N�^
	UserResources()
		: m_timer(nullptr)
		,m_scoreCalculation(nullptr)
	{
	}

	// ------------------------------------------ //
	// ���ʃX�e�[�g	
	// ------------------------------------------ //

	// ���ʃX�e�[�g��ݒ肷��֐�
	void SetCommonStates(DirectX::CommonStates* states) { m_states = states; }

	// ���ʃX�e�[�g���擾����֐�
	DirectX::CommonStates* GetCommonStates() { return m_states; }

	// ------------------------------------------ //
	// �X�e�b�v�^�C�}�[	
	// ------------------------------------------ //

	// �X�e�b�v�^�C�}�[��ݒ肷��֐�
	void SetStepTimerStates(DX::StepTimer* timer) { m_timer = timer; }

	// �X�e�b�v�^�C�}�[���擾����֐�
	DX::StepTimer* GetStepTimer() { return m_timer; }

	// ------------------------------------------ //
	// �X�R�A	
	// ------------------------------------------ //

	// �X�R�A��ݒ肷��֐�
	void SetScoreCalculation(ScoreCalculation* scoreCalculation) { m_scoreCalculation = scoreCalculation; }

	// �X�R�A���擾����֐�
	ScoreCalculation* GetScoreCalculation() { return m_scoreCalculation; }
};

