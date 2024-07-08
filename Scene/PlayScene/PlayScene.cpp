#include "pch.h"
#include "PlayScene.h"
#include"Scene/ResultScene.h"
#include"Scene/GameObjects/Models/Textures.h"
#include"Scene/StageSelectScene.h"
using namespace DirectX;

const float TIME_LIMIT(180.0f);		//�������ԁis�j

PlayScene::PlayScene() :
	m_timer(0),
	m_sun(nullptr),
	m_PausedScreen()
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	PlayScene::CreateDeviceDependentResources();
	PlayScene::CreateWindowSizeDependentResources();
	m_timerTex->Initialize(
		DirectX::SimpleMath::Vector2(1400, 50),
		DirectX::SimpleMath::Vector2(0.8f, 0.8f),
		TIME_LIMIT,
		tito::ANCHOR::TOP_CENTER
	);

	m_score->Initialize(
		DirectX::SimpleMath::Vector2(1400, 130),
		DirectX::SimpleMath::Vector2(0.8f, 0.8f) ,
		GetUserResources()->GetScoreCalculation()->GetScore(),
		tito::ANCHOR::TOP_CENTER
	);
	m_sun->Initialize();
	Draw::GetInstance()->SetSun(m_sun.get());
	Textures::GetInstance()->SetSun(m_sun.get());
	m_PausedScreen->Initialize();
	Mouse::Get().SetVisible(Mouse::Mode::MODE_ABSOLUTE);

}

void PlayScene::Update(float elapsedTime)
{
	//�|�[�Y��ʂ̍X�V
	m_menuSceneFlag = m_PausedScreen->Update(elapsedTime);

	//�|�[�Y��ʂ�������I��
	if (m_menuSceneFlag)
	{
		Mouse::Get().SetVisible(Mouse::Mode::MODE_RELATIVE);
		return;
	}
	else
		Mouse::Get().SetVisible(Mouse::Mode::MODE_ABSOLUTE);

	m_sun->Update(elapsedTime);
	//���݂̃X�R�A�̍X�V
	GetUserResources()->GetScoreCalculation()->PlaySceneUpdate();
	m_score->Update(GetUserResources()->GetScoreCalculation()->GetScore());

	//���Ԃ̍X�V
	m_timerTex->Update(TIME_LIMIT - m_timer);

	//�b�����v�Z
	m_timer += elapsedTime;
	Draw::GetInstance()->Update(elapsedTime);

	UNREFERENCED_PARAMETER(elapsedTime);
}

void PlayScene::Render()
{
	m_timerTex->Render();
	m_score->Render();

	m_PausedScreen->Render();
}

void PlayScene::Finalize()
{
	for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
	{
		Draw::GetInstance()->DynamicShadowMapTexCreateStart(i, 1);
		Draw::GetInstance()->StaticShadowMapTexCreateStart(i, 1);
	}
	Draw::GetInstance()->ShadowMapTexCreateEnd();

	Mouse::Get().SetVisible(Mouse::Mode::MODE_RELATIVE);

}

void PlayScene::CreateDeviceDependentResources()
{
	//�G�̃C���X�^���X�𐶐�
	m_timerTex = std::make_unique<TimerTex>();
	//�G�̃C���X�^���X�𐶐�
	m_score = std::make_unique<ScoreTex>();

	//�G�̃C���X�^���X�𐶐�
	m_sun = std::make_unique<Sun>();

	//�G�̃C���X�^���X�𐶐�
	m_PausedScreen = std::make_unique<PausedScreen>(this);

}

void PlayScene::CreateWindowSizeDependentResources()
{
}

void PlayScene::OnDeviceLost()
{
	Finalize();
}
