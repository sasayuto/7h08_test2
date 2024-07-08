#pragma once
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Player/PlayerComponent.h"

/// <summary>
/// �H�̃N���X���`����
/// </summary>
class LeftTire : public PlayerComponent
{
public:
	static const float FALL_SPEED_ACCELERATION;		//�����̉����x		(m/s)
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
	LeftTire(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~LeftTire()override;

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

};