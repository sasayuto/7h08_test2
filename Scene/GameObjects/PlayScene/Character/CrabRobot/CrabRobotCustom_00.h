#pragma once
#include"CrabRobot.h"


//�I���{�b�g�P�̃N���X���`����
class CrabRobotCustom_00 :public CrabRobot
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="Hp">�G��HP</param>
	/// <param name="offensivePower">�G�̃p���[</param>
	CrabRobotCustom_00(const int& Hp, const int& offensivePower);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CrabRobotCustom_00();

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="bulletManager">���̊Ǘ��҂̃A�h���X</param>
	/// <param name="crabRobotManager">�I���{�b�g�̊Ǘ��҂̃A�h���X</param>
	/// <param name="airshipManager">��s�D�̊Ǘ��҂̃A�h���X</param>
	/// <param name="floor">���̃A�h���X</param>
	/// <param name="sandstormManager">�����̃A�h���X</param>
	void Initialize(
		BulletManager* bulletManager,
		CrabRobotManager* crabRobotManager,
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
