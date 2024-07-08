#pragma once
#include"Scene/GameObjects/UI/Letter/StageSelectLetter.h"
#include"Scene/GameObjects/UI/UnderBar/UnderBar.h"

class PauseSelect;
class PlayScene;

/// <summary>
/// ISelectPlayScene�C���^�[�t�F�C�X���`����
/// </summary>
class StatePauseScene
{
public:
	PlayScene* GetPlayScene() { return m_pPlayScene; }

	PauseSelect* GetPauseSelect() { return m_pPauseSelect; }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	StatePauseScene();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize(PauseSelect* pauseSelect, PlayScene* playScene);

	/// <summary>
	/// ���������s����
	/// </summary>
	/// <param name="elapsedTime">�I������</param>
	virtual void Update(const bool& selectFlag, const bool& animationFlag) = 0;

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
	virtual ~StatePauseScene() = default;

private:
	PauseSelect* m_pPauseSelect;
	PlayScene* m_pPlayScene;
};
