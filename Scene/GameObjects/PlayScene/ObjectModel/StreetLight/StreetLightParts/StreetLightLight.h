#pragma once
#include"StreetLightComponent.h"
/// <summary>
/// �{�f�B�[�N���X���`����
/// </summary>
class StreetLightLight : public StreetLightComponent
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
	StreetLightLight(
		IStreetLightComponent* parent,
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& angle
	);
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~StreetLightLight()override;
	
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	void Update(const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& angle
	)override;

	void Explosion(const float& elapsedTime) override;

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render()override;
	
	/// <summary>
	/// �㏈��
	/// </summary>
	void Finalize()override;

	/// <summary>
	/// �Ƃ̓����蔻��
	/// </summary>
	/// <param name="objectsManager">�Ƃ̃|�C���^</param>
	/// <returns>����������"true"</returns>
private:

	//��]
	DirectX::SimpleMath::Vector3 m_angle;

	//�v���y���̑��x
	DirectX::SimpleMath::Vector3 m_velcity;

};
