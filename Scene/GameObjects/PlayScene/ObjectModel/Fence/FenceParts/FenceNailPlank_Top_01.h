#pragma once
#include"../../MoveObjects/MoveObjectsParts/MoveObjectsComponent.h"
/// <summary>
/// �{�f�B�[�N���X���`����
/// </summary>
class FenceNailPlank_Top_01 : public MoveObjectsComponent
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
	FenceNailPlank_Top_01(
		IMoveObjectsComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

};
class FenceNailPlank_Top_02: public MoveObjectsComponent
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
	FenceNailPlank_Top_02(
		IMoveObjectsComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

};
class FenceNailPlank_Top_03 : public MoveObjectsComponent
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
	FenceNailPlank_Top_03(
		IMoveObjectsComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

};
