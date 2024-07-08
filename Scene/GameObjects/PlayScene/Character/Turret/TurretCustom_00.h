#pragma once
#include"Turret.h"


//TurretCustom_00�̃N���X���`����
class TurretCustom_00 :public Turret
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="Hp">�G��HP</param>
	/// <param name="Fuel">�G�̔R��</param>
	/// <param name="offensivePower">�G�̃p���[</param>
	TurretCustom_00(const int& Hp, const int& offensivePower);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TurretCustom_00();

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="bulletManager">���̃A�h���X</param>
	/// <param name="turretManager">�^���b�g�̊Ǘ��҂̃A�h���X</param>
	/// <param name="airshipManager">��s�D�̊Ǘ��҂̃A�h���X</param>
	/// <param name="floor">���̃A�h���X</param>
	/// <param name="sandstormManager">�����̊Ǘ��҂̃A�h���X</param>
	void Initialize(
		BulletManager* bulletManager,
		TurretManager* turretManager,
		AirshipManager* airshipManager,
		Floor* floor,
		SandstormManager* sandstormManager
	)override;

	/// <summary>
	/// ���������Z�b�g
	/// </summary>
	void Reset()override;

private:
	//�ő�HP
	int m_maxHp;

	//�U����
	int m_OffensivePower;
};
