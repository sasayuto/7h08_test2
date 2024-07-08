#pragma once
#include"TurretComponent.h"

class BulletManager;
/// <summary>
/// TurretCancer_Middle�N���X���`����
/// </summary>
class TurretCancer_Middle : public TurretComponent
{
public:
	static const float FALL_SPEED_ACCELERATION;		//�����̉����x		(m/s)
	static const float EXPLOSIVE_ROTATE;		//���f���̉�]�̑���(��/s�j
	static const float EXPLOSIVE_RANDOM_POWER;	//�����̃����_���ȕ����̃p���[		(m/s)
	static const float EXPLOSIVE_POWER;			//�����̕����̃p���[		(m/s)
	static const float BULLET_COOL_TIME;		//���N�[���^�C��	(s)
	static const int MAX_HP;	//HP

public:
	/// <summary>
	/// ���������s����
	/// </summary>
	/// <param name="parent">���̊Ǘ��҂̃A�h���X</param>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	TurretCancer_Middle(
		BulletManager* bulletManager,
		ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TurretCancer_Middle()override;

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="position">�P�t���[������</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	void Update(
		const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	)override;

	/// <summary>
	///��������
	/// </summary>
	/// <param name="position">�P�t���[������</param>
	void Explosion(const float& elapsedTime)override;

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render()override;

	/// <summary>
	/// �㏈��
	/// </summary>
	void Finalize()override;

private:

	//���̊Ǘ��҂̃|�C���^
	BulletManager* m_pBulletManager;

	//���̃N�[���^�C��
	float m_bulletCoolTime;

	DirectX::SimpleMath::Quaternion m_CancerAngle;
	float b = 0;
	bool h = false;


};