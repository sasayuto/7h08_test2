#pragma once
#include"ICrabRobotState.h"
#include"../CrabRobot.h"

/// <summary>
/// �G�̎��S��Ԃ̃N���X���`����
/// </summary>
class CrabRobotKillMotion :public ICrabRobotState
{
private:
	/// <summary>
	/// ����
	/// </summary>
	void Motion();

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	CrabRobotKillMotion(CrabRobot* crabRobot);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CrabRobotKillMotion();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// ���������s����
	/// </summary>
	/// <param name="elapsedTime">�t���[������</param>
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
	//�e�̃|�C���^
	CrabRobot* m_pCrabRobot;

	//���S�������̉�]
	DirectX::SimpleMath::Quaternion m_killrotate;

	//���̓����܂ł̎���
	float m_nextMotionTime;
};
