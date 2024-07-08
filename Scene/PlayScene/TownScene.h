#pragma once

#include "ImaseLib/SceneManager.h"
#include "UserResources.h"

#include"Scene/GameObjects/PlayScene/Item/SupplyPointManager.h"
#include "Scene/GameObjects/Camera/PlaySceneCamera/PlaySceneCamera.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/EnemyManager.h"
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"
#include"Scene/GameObjects/UI/Gaueg.h"
#include"Scene/GameObjects/UI/TransitionState.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/StoneFloor.h"
#include"Scene/GameObjects/PlayScene/Character/Turret/TurretManager.h"
#include"Scene/GameObjects/PlayScene/Character/CrabRobot/CrabRobotManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/ObjectsManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Bench/BenchManager.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/FloorManagers/FloorManager_01.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Windmill/WindmillManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/StreetLight/StreetLightManager.h"
#include"Scene/GameObjects/PlayScene/Item/CoinManager.h"
#include"Scene/GameObjects/UI/Timer/Timer.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/AirshipManager.h"
#include"Scene/GameObjects/UI/Letter/returnLetter/ReturnLetter.h"
#include"Scene/GameObjects/PlayScene/Sandstorm/SandstormManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Objects/Walls/BigBrickWall/BigBrickWallManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Fence/FenceManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/HouseMoveObjects/HouseMoveObjectsManager.h"

//�f��
#include"Scene/GameObjects/Background/CloudyBackGround.h"

#include"PlayScene.h"
/// <summary>
/// TownScene�̃N���X���`����
/// </summary>
class TownScene : public PlayScene
{
public:
	TownScene() ;
	~TownScene() override;

	// ������
	void Initialize() override;

	// �X�V
	void Update(float elapsedTime) override;

	// �`��
	void Render() override;

	// �I������
	void Finalize() override;

	// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateDeviceDependentResources() override;

	// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateWindowSizeDependentResources() override;

	// �f�o�C�X���X�g�������ɌĂяo�����֐�
	void ShadowMapRender() override;
	void OnDeviceLost() override;

	//�ǉ�
private:

	std::unique_ptr<PlaySceneCamera> m_Camera;

	// �f�o�C�X���\�[�X
	DX::DeviceResources* m_deviceResources;

	//�w�i���f��
	std::unique_ptr<CloudyBackGround> m_cloudyBackGround;

	//�w�i���f��
	std::unique_ptr<StoneFloor> m_stoneFloor;

	//�v���C���[�̃|�C���^
	std::unique_ptr<Player> m_player;

	//�G�̃|�C���^
	std::unique_ptr<EnemyManager> m_enemyManager;

	//�G�̃|�C���^
	std::unique_ptr<ReturnLetter> m_returnLetter;;

	//���̃|�C���^
	std::unique_ptr<BulletManager> m_bulletManager;

	//���̃|�C���^
	std::unique_ptr<WindmillManager> m_windmillManager;

	//���̃|�C���^
	std::unique_ptr<StreetLightManager> m_streetLightManager;

	//�Q�[�W�̃|�C���^
	std::unique_ptr<Gaueg> m_playerGaueg;

	//�Q�[�W�̃|�C���^
	std::unique_ptr<SupplyPointManager> m_supplyPointManager;

	//�I�u�W�F�N�g�̃|�C���^
	std::unique_ptr<ObjectsManager> m_objectsManager;

	//�I�u�W�F�N�g�̃|�C���^
	std::unique_ptr<FloorManager_01> m_floorManager_01;

	//�I�u�W�F�N�g�̃|�C���^
	std::unique_ptr<BenchManager> m_benchManager;

	//�I�u�W�F�N�g�̃|�C���^
	std::unique_ptr<CoinManager> m_coinManager;

	//�I�u�W�F�N�g�̃|�C���^
	std::unique_ptr<AirshipManager> m_airshipManager;

	//�I�u�W�F�N�g�̃|�C���^
	std::unique_ptr<SandstormManager> m_sndstormManager;

	//�ǂ̊Ǘ��҂̃|�C���^
	std::unique_ptr<BigBrickWallManager> m_bigBrickWallManager;

	//�X�e�[�W�Z���N�g�̃|�C���^
	std::unique_ptr<TransitionState> m_transitionState;

	//�t�F���X�Ǘ��҂̃|�C���^
	std::unique_ptr<FenceManager> m_fenceManager;

	//�X�e�[�W�Z���N�g�̃|�C���^
	std::unique_ptr<HouseMoveObjectsManager> m_HouseMove_03Manager;
	//�X�e�[�W�Z���N�g�̃|�C���^
	std::unique_ptr<HouseMoveObjectsManager> m_HouseMove_02Manager;
	//�X�e�[�W�Z���N�g�̃|�C���^
	std::unique_ptr<HouseMoveObjectsManager> m_HouseMove_01Manager;

	//��ʃT�C�Y
	RECT m_rect;
	//����
	bool a = false;
	float m_timespeed = 0;
	//

};

