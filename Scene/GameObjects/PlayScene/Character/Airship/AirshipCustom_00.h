#pragma once
#include"Airship.h"


//�G�̃N���X���`����
class AirshipCustom_00 :public Airship
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="Hp">�G��HP</param>
	/// <param name="Fuel">�G�̔R��</param>
	/// <param name="offensivePower">�G�̃p���[</param>
	AirshipCustom_00(const int& Hp, const int& Fuel, const int& offensivePower);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~AirshipCustom_00();

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="bulletManager">���̃A�h���X</param>
	/// <param name="enemyManager">�G�̃}�l�[�W���[�̃A�h���X</param>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	void Initialize(
		BulletManager* bulletManager,
		ObjectsManager* objectsManager,
		Player* player
	)override;

	/// <summary>
/// ���������Z�b�g
/// </summary>
	void Reset()override;

private:
	int m_maxHp;

	int m_maxFuel;

	int m_OffensivePower;
};
