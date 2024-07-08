#pragma once
#include"IStateTutorialUI.h"

class TutorialUI;
/// <summary>
/// �A�C�e���̊��N���X���`����
/// </summary>
class NiceLetter : public IStateTutorialUI
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	NiceLetter(TutorialUI* tutorialUI);

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
	void Update(const float& elapsedTime) override;

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render() override;

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void Reset() override;

private:
	TutorialUI* m_pTutorialUI;
};
