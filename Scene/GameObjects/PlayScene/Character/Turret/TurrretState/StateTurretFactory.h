#pragma once
#include "IStateTurretFactory.h"

class ITurretState;
class Turret;
class TurretManager;

/// <summary>
/// StateTurretFactory�̃N���X���`����
/// </summary>
class StateTurretFactory : public IStateTurretFactory
{
public:
	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�^���b�g�̃A�h���X</param>
	/// <param name="coinManager">�^���b�g�̊Ǘ��҂̃A�h���X</param>
	/// <returns>�ʏ�̏�Ԃ̃|�C���^</returns>
	static std::unique_ptr<ITurretState> CreateTurretMotion(
		Turret* parent,
		TurretManager* TurretManager
	);

	/// <summary>
	/// ���S��Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�^���b�g�̃A�h���X</param>
	/// <returns>���S��Ԃ̃|�C���^</returns>
	static std::unique_ptr<ITurretState> CreateTurretKillMotion(
		Turret* parent
	);
};

