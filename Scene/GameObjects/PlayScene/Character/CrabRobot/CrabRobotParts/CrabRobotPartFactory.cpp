#include "pch.h"

#include "CrabRobotPartFactory.h"

#include"CrabRobotHead.h"

std::unique_ptr<ICrabRobotComponent> CrabRobotPartFactory::CreateCrabRobotHead(ICrabRobotComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<ICrabRobotComponent> crabRobotHead = std::make_unique<CrabRobotHead>( parent, position, angle);
	// ����������
	crabRobotHead->Initialize();
	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(crabRobotHead);
}
