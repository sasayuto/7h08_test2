#include "pch.h"

#include"PlayerCameraFactory.h"

#include"NormalCamera.h"
#include"DeathCamera.h"
std::unique_ptr<StatePlaySceneCamera> PlayerCameraFactory::CreateNormalCamera(PlaySceneCamera* parent)
{
	//�ʏ�̃J�����̃C���X�^���X�𐶐�����
	std::unique_ptr<StatePlaySceneCamera> normalCamera = std::make_unique<NormalCamera>();

	//����������
	normalCamera->Initialize(parent);

	//�ʏ�̃J�����̃C���X�^���X��Ԃ�
	return move(normalCamera);
}

std::unique_ptr<StatePlaySceneCamera> PlayerCameraFactory::CreateDeathCamera(PlaySceneCamera* parent)
{
	//�f�X�̃J�����̃C���X�^���X�𐶐�����
	std::unique_ptr<StatePlaySceneCamera> deathCamera = std::make_unique<DeathCamera>();

	//����������
	deathCamera->Initialize(parent);

	//�f�X�̃J�����̃C���X�^���X��Ԃ�
	return move(deathCamera);
}
