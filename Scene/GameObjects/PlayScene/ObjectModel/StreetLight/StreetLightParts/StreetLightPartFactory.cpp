#include "pch.h"

#include "StreetLightPartFactory.h"

#include"StreetLightFoundation.h"
#include"StreetLightLight.h"
#include"StreetLightConnection.h"

std::unique_ptr<IStreetLightComponent> StreetLightPartFactory::CreateStreetLightConnection(IStreetLightComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<IStreetLightComponent> streetLightConnection = std::make_unique<StreetLightConnection>(parent, position, angle);
	// ����������
	streetLightConnection->Initialize();
	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(streetLightConnection);
}

std::unique_ptr<IStreetLightComponent> StreetLightPartFactory::CreateStreetLightLight(IStreetLightComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<IStreetLightComponent> streetLightLight = std::make_unique<StreetLightLight>(parent, position, angle);
	// ����������
	streetLightLight->Initialize();
	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(streetLightLight);
}

std::unique_ptr<IStreetLightComponent> StreetLightPartFactory::CreateStreetLightFoundation(IStreetLightComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<IStreetLightComponent> streetLightFoundation = std::make_unique<StreetLightFoundation>(parent, position, angle);
	// ����������
	streetLightFoundation->Initialize();
	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(streetLightFoundation);
}
