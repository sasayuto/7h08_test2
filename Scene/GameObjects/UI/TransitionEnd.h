//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// ���j���[�N���X
//
//-------------------------------------------------------------------------------------

#pragma once

#include "ImaseLib/Transition.h"

class TransitionEnd
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TransitionEnd();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TransitionEnd();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pDR">�f�o�C�X���\�[�V�[�Y�̃|�C���^</param>
	void Initalize();

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
	//�J�ڂ̃|�C���^
	std::unique_ptr<tito::Transition> m_transition;

	//�X�^�[�g
	float m_state;
};