#include"pch.h"
#include "ResultScene.h"
#include"StageSelectScene.h"
using namespace DirectX;

void ResultScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();


	//�X�R�A���v�Z����
	GetUserResources()->GetScoreCalculation()->Initialize();

	m_ResultBaseUI->Create(
		L"Resources/Textures/Black.png"
		, DirectX::SimpleMath::Vector2(0, 0)
		, DirectX::SimpleMath::Vector2(1, 1)
		, tito::ANCHOR::MIDDLE_CENTER
		, tito::POSITION_ANCHOR::MIDDLE_CENTER
	);
	m_ResultBaseUI->SetTransparency(0.7f);
	m_CloudyBackGround->Initialize();
	m_CloudyBackGround->SetScale(DirectX::SimpleMath::Vector3(1000, 1000, 1000));
	m_stoneFloor->Initialize();

	m_transitionState->Initialize();
	Mouse::Get().SetVisible(Mouse::Mode::MODE_RELATIVE);


}

void ResultScene::Update(float elapsedTime)
{
	Mouse::Get().SetVisible(Mouse::Mode::MODE_RELATIVE);

	//�J�ڂ̍X�V����
	m_transitionState->Update(elapsedTime);

	//�X�R�A���v�Z����
	GetUserResources()->GetScoreCalculation()->Update(elapsedTime);

	m_camera->Update(
		DirectX::SimpleMath::Vector3(10, 0, 0),
		DirectX::SimpleMath::Quaternion::Identity
	);
	//�J�����̏����Z�b�g�i�r���{�[�h�A�\�[�g�A�`��͈͂Ȃǂ����߂邽�߁B���Ȃ��Ȃ�Z�b�g���Ȃ��Ă��悢�j
	Draw::GetInstance()->SetCameraTarget(m_camera->GetTargetPosition());
	Draw::GetInstance()->SetCameraPosition(m_camera->GetEyePosition());
	Draw::GetInstance()->SetCameraUp(m_camera->GetUpPosition());
	Draw::GetInstance()->SetCameraDir(m_camera->GetDir());
	m_stoneFloor->Update();


	//�X�R�A�̕\�����I�������
	if (GetUserResources()->GetScoreCalculation()->GetSceneTransitionFlag())
		//����{�^������������
		if (KeyboardTracker::GetInstance()->Decision())
			m_transitionState->SetAnimationFlag(true);

	//����{�^������������
	if (KeyboardTracker::GetInstance()->Decision())
		//�X�R�A�������\��
		GetUserResources()->GetScoreCalculation()->SetTimer(100);

	//�Z���N�g�V�[����
	if (m_transitionState->GetStageSelct())
		ChangeScene<StageSelectScene>();

}

void ResultScene::Render()
{
	for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
	{
		Draw::GetInstance()->DynamicShadowMapTexCreateStart(i, 0);
	}

	//�e�ɂȂ�I�u�W�F�N�g�͂��̊Ԃɏ���
	for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
	{
		Draw::GetInstance()->StaticShadowMapTexCreateStart(i, 0);
		//////���̕`��
		//m_coinManager->RenderShadowTex();
	}
	Draw::GetInstance()->ShadowMapTexCreateEnd();

	//�w�i
	m_CloudyBackGround->Render();
	Draw::GetInstance()->ShadowMapTexCreateEndCon();

	//�R�C���n�_�̕`��
	m_stoneFloor->Render();
	m_ResultBaseUI->Render();
	//�X�R�A���v�Z����
	GetUserResources()->GetScoreCalculation()->Render();
	m_transitionState->Render();

}

void ResultScene::Finalize()
{
	//���U���g������n������
	GetUserResources()->GetScoreCalculation()->Finalize();
}

void ResultScene::CreateDeviceDependentResources()
{
	m_camera = std::make_unique<TitleCamera>();
	m_stoneFloor = std::make_unique<StoneFloor>();

	m_CloudyBackGround = std::make_unique<CloudyBackGround>();

	m_transitionState = std::make_unique<TransitionState>();
	m_ResultBaseUI = std::make_unique<tito::UserInterface>();
}

void ResultScene::CreateWindowSizeDependentResources()
{
}

void ResultScene::OnDeviceLost()
{
	Finalize();
}
