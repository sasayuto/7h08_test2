#include "pch.h"

#include "TurretPartFactory.h"

#include"TurretBase.h"
#include"TurretCancer_Middle.h"
#include"TurretCancer_Left.h"
#include"TurretCancer_Right.h"
#include"TurretHead.h"

std::unique_ptr<ITurretComponent> TurretPartFactory::CreateTurretBase(BulletManager* bulletManager, ITurretComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<ITurretComponent> turretBase = std::make_unique<TurretBase>(bulletManager,parent, position, angle);
	// ����������
	turretBase->Initialize();
	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(turretBase);
}
std::unique_ptr<ITurretComponent> TurretPartFactory::CreateTurretCancer_Middle(BulletManager* bulletManager, ITurretComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<ITurretComponent> turretCancer_Middle = std::make_unique<TurretCancer_Middle>(bulletManager, parent, position, angle);
	// ����������
	turretCancer_Middle->Initialize();
	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(turretCancer_Middle);
}
std::unique_ptr<ITurretComponent> TurretPartFactory::CreateTurretCancer_Left(BulletManager* bulletManager, ITurretComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<ITurretComponent> turretCancer_Left = std::make_unique<TurretCancer_Left>(bulletManager, parent, position, angle);
	// ����������
	turretCancer_Left->Initialize();
	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(turretCancer_Left);
}
std::unique_ptr<ITurretComponent> TurretPartFactory::CreateTurretCancer_Right(BulletManager* bulletManager, ITurretComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<ITurretComponent> turretCancer_Right = std::make_unique<TurretCancer_Right>(bulletManager, parent, position, angle);
	// ����������
	turretCancer_Right->Initialize();
	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(turretCancer_Right);
}
std::unique_ptr<ITurretComponent> TurretPartFactory::CreateTurretHead(BulletManager* bulletManager, ITurretComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<ITurretComponent> turretHead = std::make_unique<TurretHead>(bulletManager,parent, position, angle);
	// ����������
	turretHead->Initialize();
	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(turretHead);
}
