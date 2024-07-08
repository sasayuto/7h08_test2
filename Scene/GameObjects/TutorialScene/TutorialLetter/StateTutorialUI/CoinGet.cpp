#include "pch.h"
#include"CoinGet.h"
#include<random>
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"

#include"../TutorialUI.h"
using namespace DirectX;

const float DRAWING_TIME(1);

CoinGet::CoinGet(TutorialUI* tutorialUI):
	IStateTutorialUI(),
	m_pTutorialUI(tutorialUI),
	m_wasdPushFlag(false)
{
}

void CoinGet::Initialize()
{
	//文字の設定
	GetTextLetter()->Initialize(
		L"Resources/Textures/CoinGetLtter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
}

void CoinGet::Update(const float& elapsedTime)
{
	//コインゲットミッションをtrueにする
	m_pTutorialUI->SetCoinDrawFlag(true);

	//コインをとったらtrue
	if (m_pTutorialUI->GetCoinGetFlag())
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
	m_pTutorialUI->SetCoinMissionAccomplishedFlag(true);

	//コインをとったら時間を進める
	SetTimer(GetTimer() + elapsedTime);

	//文字の終了処理
	GetTextLetter()->ReduceTransparency(elapsedTime);

	//文字の終了処理が終わったら
	if (GetTimer() >= DRAWING_TIME + TutorialUI::FADE_TIME)
	{
		//次のシーンにナイスがあるときは次に行く命令文をここにセットする
		m_pTutorialUI->SetNiceUis(TUTORIAl_UIS::BENCH_STREET_LIGHT_GET);

		//ナイスの次になにか言葉をはさむときにここにセットする
		m_pTutorialUI->SetPraiseUis(TUTORIAl_UIS::SCORE_UP_LETTER);

		//次に行くシーンをセっと
		m_pTutorialUI->SetCurrentState(m_pTutorialUI->GetTutorialUI()[TUTORIAl_UIS::NICE_LETTER].get());
	}
}

void CoinGet::Render()
{
	GetTextLetter()->Render();
}

void CoinGet::Finalize()
{
}

void CoinGet::Reset()
{
	SetTimer(0);
	m_wasdPushFlag = false;
}
