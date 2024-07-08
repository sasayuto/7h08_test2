#pragma once

#include "ImaseLib/SceneManager.h"
#include "UserResources.h"
#include"Scene/GameObjects/UI/TransitionState.h"
#include"Scene/GameObjects/UI/OperationInstructions/OperationInstructionsUI.h"
#include"Scene/GameObjects/UI/Letter/returnLetter/ReturnLetter.h"
class OperationInstructionsScene : public Imase::Scene<UserResources>
{
public:
	OperationInstructionsScene();
	~OperationInstructionsScene() override;

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
	std::unique_ptr<ReturnLetter> m_returnLetter;
	std::unique_ptr<TransitionState> m_transitionState;
	std::unique_ptr<OperationInstructionsUI> m_operationInstructionsUI;
};

