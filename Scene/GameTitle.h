#pragma once

#include "ImaseLib/SceneManager.h"
#include "UserResources.h"

#include"Scene/GameObjects/UI/SwayUserInterface.h"
#include"Scene/GameObjects/UI/TransitionState.h"
#include"Scene/GameObjects/UI/Letter/SpaseLetter.h"
#include"Scene/GameObjects/Camera/StageSelectCamera.h"
#include"Scene/GameObjects/Background/CloudyBackGround.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy_03.h"
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/ObjectsManager.h"
#include"Scene/GameObjects/PlayScene/Sun/Sun.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Objects/Walls/BigBrickWall/BigBrickWallManager.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/StoneFloor.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/HouseMoveObjects/HouseMoveObjectsManager.h"

class GameTitle : public Imase::Scene<UserResources>
{
public:

	static const float SELECT_TINE;

	GameTitle();
	~GameTitle() override;

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
	void OnDeviceLost() override;

	/// <summary>
	/// �e�ɂȂ�I�u�W�F�N�g�̕`��
	/// </summary>
	void ShadowMapRender();

private:
	//�Q�[�W�̃|�C���^
	std::unique_ptr<SwayUserInterface> m_titleName;
	std::unique_ptr <TransitionState> m_transitionState;
	std::unique_ptr <StageSelectCamera> m_titleCamera;
	std::unique_ptr <Background> m_grandCanyon;
	std::unique_ptr <Enemy> m_enemy;
	std::unique_ptr <BulletManager> m_bulletManager;
	std::unique_ptr <ObjectsManager> m_objectsManager;
	std::unique_ptr <Sun> m_sun;
	std::unique_ptr <SpaseLetter> m_spaseLetter;
	//�V�[���J�ڂ̃A�j���[�V�����̃|�C���^
	std::unique_ptr<tito::Transition> m_translucent;

	float m_timerShadowSpeed;
	//�w�i���f��
	std::unique_ptr<StoneFloor> m_stoneFloor;

	//�I�u�W�F�N�g�̃|�C���^
	std::unique_ptr<FloorManager_01> m_floorManager_01;
	//�ǂ̊Ǘ��҂̃|�C���^
	std::unique_ptr<BigBrickWallManager> m_bigBrickWallManager;

	//�X�e�[�W�Z���N�g�̃|�C���^
	std::unique_ptr<HouseMoveObjectsManager> m_HouseMove_03Manager;
	//�X�e�[�W�Z���N�g�̃|�C���^
	std::unique_ptr<HouseMoveObjectsManager> m_HouseMove_02Manager;
	//�X�e�[�W�Z���N�g�̃|�C���^
	std::unique_ptr<HouseMoveObjectsManager> m_HouseMove_01Manager;

	//�o�ߎ���
	float m_nowTimer;
	float m_transition;
};

