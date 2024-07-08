#pragma once
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"

#include"StateTutorialUI/IStateTutorialUI.h"
#include"../OperationTaskUI.h"

enum TUTORIAl_UIS
{
	NONE,
	WELCOME_TO_TOWN,
	WASDQE_MOVE,
	SHIFT_STOP,
	BENCH_STREET_LIGHT_GET,
	NICE_LETTER,
	SCORE_UP_LETTER,
	COIN_GET,
	CHALLENGE_LIMITS_LETTER,
	ENEMY_AND_DES_SCORE_LETTER,
	TIME_3MINUTES_LETTER,
	RECOVERY_ITEMS_GET,
	LET_IS_RECOVER_LETTER,
	TUTORIAl_UIS_COUNT,
};

/// <summary>
/// �A�C�e���̊��N���X���`����
/// </summary>
class TutorialUI
{
public:
	//�R�C���t���O�̃Z�b�^�[
	void SetCoinGetFlag(const bool& coinGetFlag) { m_coinGetFlag = coinGetFlag; }
	bool GetCoinGetFlag() { return m_coinGetFlag; };

	//�R�C���t���O�̃Z�b�^�[
	void SetObjectsKillFlag(const bool& objectsKillFlag) { m_objectsKillFlag = objectsKillFlag; }
	bool GetObjectsKillFlag() { return m_objectsKillFlag; }

	//�R�C���t���O�̃Z�b�^�[
	void SetItemsFlag(const bool& itemsFlag) { m_itemsFlag = itemsFlag; }
	bool GetItemsFlag() { return m_itemsFlag; }

	// �R�C���t���O�̃Z�b�^�[
	void SetCoinMissionAccomplishedFlag(const bool& coinMissionAccomplishedFlag) { m_coinMissionAccomplishedFlag = coinMissionAccomplishedFlag; }
	bool GetCoinMissionAccomplishedFlag() const { return m_coinMissionAccomplishedFlag; }

	// �A�C�e���t���O�̃Z�b�^�[
	void SetItemsMissionAccomplishedFlag(const bool& itemsMissionAccomplishedFlag) { m_itemsMissionAccomplishedFlag = itemsMissionAccomplishedFlag; }
	bool GetItemsMissionAccomplishedFlag() const { return m_itemsMissionAccomplishedFlag; }

	// �I�u�W�F�N�g�L���t���O�̃Z�b�^�[
	void SetObjectKillMissionAccomplishedFlag(const bool& objectKillMissionAccomplishedFlag) { m_ObjectKillMissionAccomplishedFlag = objectKillMissionAccomplishedFlag; }
	bool GetObjectKillMissionAccomplishedFlag() const { return m_ObjectKillMissionAccomplishedFlag; }

	// �V�t�g�t���O�̃Z�b�^�[
	void SetShiftMissionAccomplishedFlag(const bool& shiftMissionAccomplishedFlag) { m_shiftMissionAccomplishedFlag = shiftMissionAccomplishedFlag; }
	bool GetShiftMissionAccomplishedFlag() const { return m_shiftMissionAccomplishedFlag; }

	// WASD�t���O�̃Z�b�^�[
	void SetWASDMissionAccomplishedFlag(const bool& WASDMissionAccomplishedFlag) { m_WASDMissionAccomplishedFlag = WASDMissionAccomplishedFlag; }
	bool GetWASDMissionAccomplishedFlag() const { return m_WASDMissionAccomplishedFlag; }

	// �R�C���t���O�̃Z�b�^�[
	void SetCoinDrawFlag(const bool& coinDrawFlag) { m_coinDrawFlag = coinDrawFlag; }
	bool GetCoinDrawFlag() const { return m_coinDrawFlag; }

	// �A�C�e���t���O�̃Z�b�^�[
	void SetItemsDrawFlag(const bool& itemsDrawFlag) { m_itemsDrawFlag = itemsDrawFlag; }
	bool GetItemsDrawFlag() const { return m_itemsDrawFlag; }

	// �I�u�W�F�N�g�L���t���O�̃Z�b�^�[
	void SetObjectKillDrawFlag(const bool& objectKillDrawFlag) { m_ObjectKillDrawFlag = objectKillDrawFlag; }
	bool GetObjectKillDrawFlag() const { return m_ObjectKillDrawFlag; }

	// �V�t�g�t���O�̃Z�b�^�[
	void SetShiftDrawFlag(const bool& shiftDrawFlag) { m_shiftDrawFlag = shiftDrawFlag; }
	bool GetShiftDrawFlag() const { return m_shiftDrawFlag; }

	// WASD�t���O�̃Z�b�^�[
	void SetWASDDrawFlag(const bool& WASDDrawFlag) { m_WASDDrawFlag = WASDDrawFlag; }
	bool GetWASDDrawFlag() const { return m_WASDDrawFlag; }

	// �^�X�N�`��t���O�̃Z�b�^�[
	void SetTaskDrawFlag(const bool& taskDrawFlag) { m_taskDrawFlag = taskDrawFlag; }
	bool GetTaskDrawFlag() const { return m_taskDrawFlag; }	

	//�X�e�[�W�J�ڃt���O�̃Z�b�^�[
	void SetSceneTransitionFlag(const bool& sceneTransitionFlag) { m_sceneTransitionFlag = sceneTransitionFlag; }
	//�X�e�[�W�J�ڃt���O�̃Z�b�^�[
	bool GetSceneTransitionFlag() {return m_sceneTransitionFlag; }

	std::unique_ptr<IStateTutorialUI>* GetTutorialUI() { return m_tutorialUI; }

	void SetCurrentState(IStateTutorialUI* iStateTutorialUI) 
	{ 
		m_pCurrentState = iStateTutorialUI;
		m_pCurrentState->Reset();
	}

	void SetPraiseUis(const TUTORIAl_UIS& tutorialUis) { m_praiseUis = tutorialUis; }
	TUTORIAl_UIS GetPraiseUis() { return m_praiseUis; }

	void SetNiceUis(const TUTORIAl_UIS& tutorialUis) { m_niceUis = tutorialUis; }
	TUTORIAl_UIS GetNiceUis() { return m_niceUis; }

	static const float FADE_TIME;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TutorialUI();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~TutorialUI();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
	virtual void Update(const float& elapsedTime);

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render();

	/// <summary>
	/// ��n��
	/// </summary>
	virtual void Finalize();

private:

	std::unique_ptr<IStateTutorialUI> m_tutorialUI[TUTORIAl_UIS::TUTORIAl_UIS_COUNT];

	//�^�X�N�̏��Ԃ�\��
	enum TUTORIAl_TASK_UI
	{
		WASD,
		SHIFT_STOP,
		COIN_GET,
		OBJECTS_BREAK,
		ITEMS_GET,
		TUTORIAl_TASK_COUNT,
	};
	std::unique_ptr<OperationTaskUI> m_tutorialTaskUIs[TUTORIAl_TASK_UI::TUTORIAl_TASK_COUNT];

	std::unique_ptr<TutorialLetter> m_tutorialTaskListLetter;

	IStateTutorialUI* m_pCurrentState;

	//�R�C�����Ƃ�����
	bool m_coinGetFlag;

	//�R�C�����Ƃ�����
	bool m_objectsKillFlag;

	//���̂�j�󂵂���
	bool m_itemsFlag;

	//�V�[���J�ڃt���O
	bool m_sceneTransitionFlag;

	bool m_taskDrawFlag;
	bool m_WASDMissionAccomplishedFlag;
	bool m_coinMissionAccomplishedFlag;
	bool m_shiftMissionAccomplishedFlag;
	bool m_itemsMissionAccomplishedFlag;
	bool m_ObjectKillMissionAccomplishedFlag;
	bool m_WASDDrawFlag;
	bool m_coinDrawFlag;
	bool m_shiftDrawFlag;
	bool m_itemsDrawFlag;
	bool m_ObjectKillDrawFlag;
	//���ɍs�������V�[���̊Ԃɕ�����g�p���镶�������������Ɏg��
	TUTORIAl_UIS m_niceUis;

	//���̎��ɍs�������V�[���̊Ԃɕ�����g�p���镶�������������Ɏg��
	TUTORIAl_UIS m_praiseUis;
};
