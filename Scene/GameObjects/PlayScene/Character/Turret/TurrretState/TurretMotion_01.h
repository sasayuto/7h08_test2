#pragma once
#include"ITurretState.h"
class TurretManager;
class Turret;

/// <summary>
/// �^���b�g�̒ʏ���1�̃N���X���`����
/// </summary>
class TurretMotion_01 :public ITurretState
{

public:		
	/// <summary>
	/// �v���C���[�̓���
	/// </summary>
	void Motion();

public:
	/// <summary>
	/// �R���e�L�X�g
	/// </summary>
	/// <param name="parent">�^���b�g�̃A�h���X</param>
	/// <param name="enemyManager">�^���b�g�̃}�l�[�W���[�̃A�h���X</param>
	TurretMotion_01(Turret* turret, TurretManager* turretManager);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TurretMotion_01();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">�P�t���[������</param>
	void Update(const float& elapsedTime)override;

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render()override;

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize()override;

private:
	//�^���b�g�̃|�C���^
	Turret* m_pTurret;

	//�^���b�g�̃}�l�[�W���[�̃|�C���^
	TurretManager* m_pTurretManager;
};
