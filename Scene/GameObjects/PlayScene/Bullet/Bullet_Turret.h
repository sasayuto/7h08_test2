#pragma once
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"Bullet.h"
/// <summary>
/// �^���b�g�̋��̃N���X���`����
/// </summary>
class Bullet_Turret :public Bullet
{
public:
	static const float FALL_SPEED_ACCELERATION;	//�����̉����x			(m/s)


	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Bullet_Turret();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Bullet_Turret();

	/// <summary>
/// ���������s����
/// </summary>
	void Update()override;

private:
	//�d��
	float m_gravity;
};