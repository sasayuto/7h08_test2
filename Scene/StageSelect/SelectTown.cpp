#include "pch.h"
#include "SelectTown.h"
#include"Scene/StageSelectScene.h"
#include"Scene/PlayScene/TownScene.h"
using namespace DirectX;

const float ELAPSED_TIME = 1.0f;

 SelectTown::SelectTown() :
	 ISelectPlayScene()
{
	 m_StageUI = std::make_unique<FreeUi>();

	 m_StageUI->Initialize(
		 L"Resources/Textures/Stage1-1Letter.png"
		 ,DirectX::SimpleMath::Vector2(0,150)
		 , DirectX::SimpleMath::Vector2(1, 1)
		 , tito::ANCHOR::MIDDLE_CENTER
		 , tito::POSITION_ANCHOR::MIDDLE_CENTER
	 );
 }

 SelectTown::~SelectTown()
{
}


 void SelectTown::Update(const bool& selectFlag, const bool& selectStartFlag)
 {
	 SetSelectFlag(selectStartFlag);

	 GetStageSelect()->GetBackground()[TOWN]->SelectMotion();

	 if (selectFlag)
		 GetStageSelectScene()->ChangeScene<TownScene>();
 }

 void SelectTown::Render()
 {
	 GetStageSelect()->GetBackground()[TOWN]->Render();
	 if (!GetSelectFlag())
		 m_StageUI->Render();
 }

void SelectTown::Finalize()
{
}

