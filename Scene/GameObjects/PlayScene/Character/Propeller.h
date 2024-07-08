#pragma once
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Player/PlayerComponent.h"

//�v���y���̃N���X���`����
class Propeller : public PlayerComponent
{
public:
	static const float FALL_SPEED_ACCELERATION;	//�����̉����x			(m/s)
	static const float PROPELLER_ACCELERATION;//�v���y���̉�]�̉����x(��/s�j
	static const float PROPELLER_COOL_TIME;	//��C��R
	static const float EXPLOSIVE_ROTATE;		//���f���̉�]�̑���(��/s�j
	static const float EXPLOSIVE_RANDOM_POWER;	//�����̃����_���ȕ����̃p���[		(m/s)
	static const float EXPLOSIVE_POWER;			//�����̕����̃p���[		(m/s)

public:
	/// <summary>
	/// ���������s����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	Propeller(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Propeller()override;

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="angle">���˃x�N�g��</param>
	void Initialize(const DirectX::SimpleMath::Vector3& reflectionVector)override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	void Update(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	)override;

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render()override;

	/// <summary>
	///��������
	/// </summary>
	void Explosion()override;

	/// <summary>
	/// �㏈��
	/// </summary>
	void Finalize()override;

	/// <summary>
	/// ��������
	/// </summary>
	void Speed()override;

private:

	//�v���y���̉�]
	DirectX::SimpleMath::Vector3 m_angle;

	//�v���y���̑��x
	DirectX::SimpleMath::Vector3 m_velcity;
};
