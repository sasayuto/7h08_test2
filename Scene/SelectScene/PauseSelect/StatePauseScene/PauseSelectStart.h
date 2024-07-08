#pragma once

#include"StatePauseScene.h"
class TitleScene;

/// <summary>
/// SelectGrandCanyon�̃N���X���`����
/// </summary>
class PauseSelectStart :public StatePauseScene
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="titleScene">�^�C�g���V�[���̃A�h���X</param>
	PauseSelectStart();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PauseSelectStart()override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="selectFlag">�V�[���J�ڂ̃t���O</param>
	void Update(const bool& selectFlag, const bool& animationFlag)override;

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render()override;


	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize()override;
};

