#pragma once
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"
/// <summary>
/// �A�C�e���̊��N���X���`����
/// </summary>
class TutorialLetters
{
public:
	//�R�C���t���O�̃Z�b�^�[
	void SetCoinGetFlag(const bool& coinGetFlag) { m_coinGetFlag = coinGetFlag; }

	//�R�C���t���O�̃Z�b�^�[
	void SetObjectsKillFlag(const bool& objectsKillFlag) { m_objectsKillFlag = objectsKillFlag; }

	//�X�e�[�W�J�ڃt���O�̃Z�b�^�[
	void SetSceneTransitionFlag(const bool& sceneTransitionFlag) { m_sceneTransitionFlag = sceneTransitionFlag; }
	//�X�e�[�W�J�ڃt���O�̃Z�b�^�[
	bool GetSceneTransitionFlag() {return m_sceneTransitionFlag; }

	static const float FADE_TIME;


	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TutorialLetters();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~TutorialLetters();

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
	std::unique_ptr<TutorialLetter> m_WelcomeToTownLetter;
	std::unique_ptr<TutorialLetter> m_challengeLimitsLetter;
	std::unique_ptr<TutorialLetter> m_CoinGetLtter;
	std::unique_ptr<TutorialLetter> m_EnemyAndDesScoreLetter;
	std::unique_ptr<TutorialLetter> m_niceLetter;
	std::unique_ptr<TutorialLetter> m_niceLetter_02;
	std::unique_ptr<TutorialLetter> m_ScoreUpLetter;
	std::unique_ptr<TutorialLetter> m_ScoreUpLetter_02;
	std::unique_ptr<TutorialLetter> m_Time3minutesLetter;
	std::unique_ptr<TutorialLetter> m_BenchStreetLightGetLtter;

	std::unique_ptr<tito::OperationUI> m_operationUI[1];
	float m_timer;

	float m_adjustedTime;

	//�R�C�����Ƃ�����
	bool m_coinGetFlag;

	//���̂�j�󂵂���
	bool m_objectsKillFlag;

	bool m_sceneTransitionFlag;
};
