//--------------------------------------------------------------------------------------
// File: StateDrawOptionScene.h
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
//--------------------------------------------------------------------------------------
#pragma once
#include"../OptionScene.h"
#include"Scene/GameObjects/UI/Gaueg/VolumeGaueg.h"

class StateDrawOptionScene : public OptionScene::State
{
public:

	//�ő剹��
	static const int DRAW_MAX_DISTANCE;
	static const int DRAW_MIN_DISTANCE;


	StateDrawOptionScene(OptionScene::FSM* fsm);
	~StateDrawOptionScene();
	// ������
	void Initialize() override;

	// �X�V
	void Update(const float& elapsedTime) override;

	// �`��
	void Render() override;

	// �I������
	void Finalize() override;

	void Enter()override;
	void Exit() override;

	// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateDeviceDependentResources() override;

private:
	OptionScene::FSM* m_fsm;
	//�{�����[���̃Q�[�W�̃|�C���^
	std::unique_ptr<VolumeGaueg> m_drawDistanceGaueg;

	float m_drawDistance;

	//�{�����[���̃Q�[�W�̃|�C���^
	std::unique_ptr<VolumeGaueg> m_soundEffectGaueg;

	//�z�[���̕���
	std::unique_ptr <tito::UserInterface> m_Letter[2];


};
