#include "pch.h"
#include"TutorialUI.h"
#include<random>
#include"StateTutorialUI/WelcomeToTownLetter.h"
#include"StateTutorialUI/WASDQEmove.h"
#include"StateTutorialUI/BenchStreetLightGet.h"
#include"StateTutorialUI/ShiftStopLetter.h"
#include"StateTutorialUI/NiceLetter.h"
#include"StateTutorialUI/ScoreUpLetter.h"
#include"StateTutorialUI/CoinGet.h"
#include"StateTutorialUI/ChallengeLimitsLetter.h"
#include"StateTutorialUI/EnemyAndDesScoreLetter.h"
#include"StateTutorialUI/RecoveryItemsGet.h"
#include"StateTutorialUI/Time3minutesLetter.h"
#include"StateTutorialUI/LetIsRecoverLetter.h"
using namespace DirectX;

const float TutorialUI::FADE_TIME(1);
const int TASK_LIST_WIDTH(30);
const int TASK_LIST_POSITION_X(50);
const int TASK_LIST_POSITION_Y(100);

TutorialUI::TutorialUI() :
	m_objectsKillFlag(false),
	m_coinGetFlag(false),
	m_sceneTransitionFlag(false),
	m_niceUis(TUTORIAl_UIS::WASDQE_MOVE),
	m_praiseUis(TUTORIAl_UIS::NONE),
	m_coinMissionAccomplishedFlag(false),
	m_itemsMissionAccomplishedFlag(false),
	m_ObjectKillMissionAccomplishedFlag(false),
	m_shiftMissionAccomplishedFlag(false),
	m_WASDMissionAccomplishedFlag(false),
	m_coinDrawFlag(false),
	m_itemsDrawFlag(false),
	m_ObjectKillDrawFlag(false),
	m_shiftDrawFlag(false),
	m_WASDDrawFlag(false),
	m_taskDrawFlag(false)
{
}

TutorialUI::~TutorialUI()
{

}

void TutorialUI::Initialize()
{
	m_tutorialUI[TUTORIAl_UIS::WELCOME_TO_TOWN] = std::make_unique<WelcomeToTownLetter>(this);
	m_tutorialUI[TUTORIAl_UIS::WELCOME_TO_TOWN]->Initialize();

	m_tutorialUI[TUTORIAl_UIS::WASDQE_MOVE] = std::make_unique<WASDQEmove>(this);
	m_tutorialUI[TUTORIAl_UIS::WASDQE_MOVE]->Initialize();

	m_tutorialUI[TUTORIAl_UIS::BENCH_STREET_LIGHT_GET] = std::make_unique<BenchStreetLightGet>(this);
	m_tutorialUI[TUTORIAl_UIS::BENCH_STREET_LIGHT_GET]->Initialize();

	m_tutorialUI[TUTORIAl_UIS::SHIFT_STOP] = std::make_unique<ShiftStopLetter>(this);
	m_tutorialUI[TUTORIAl_UIS::SHIFT_STOP]->Initialize();

	m_tutorialUI[TUTORIAl_UIS::NICE_LETTER] = std::make_unique<NiceLetter>(this);
	m_tutorialUI[TUTORIAl_UIS::NICE_LETTER]->Initialize();

	m_tutorialUI[TUTORIAl_UIS::SCORE_UP_LETTER] = std::make_unique<ScoreUpLetter>(this);
	m_tutorialUI[TUTORIAl_UIS::SCORE_UP_LETTER]->Initialize();

	m_tutorialUI[TUTORIAl_UIS::CHALLENGE_LIMITS_LETTER] = std::make_unique<ChallengeLimitsLetter>(this);
	m_tutorialUI[TUTORIAl_UIS::CHALLENGE_LIMITS_LETTER]->Initialize();

	m_tutorialUI[TUTORIAl_UIS::ENEMY_AND_DES_SCORE_LETTER] = std::make_unique<EnemyAndDesScoreLetter>(this);
	m_tutorialUI[TUTORIAl_UIS::ENEMY_AND_DES_SCORE_LETTER]->Initialize();

	m_tutorialUI[TUTORIAl_UIS::TIME_3MINUTES_LETTER] = std::make_unique<Time3minutesLetter>(this);
	m_tutorialUI[TUTORIAl_UIS::TIME_3MINUTES_LETTER]->Initialize();

	m_tutorialUI[TUTORIAl_UIS::RECOVERY_ITEMS_GET] = std::make_unique<RecoveryItemsGet>(this);
	m_tutorialUI[TUTORIAl_UIS::RECOVERY_ITEMS_GET]->Initialize();

	m_tutorialUI[TUTORIAl_UIS::COIN_GET] = std::make_unique<CoinGet>(this);
	m_tutorialUI[TUTORIAl_UIS::COIN_GET]->Initialize();

	m_tutorialUI[TUTORIAl_UIS::LET_IS_RECOVER_LETTER] = std::make_unique<LetIsRecoverLetter>(this);
	m_tutorialUI[TUTORIAl_UIS::LET_IS_RECOVER_LETTER]->Initialize();

	//タスクを生成
	for (int i = 0; i < TUTORIAl_TASK_UI::TUTORIAl_TASK_COUNT; i++)
	{
		m_tutorialTaskUIs[i] = std::make_unique<OperationTaskUI>();
		m_tutorialTaskUIs[i]->Create(
			DirectX::SimpleMath::Vector2(static_cast<float>(TASK_LIST_POSITION_X), static_cast<float>(TASK_LIST_POSITION_Y + i * -TASK_LIST_WIDTH)),
			tito::ANCHOR::MIDDLE_LEFT,
			tito::POSITION_ANCHOR::MIDDLE_LEFT
		);
	}
	//各タスクの文字をセット
	m_tutorialTaskUIs[TUTORIAl_TASK_UI::COIN_GET]->LoadTexture(L"Resources/Textures/CoinGetTaskLetter.png");
	m_tutorialTaskUIs[TUTORIAl_TASK_UI::ITEMS_GET]->LoadTexture(L"Resources/Textures/ItemsGetTaskLetter.png");
	m_tutorialTaskUIs[TUTORIAl_TASK_UI::OBJECTS_BREAK]->LoadTexture(L"Resources/Textures/BenchBreakTaskLetter.png");
	m_tutorialTaskUIs[TUTORIAl_TASK_UI::SHIFT_STOP]->LoadTexture(L"Resources/Textures/StopTaskLetter.png");
	m_tutorialTaskUIs[TUTORIAl_TASK_UI::WASD]->LoadTexture(L"Resources/Textures/MoveTaskLetter.png");

	m_tutorialTaskListLetter = std::make_unique<TutorialLetter>();
	m_tutorialTaskListLetter->Initialize(
		L"Resources/Textures/TaskListLetter.png",
		DirectX::SimpleMath::Vector2(TASK_LIST_POSITION_X, TASK_LIST_POSITION_Y + 40),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::MIDDLE_LEFT,
		tito::POSITION_ANCHOR::MIDDLE_LEFT
	);
	m_pCurrentState = m_tutorialUI[TUTORIAl_UIS::WELCOME_TO_TOWN].get();
}

void TutorialUI::Update(const float& elapsedTime)
{
	m_pCurrentState->Update(elapsedTime);

	//フラグは１度だけtrueにしたいので使い終わったらfalseにする
	//他の画面の時にtrueになったらそのまま継続されてしまうから
	m_coinGetFlag = false;
	m_objectsKillFlag = false;
	m_itemsFlag = false;

	//タスクが描画OKだったら更新する
	if (m_taskDrawFlag)
	{
		m_tutorialTaskListLetter->Update(elapsedTime);

		if (m_coinDrawFlag)
		{
			//タスクの更新処理
			m_tutorialTaskUIs[TUTORIAl_TASK_UI::COIN_GET]->Update(elapsedTime);
			//タスクのクリアフラグをセット
			m_tutorialTaskUIs[TUTORIAl_TASK_UI::COIN_GET]->SetTaskSuccessFlag(m_coinMissionAccomplishedFlag);
		}
		if (m_WASDDrawFlag)
		{

			//タスクの更新処理
			m_tutorialTaskUIs[TUTORIAl_TASK_UI::WASD]->Update(elapsedTime);
			//タスクのクリアフラグをセット
			m_tutorialTaskUIs[TUTORIAl_TASK_UI::WASD]->SetTaskSuccessFlag(m_WASDMissionAccomplishedFlag);
		}
		if (m_shiftDrawFlag)
		{

			//タスクの更新処理
			m_tutorialTaskUIs[TUTORIAl_TASK_UI::SHIFT_STOP]->Update(elapsedTime);
			//タスクのクリアフラグをセット
			m_tutorialTaskUIs[TUTORIAl_TASK_UI::SHIFT_STOP]->SetTaskSuccessFlag(m_shiftMissionAccomplishedFlag);
		}
		if (m_itemsDrawFlag)
		{

			//タスクの更新処理
			m_tutorialTaskUIs[TUTORIAl_TASK_UI::ITEMS_GET]->Update(elapsedTime);
			//タスクのクリアフラグをセット
			m_tutorialTaskUIs[TUTORIAl_TASK_UI::ITEMS_GET]->SetTaskSuccessFlag(m_itemsMissionAccomplishedFlag);
		}
		if (m_ObjectKillDrawFlag)
		{

			//タスクの更新処理
			m_tutorialTaskUIs[TUTORIAl_TASK_UI::OBJECTS_BREAK]->Update(elapsedTime);
			//タスクのクリアフラグをセット
			m_tutorialTaskUIs[TUTORIAl_TASK_UI::OBJECTS_BREAK]->SetTaskSuccessFlag(m_ObjectKillMissionAccomplishedFlag);
		}
	}
}

void TutorialUI::Render()
{
	m_pCurrentState->Render();

	//タスクが描画OKだったら描画する
	if (m_taskDrawFlag)
		for (int i = 0; i < TUTORIAl_TASK_UI::TUTORIAl_TASK_COUNT; i++)
		{
			m_tutorialTaskUIs[i]->Render();
			m_tutorialTaskListLetter->Render();
		}
}

void TutorialUI::Finalize()
{
	m_pCurrentState->Finalize();
}
