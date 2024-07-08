#pragma once

#include "ImaseLib/SceneManager.h"
#include "UserResources.h"
#include "ImaseLib/UserInterface.h"
#include"Scene/GameObjects/UI/TransitionState.h"
#include"Scene/GameObjects/Camera/TitleCamera.h"
#include"Scene/GameObjects/Background/CloudyBackGround.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/StoneFloor.h"

class ResultScene : public Imase::Scene<UserResources>
{
public:

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

private:
	std::unique_ptr <tito::UserInterface> m_ResultBaseUI;

	std::unique_ptr <TransitionState> m_transitionState;
	std::unique_ptr<TitleCamera> m_camera;
	std::unique_ptr<CloudyBackGround> m_CloudyBackGround;
	//�w�i���f��
	std::unique_ptr<StoneFloor> m_stoneFloor;

};

