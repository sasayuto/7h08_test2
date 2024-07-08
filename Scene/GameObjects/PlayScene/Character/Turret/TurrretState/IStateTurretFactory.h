#pragma once
#include <combaseapi.h>
class ITurretState;
class Turret;
class TurretManager;

/// <summary>
/// IStateTurretFactory�C���^�[�t�F�C�X�̃N���X���`����
/// </summary>
interface  IStateTurretFactory
{
	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�^���b�g�̃A�h���X</param>
	/// <param name="coinManager">�^���b�g�̊Ǘ��҂̃A�h���X</param>
	/// <returns>�ʏ�̏�Ԃ̃|�C���^</returns>
	virtual std::unique_ptr<ITurretState> CreateTurretMotion(
		const Turret* parent,
		const TurretManager* TurretManager
	) = 0;

	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <returns>���S��Ԃ̃|�C���^</returns>
	virtual std::unique_ptr<ITurretState> CreateTurretKillMotion(
		const Turret* parent
	) = 0;

};

