#include "pch.h"
#include "Tutorial.h"
#include"Scene/StageSelectScene.h"
#include"Scene/PlayScene/TutorialScene.h"
using namespace DirectX;

const float ELAPSED_TIME = 1.0f;

 Tutorial::Tutorial() :
	 ISelectPlayScene()
{
	 m_StageUI = std::make_unique<FreeUi>();

	 m_StageUI->Initialize(
		 L"Resources/Textures/StageTutorialLetter.png"
		 ,DirectX::SimpleMath::Vector2(0,150)
		 , DirectX::SimpleMath::Vector2(1, 1)
		 , tito::ANCHOR::MIDDLE_CENTER
		 , tito::POSITION_ANCHOR::MIDDLE_CENTER
	 );
 }

 Tutorial::~Tutorial()
{
}


 void Tutorial::Update(const bool& selectFlag, const bool& selectStartFlag)
 {
	 SetSelectFlag(selectStartFlag);

	 GetStageSelect()->GetBackground()[TUTORIAL]->SelectMotion();

	 if (selectFlag)
		 GetStageSelectScene()->ChangeScene<TutorialScene>();
 }

 void Tutorial::Render()
 {
	 GetStageSelect()->GetBackground()[TUTORIAL]->Render();
	 if (!GetSelectFlag())
		 m_StageUI->Render();
 }

void Tutorial::Finalize()
{
}

