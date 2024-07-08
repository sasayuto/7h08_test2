#pragma once
#include"Scene/GameObjects/PlayScene/Character/Player/IState.h"
#include"Player.h"

class Player;

/// <summary>
/// ���S��Ԃ̃N���X���`����
/// </summary>
class KillMotion :public IState
{
public:
	static const float FALL_SPEED_ACCELERATION;	//�����̉����x			(m/s)
	static const float EXPLOSIVE_POWER_XZ;		//�����̉��̃p���[		(m/s)
	static const float EXPLOSIVE_A;				//�����̉��̃p���[		(m/s)
	static const float EXPLOSIVE_ROTATE;		//���f���̉�]�̑���	(��/s�j
	static const float NEXT_MOTION_TIME;		//���̏�Ԃ܂ł̎���	(s)

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	KillMotion(Player* parent);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~KillMotion();

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

	/// <summary>
	/// �v���C���[�̓���
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
	void Motion(const float& elapsedTime)override;
private:
	//�e�̃A�h���X
	Player* m_pPlayer;

	//���S�������̉�]
	DirectX::SimpleMath::Quaternion m_killrotate;

	//���̓����܂ł̎���
	float m_nextMotionTime;
};
