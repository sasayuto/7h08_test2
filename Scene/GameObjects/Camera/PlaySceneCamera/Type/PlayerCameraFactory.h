#pragma once
#include "../StatePlaySceneCamera.h"
#include "IPlayerCameraFactory.h"

/// <summary>
/// StatePlayerFactory�̃N���X���`����
/// </summary>
class PlayerCameraFactory : public IPlayerCameraFactory
{
public:
	/// <summary>
	/// �ʏ�̃J�����𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <returns>�ʏ�̃J�����̃|�C���^</returns>
	static std::unique_ptr<StatePlaySceneCamera> CreateNormalCamera(
		PlaySceneCamera* parent
	);

	/// <summary>
	/// �f�X�̃J�����𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <returns>�f�X�̃J�����̃|�C���^</returns>
	static std::unique_ptr<StatePlaySceneCamera> CreateDeathCamera(
		PlaySceneCamera* parent
	);

};

