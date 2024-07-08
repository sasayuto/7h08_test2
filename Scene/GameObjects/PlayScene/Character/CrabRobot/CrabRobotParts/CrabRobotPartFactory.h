#pragma once
#include "ICrabRobotComponent.h"
#include "ICrabRobotPartFactory.h"

/// <summary>
/// PlayerPartFactory�̃N���X���`����
/// </summary>
class CrabRobotPartFactory : public ICrabRobotPartFactory
{
public:
	/// <summary>
	///�@�^���b�g�̓y��𐶐�����
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	/// <returns>�v���y���̃A�h���X</returns>
	static std::unique_ptr<ICrabRobotComponent> CreateCrabRobotHead(
		ICrabRobotComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);
};

