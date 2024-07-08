#pragma once

#include"Scene/GameObjects/UI/Timer/Timer.h"
#include"Scene/GameObjects/UI/FreeUi/FreeUi.h"
class ScoreCount
{
public:
	const int ENEMY_SCORE = 1000;
	const int ENEMY_TURRET_SCORE = 10000;
	const int BENCH_SCORE=500;
	const int STREET_LIGHT_SCORE=300;
	const int COIN_SCORE = 3000;
	const int FENCE_SCORE = 2000;

	enum KindsScore
	{
		ENEMY,
		TURRET,
		BENCH,
		STREET_LIGHT,
		COIN,
		FENCE,

		COUNT
	};
	KindsScore GetKindsScore()const { return m_kindsScore; }
	int GetCount()const { return m_count; }
	void SetCount(const int& count) { m_count = count; }
	int GetScore()const { return m_score; }
	ScoreCount(KindsScore kindsScore, int count) :
		m_kindsScore(kindsScore),
		m_count(count) {
		switch (m_kindsScore)
		{
		case ScoreCount::KindsScore::BENCH:
			m_score =BENCH_SCORE;
			break;
		case ScoreCount::KindsScore::COIN:
			m_score = COIN_SCORE;
			break;
		case ScoreCount::KindsScore::ENEMY:
			m_score = ENEMY_SCORE;
			break;
		case ScoreCount::KindsScore::STREET_LIGHT:
			m_score = STREET_LIGHT_SCORE;
			break;
		case ScoreCount::KindsScore::TURRET:
			m_score = ENEMY_TURRET_SCORE;
			break;
		case ScoreCount::KindsScore::FENCE:
			m_score = FENCE_SCORE;
			break;
		default:
			break;

		}
	};

	~ScoreCount() {};
private:
	KindsScore m_kindsScore;
	int m_count;
	int m_score;
};
/// <summary>
/// �n�ʂ̃N���X���`����
/// </summary>
class ScoreCalculation
{
public:

	void SetScoreCount(ScoreCount::KindsScore kindsScore, int killCount) {
			m_scoreCounts[kindsScore]->SetCount(killCount);
	};

	TimerTex* GetTimerTex() { return m_totalScoreTex.get(); }

	void SetTimer(const float& timer) { m_timer = timer; }
	//�X�e�[�W�J�ڃt���O�̃Z�b�^�[
	bool GetSceneTransitionFlag() { return m_sceneTransitionFlag; }

	//�X�R�A�̃Q�b�^�[
	int GetScore() { return m_score; };
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ScoreCalculation();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ScoreCalculation();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(const float& elapsedTime);

	/// <summary>
	/// �X�V����
	/// </summary>
	void PlaySceneUpdate();

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize();

private:
	std::unique_ptr<ScoreCount> m_scoreCounts[ScoreCount::KindsScore::COUNT];

	int m_score;

	bool m_sceneTransitionFlag;
	float m_timer;
	std::unique_ptr<TimerTex> m_totalScoreTex;
	std::vector<std::unique_ptr<TimerTex>> m_kindsOneScoreTex;
	std::vector<std::unique_ptr<TimerTex>> m_kindsCountTex;
	std::vector<std::unique_ptr<TimerTex>> m_kindsScoreTex;
	std::vector<std::unique_ptr<FreeUi>> m_asterisk;
	std::vector<std::unique_ptr<FreeUi>> m_equal;
	std::vector<std::unique_ptr<tito::UserInterface>> m_ResultBaseLetter;

};
