#pragma once
#include"Scene/GameObjects/UI/Letter/StageSelectLetter.h"
#include"Scene/GameObjects/UI/UnderBar/UnderBar.h"

class MenuSelect;
class TitleScene;

/// <summary>
/// ISelectPlayScene�C���^�[�t�F�C�X���`����
/// </summary>
class StateMenuScene
{
public:
	TitleScene* GetTitleScene() { return m_pTitleScene; }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	StateMenuScene();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize(MenuSelect* menuSelect, TitleScene* titleScene);

	/// <summary>
	/// ���������s����
	/// </summary>
	/// <param name="elapsedTime">�I������</param>
	virtual void Update(const bool& selectFlag) = 0;

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// ��n��������
	/// </summary>
	virtual void Finalize() = 0;

	/// <summary>
	/// ���z�f�X�g���N�^
	/// </summary>
	virtual ~StateMenuScene() = default;

private:
	MenuSelect* m_pMenuSelect;
	TitleScene* m_pTitleScene;
};
