#pragma once

#include"StateMenuScene.h"
class TitleScene;

/// <summary>
/// SelectGrandCanyon�̃N���X���`����
/// </summary>
class OptionSelectScene :public StateMenuScene
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="titleScene">�^�C�g���V�[���̃A�h���X</param>
	OptionSelectScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~OptionSelectScene()override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="selectFlag">�V�[���J�ڂ̃t���O</param>
	void Update(const bool& selectFlag)override;

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render()override;


	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize()override;
};

