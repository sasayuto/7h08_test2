#pragma once
#include"ICrabRobotState.h"
class CrabRobotManager;
class CrabRobot;

/// <summary>
/// �G�̒ʏ��Ԃ̃N���X���`����
/// </summary>
class CrabRobotMotion_01 :public ICrabRobotState
{

public:		
	/// <summary>
	/// �v���C���[�̓���
	/// </summary>
	void Motion();

public:
	/// <summary>
	/// �R���e�L�X�g
	/// </summary>
	/// <param name="parent">�I���{�b�g�̃A�h���X</param>
	/// <param name="enemyManager">���{�b�g�̃}�l�[�W���[�̃A�h���X</param>
	CrabRobotMotion_01(CrabRobot* crabRobot, CrabRobotManager* crabRobotManager);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CrabRobotMotion_01();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">�P�t���[������</param>
	void Update(const float& elapsedTime)override;

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render()override;

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize()override;

private:
	//�G�̃|�C���^
	CrabRobot* m_pCrabRobot;

	//�G�̃}�l�[�W���[�̃|�C���^
	CrabRobotManager* m_pCrabRobotManager;
};
