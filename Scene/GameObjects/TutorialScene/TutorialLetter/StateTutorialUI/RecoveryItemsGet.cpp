#include "pch.h"
#include"RecoveryItemsGet.h"
#include<random>
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"

#include"../TutorialUI.h"
using namespace DirectX;

const float DRAWING_TIME(1);

RecoveryItemsGet::RecoveryItemsGet(TutorialUI* tutorialUI) :
	IStateTutorialUI(),
	m_pTutorialUI(tutorialUI),
	m_wasdPushFlag(false)
{
}

void RecoveryItemsGet::Initialize()
{
	//文字の設定
	GetTextLetter()->Initialize(
		L"Resources/Textures/GetRecoveryItemsLetter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
}

void RecoveryItemsGet::Update(const float& elapsedTime)
{
	//コインゲットミッションをtrueにする
	m_pTutorialUI->SetItemsDrawFlag(true);

	//コインをとったらtrue
	if (m_pTutorialUI->GetItemsFlag())
		m_wasdPushFlag = true;

	//コインをとってなかったら||描画時間以内だったら
	if (m_wasdPushFlag == false ||
		GetTimer() <= DRAWING_TIME)
	{
		//文字の更新
		GetTextLetter()->Update(elapsedTime);

		//コインをとってなかったら時間は進めない
		if (GetTimer() <= DRAWING_TIME)
			SetTimer(GetTimer() + elapsedTime);
		//終了
		return;
	}

	//コインゲットミッションをtrueにする
	m_pTutorialUI->SetItemsMissionAccomplishedFlag(true);

	//コインをとったら時間を進める
	SetTimer(GetTimer() + elapsedTime);

	//文字の終了処理
	GetTextLetter()->ReduceTransparency(elapsedTime);

	//文字の終了処理が終わったら
	if (GetTimer() >= DRAWING_TIME + TutorialUI::FADE_TIME)
	{
		//次のシーンにナイスがあるときは次に行く命令文をここにセットする
		m_pTutorialUI->SetNiceUis(TUTORIAl_UIS::TIME_3MINUTES_LETTER);

		//ナイスの次になにか言葉をはさむときにここにセットする
		m_pTutorialUI->SetPraiseUis(TUTORIAl_UIS::LET_IS_RECOVER_LETTER);

		//次に行くシーンをセっと
		m_pTutorialUI->SetCurrentState(m_pTutorialUI->GetTutorialUI()[TUTORIAl_UIS::NICE_LETTER].get());
	}
}

void RecoveryItemsGet::Render()
{
	GetTextLetter()->Render();
}

void RecoveryItemsGet::Finalize()
{
}

void RecoveryItemsGet::Reset()
{
	SetTimer(0);
	m_wasdPushFlag = false;
}
