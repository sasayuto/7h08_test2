#pragma once

#include"ISelectPlayScene.h"

class StageSelectScene;
#include"Scene/GameObjects/UI/FreeUi/FreeUi.h"
/// <summary>
/// SelectTown�̃N���X���`����
/// </summary>
class Tutorial :public ISelectPlayScene
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="titleScene">�^�C�g���V�[���̃A�h���X</param>
	Tutorial();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Tutorial()override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="selectFlag">�V�[���J�ڂ̃t���O</param>
	void Update(const bool& selectFlag, const bool& selectStartFlag)override;

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render()override;

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize()override;
private:
	//�w�i�̘f��
	std::unique_ptr <FreeUi> m_StageUI;

};

