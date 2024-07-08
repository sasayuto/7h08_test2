#pragma once

class StageSelect;
class StageSelectScene;
/// <summary>
/// ISelectPlayScene�C���^�[�t�F�C�X���`����
/// </summary>
class ISelectPlayScene
{
public:
	StageSelect* GetStageSelect() { return m_pStageSelect; };
	StageSelectScene* GetStageSelectScene() { return m_pStageSelectScene; };

	void SetSelectFlag(bool selectFlag) { m_SelectFlag = selectFlag; }
	bool GetSelectFlag() {
		return m_SelectFlag
			;
	}
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ISelectPlayScene();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize(StageSelect* stageSelect, StageSelectScene* stageSelectScene);

	/// <summary>
	/// ���������s����
	/// </summary>
	/// <param name="elapsedTime">�I������</param>
	virtual void Update(const bool& selectFlag,const bool& selectStartFlag) = 0;

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
	virtual ~ISelectPlayScene() = default;

private:
	StageSelect* m_pStageSelect;
	StageSelectScene* m_pStageSelectScene;

	bool m_SelectFlag;
};
