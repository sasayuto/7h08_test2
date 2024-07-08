#pragma once

#include"ISelectPlayScene.h"
#include"Scene/GameObjects/Background/Background.h"
class StageSelectScene;
#include "ImaseLib/MoveUserInterface.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"

/// <summary>
/// ���̎�ށi���ԂɂȂ�j
/// </summary>
const enum Planet
{
	TUTORIAL,
	TOWN,
	//GRAND_CANYON,
	COUNT,
};

/// <summary>
/// StageSelect�̃N���X���`����
/// </summary>
class StageSelect
{
public:
	//�I�����Ă���ԍ��̃Q�b�^�[�A�Z�b�^�[
	int GetSelectNum() const{ return m_selectNum; }
	void SetSelectNum(const int& selectNum) { m_selectNum = selectNum; }

public:
	//�X�e�[�W�̉���
	static const int WIDTH = 5;

	//�w�i�̘f��
	virtual std::unique_ptr<Background>* GetBackground() { return m_background; }
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	StageSelect();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~StageSelect();
	
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="titleScene"></param>
	void Initialize(StageSelectScene* stageSelectScene);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="selectFlag"></param>
	void Update(const bool& selectFlag, const bool& selectStartFlag, const bool& retuneSelectStartFlag);

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
	std::unique_ptr<ISelectPlayScene> m_select[Planet::COUNT];

	// ���݂̏�Ԃ̃|�C���^
	ISelectPlayScene* m_pCurrentState;

	//�z�[���̕����̓����蔻��
	std::unique_ptr <Collider::Box2D> m_Collision[2];


	//�I�����Ă���ԍ�
	int m_selectNum;

private:
	//�w�i�̘f��
	std::unique_ptr <Background> m_background[COUNT];

	//�w�i�̑傫��
	const int SCALE = 1000;
private:
	//�Q�[�W�ƃx�[�X�̃|�C���^
	std::unique_ptr<tito::MoveUserInterface> m_HorizontalTriangle[2];
	std::unique_ptr<Collider::Box2D> m_HorizontalTrianglecol[2];
	bool m_flag[2];

};

