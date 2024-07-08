#pragma once
#include <combaseapi.h>

#include"ICrabRobotComponent.h"

/// <summary>
/// IPlayerPartFactory�C���^�t�F�[�X���`����
/// </summary>
interface ICrabRobotPartFactory
{	
	/// <summary>
	///�@�^���b�g�̓y��𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃A�h���X</returns>
	virtual std::unique_ptr<ICrabRobotComponent> CreateCrabRobotHead(
		const ICrabRobotComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;
};
