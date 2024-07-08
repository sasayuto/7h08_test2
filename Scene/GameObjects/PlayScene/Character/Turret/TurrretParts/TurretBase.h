#pragma once
#include"TurretComponent.h"
/// <summary>
/// TurretBase�N���X���`����
/// </summary>
class TurretBase : public TurretComponent
{
public:
	static const float FALL_SPEED_ACCELERATION;		//�����̉����x					(m/s)
	static const float EXPLOSIVE_ROTATE;			//���f���̉�]�̑���			(��/s�j
	static const float EXPLOSIVE_RANDOM_POWER;		//�����̃����_���ȕ����̃p���[	(m/s)
	static const float EXPLOSIVE_POWER;				//�����̕����̃p���[			(m/s)
	static const int MAX_HP;						//HP


public:
	/// <summary>
	/// ���������s����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	TurretBase(
		BulletManager* bulletManager,
		ITurretComponent* parent,
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& angle
	);
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TurretBase()override;
	
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// �X�V����
	/// </summary>
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
	void Explosion(const float& elapsedTime)override;

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render()override;
	
	/// <summary>
	/// �㏈��
	/// </summary>
	void Finalize()override;
};
