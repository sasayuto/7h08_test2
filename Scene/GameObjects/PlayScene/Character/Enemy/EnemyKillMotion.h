#pragma once
#include"Scene/GameObjects/PlayScene/Character/Player/IState.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
class Enemy;

/// <summary>
/// �G�̎��S��Ԃ̃N���X���`����
/// </summary>
class EnemyKillMotion :public IState
{

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	EnemyKillMotion(Enemy* parent);

	/// <summary>
	/// �v���C���[�̓���
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
	void Motion(const float& elapsedTime)override;
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyKillMotion();

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
	Enemy* m_pEnemy;

	//���S�������̉�]
	DirectX::SimpleMath::Quaternion m_killrotate;

	//���̓����܂ł̎���
	float m_nextMotionTime;
};
