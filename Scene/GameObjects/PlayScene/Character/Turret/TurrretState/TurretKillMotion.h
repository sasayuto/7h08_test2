#pragma once
#include"ITurretState.h"
#include"../Turret.h"

/// <summary>
/// �^���b�g�̎��S��Ԃ̃N���X���`����
/// </summary>
class TurretKillMotion :public ITurretState
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
	/// <param name="parent">�^���b�g�̃A�h���X</param>
	TurretKillMotion(Turret* turret);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TurretKillMotion();

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
	//�^���b�g�̃|�C���^
	Turret* m_pTurret;

	//���S�������̉�]
	DirectX::SimpleMath::Quaternion m_killrotate;

	//���̓����܂ł̎���
	float m_nextMotionTime;
};
