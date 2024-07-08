#pragma once
#include "IStateAirshipFactory.h"

class Player;
class Airship;
class IStateAirship;

/// <summary>
/// StateEnemyFactory�̃N���X���`����
/// </summary>
class StateAirshipFactory : public IStateAirshipFactory
{
public:
	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�C�e���̃A�h���X</param>
	/// <param name="coinManager">�v���C���[�̃A�h���X</param>
	/// <returns>�ʏ�̏�Ԃ̃|�C���^</returns>
	static std::unique_ptr<IStateAirship> CreateAirshipMotion(
		Airship* enemy,
		Player* player
	);

	/// <summary>
	/// �ʏ�Q�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�C�e���̃A�h���X</param>
	/// <param name="coinManager">�v���C���[�̃A�h���X</param>
	/// <returns>�ʏ�Q�̏�Ԃ̃|�C���^</returns>
	static std::unique_ptr<IStateAirship> CreateAirshipMotion_01(
		Airship* enemy,
		Player* player
	);

};

