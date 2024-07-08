#pragma once
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"
/// <summary>
/// �A�C�e���̊��N���X���`����
/// </summary>
class IStateTutorialUI
{
public:
	TutorialLetter* GetTextLetter() { return m_textLetter.get(); };

	float GetTimer() { return m_timer; };
	void SetTimer(float timer) { m_timer = timer; };

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	IStateTutorialUI() :
		m_timer(),
		m_textLetter()
	{
		m_textLetter = std::make_unique<TutorialLetter>();
	}
	/// <summary>
	/// ���z�f�X�g���N�^
	/// </summary>
	virtual ~IStateTutorialUI() = default;

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
	virtual void Update(const float& elapsedTime) = 0;

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// ��n��
	/// </summary>
	virtual void Finalize() = 0;

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	virtual void Reset() = 0;

private:
	std::unique_ptr<TutorialLetter> m_textLetter;

	float m_timer;
};
