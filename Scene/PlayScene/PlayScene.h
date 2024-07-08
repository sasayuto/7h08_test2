#pragma once

#include "ImaseLib/SceneManager.h"
#include "UserResources.h"
#include"Scene/GameObjects/UI/Timer/Timer.h"
#include"Scene/GameObjects/UI/Timer/Score.h"
#include"Scene/GameObjects/PlayScene/Sun/Sun.h"
#include"Scene/PlayScene/PausedScreen.h"

/// <summary>
/// PlayScene�̊��N���X���`����
/// </summary>
class PlayScene : public Imase::Scene<UserResources>
{
public:
	PlayScene() ;
	~PlayScene() override;

	// ������
	virtual void Initialize() override;

	// �X�V
	virtual void Update(float elapsedTime) override;

	// �`��
	virtual void Render() override;

	// �`��
	virtual void ShadowMapRender() {};

	// �I������
	virtual void Finalize() override;

	// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	virtual void CreateDeviceDependentResources() override;

	// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
	virtual void CreateWindowSizeDependentResources() override;

	// �f�o�C�X���X�g�������ɌĂяo�����֐�
	virtual void OnDeviceLost() override;

	//�ǉ�

public:
	bool GetMenuFlag()const { return m_menuSceneFlag; };
	void SetMenuFlag(const bool& menuFlag) { m_menuSceneFlag = menuFlag; };

	float GetTimer()const { return m_timer; };
	void SetTimer(const float& timer) { m_timer = timer; };

private:
	//�I�u�W�F�N�g�̃|�C���^
	std::unique_ptr<TimerTex> m_timerTex;

	//���z�̃|�C���^
	std::unique_ptr<Sun> m_sun;

	//�I�u�W�F�N�g�̃|�C���^
	std::unique_ptr<ScoreTex> m_score;
	//�b��
	float m_timer;
//menu
private:
	//�X�e�[�W�Z���N�g�̃|�C���^
	std::unique_ptr<PausedScreen> m_PausedScreen;
	bool m_menuSceneFlag;

};

