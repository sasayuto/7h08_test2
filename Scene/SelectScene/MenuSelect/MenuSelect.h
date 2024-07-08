#pragma once
#include"StateManuScene/StateMenuScene.h"

class TitleScene;

/// <summary>
/// ���j���[��ʂ̎�ށi���ԂɂȂ�j
/// </summary>
const enum Menu
{
	STAGE_SELECT,
	OPTION,
	TITLE,
	MENU_COUNT
};

/// <summary>
/// StageSelect�̃N���X���`����
/// </summary>
class MenuSelect
{
public:
		//UI�̏c��
		static const int WIDTH = 90;


	//�I�����Ă���ԍ��̃Q�b�^�[�A�Z�b�^�[
	int GetSelectNum() const{ return m_selectNum; }
	void SetSelectNum(const int& selectNum) { m_selectNum = selectNum; }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	MenuSelect();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MenuSelect();
	
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="titleScene"></param>
	void Initialize(TitleScene* titleScene);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="selectFlag"></param>
	void Update(const bool& selectFlag, const bool& selectStartFlag);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize();

	/// <summary>
	/// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	/// </summary>
	void CreateDeviceDependentResources();

private:
	//��Ԃ̃|�C���^
	std::unique_ptr<StateMenuScene> m_select[Menu::MENU_COUNT];

	// ���݂̏�Ԃ̃|�C���^
	StateMenuScene* m_pCurrentState;

	//�^�C�g���V�[���̃|�C���^
	TitleScene* m_titleScene;

	//�I�����Ă���ԍ�
	int m_selectNum;
private:
	//�w�i�̘f��
	std::unique_ptr <StageSelectLetter> m_object[Menu::MENU_COUNT];

	//���f��
	std::unique_ptr <UnderBar> m_underBar;
	MenuSelect* m_pMenuSelect;



};

