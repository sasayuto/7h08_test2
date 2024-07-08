#pragma once
class PlayScene;
class StatePauseScene;
#include"Scene/GameObjects/UI/Letter/StageSelectLetter.h"
#include"Scene/GameObjects/UI/UnderBar/UnderBar.h"

/// <summary>
/// StageSelect�̃N���X���`����
/// </summary>
class PauseSelect
{
public:
	/// <summary>
/// ���j���[��ʂ̎�ށi���ԂɂȂ�j
/// </summary>
	const enum Pause
	{
		STAGE_SELECT,
		TITLE,
		PAUSE_COUNT
	};

		//UI�̏c��
		static const int WIDTH = 90;


	//�I�����Ă���ԍ��̃Q�b�^�[�A�Z�b�^�[
	int GetSelectNum() const{ return m_selectNum; }
	void SetSelectNum(const int& selectNum) { m_selectNum = selectNum; }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PauseSelect();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PauseSelect();
	
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="titleScene"></param>
	void Initialize(PlayScene* playScene);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="selectFlag"></param>
	void Update(const bool& selectFlag, const bool& animationFlag);

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

	bool GetGameStop()const { return m_gameStop; }

	void SetGameStop(const bool& gameStop) { m_gameStop = gameStop; }
private:
	//��Ԃ̃|�C���^
	std::unique_ptr<StatePauseScene> m_select[Pause::PAUSE_COUNT];
	// ���݂̏�Ԃ̃|�C���^
	StatePauseScene* m_pCurrentState;

	//�^�C�g���V�[���̃|�C���^
	PlayScene* m_titleScene;

	//�I�����Ă���ԍ�
	int m_selectNum;

	bool m_gameStop;
private:
	//�w�i�̘f��
	std::unique_ptr <StageSelectLetter> m_object[Pause::PAUSE_COUNT];

	//���f��
	std::unique_ptr <UnderBar> m_underBar;

};

