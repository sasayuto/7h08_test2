#include "pch.h"

#include"PlayerPartFactory.h"

#include"Scene/GameObjects/PlayScene/Character/Wing.h"
#include"Scene/GameObjects/PlayScene/Character/Propeller.h"
#include"Scene/GameObjects/PlayScene/Character/Tail.h"
#include"Scene/GameObjects/PlayScene/Character/HorizontalStabilizer.h"
#include"Scene/GameObjects/PlayScene/Character/Body.h"
#include"Scene/GameObjects/PlayScene/Character/LeftTire.h"
#include"Scene/GameObjects/PlayScene/Character/RightTire.h"
#include"Scene/GameObjects/PlayScene/Character/WheelSupport.h"


std::unique_ptr<IPlayerComponent> PlayerPartFactory::CreatePlayerPro(
	IPlayerComponent* parent,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& angle
)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<IPlayerComponent> propeller = std::make_unique<Propeller>(parent, position, angle);

	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(propeller);
}

std::unique_ptr<IPlayerComponent> PlayerPartFactory::CreatePlayerWing(
	IPlayerComponent* parent,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& angle
)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<IPlayerComponent> wing = std::make_unique<Wing>(parent, position, angle);

	//�H�̃C���X�^���X��Ԃ�
	return move(wing);
}

std::unique_ptr<IPlayerComponent> PlayerPartFactory::CreatePlayerBody(
	IPlayerComponent* parent,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& angle
)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<IPlayerComponent> body = std::make_unique<Body>(parent, position, angle);

	//�H�̃C���X�^���X��Ԃ�
	return move(body);
}

std::unique_ptr<IPlayerComponent> PlayerPartFactory::CreatePlayerTail(IPlayerComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<IPlayerComponent> tail = std::make_unique<Tail>(parent, position, angle);

	//�H�̃C���X�^���X��Ԃ�
	return move(tail);
}

std::unique_ptr<IPlayerComponent> PlayerPartFactory::CreatePlayerHorizontalStabilizer(IPlayerComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<IPlayerComponent> horizontalStabilizer = std::make_unique<HorizontalStabilizer>(parent, position, angle);

	//�H�̃C���X�^���X��Ԃ�
	return move(horizontalStabilizer);
}

std::unique_ptr<IPlayerComponent> PlayerPartFactory::CreatePlayerLeftTire(IPlayerComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<IPlayerComponent> leftTire = std::make_unique<LeftTire>(parent, position, angle);

	//�H�̃C���X�^���X��Ԃ�
	return move(leftTire);
}

std::unique_ptr<IPlayerComponent> PlayerPartFactory::CreatePlayerRightTire(IPlayerComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<IPlayerComponent> rightTire = std::make_unique<RightTire>(parent, position, angle);

	//�H�̃C���X�^���X��Ԃ�
	return move(rightTire);
}



std::unique_ptr<IPlayerComponent> PlayerPartFactory::CreatePlayerWheelSupport(
	IPlayerComponent* parent, 
	const DirectX::SimpleMath::Vector3& position, 
	const DirectX::SimpleMath::Quaternion& angle
)
{
	//�H�̃C���X�^���X�𐶐�����
	std::unique_ptr<IPlayerComponent> wheelSupport = std::make_unique<WheelSupport>(parent, position, angle);

	//�H�̃C���X�^���X��Ԃ�
	return move(wheelSupport);
}
