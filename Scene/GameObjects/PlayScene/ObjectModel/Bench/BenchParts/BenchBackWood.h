#pragma once
#include"../../MoveObjects/MoveObjectsParts/MoveObjectsComponent.h"
/// <summary>
/// �{�f�B�[�N���X���`����
/// </summary>
class BenchBackWood : public MoveObjectsComponent
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
	BenchBackWood(
		IMoveObjectsComponent* parent,
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& angle
	);
	
};
