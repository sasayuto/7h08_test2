#include "pch.h"
#include "StageSelect.h"
using namespace DirectX;
#include"SelectTown.h"
#include"Tutorial.h"

//惑星
#include"Scene/GameObjects/Background/GrandCanyon.h"
#include"Scene/GameObjects/Background/CloudyBackGround.h"

void StageSelect::CreateDeviceDependentResources()
{
	//ここの３行追加するだけ
		//惑星を生成
	//m_background[GRAND_CANYON] = std::make_unique<GrandCanyon>();
	//m_object[GRAND_CANYON] = std::make_unique<GrandCanyon>();
	//m_select[Planet::GRAND_CANYON] = std::make_unique<SelectGrandCanyon>();

	//m_background[CLOUDY] = std::make_unique<GrandCanyon>();
	//m_select[Planet::CLOUDY] = std::make_unique<SelectCloudyBackGround>();

	m_background[TOWN] = std::make_unique<CloudyBackGround>();
	m_select[Planet::TOWN] = std::make_unique<SelectTown>();

	m_background[TUTORIAL] = std::make_unique<CloudyBackGround>();
	m_select[Planet::TUTORIAL] = std::make_unique<Tutorial>();


}

StageSelect::StageSelect():
	m_selectNum(0),
	m_background{},
	m_flag{ false,false }

{
}

StageSelect::~StageSelect()
{
}

void StageSelect::Initialize(StageSelectScene* stageSelectScene)
{

	//ゲージとベースを描画する
	for (int i = 0; i < 2; i++)
	{
		//ゲージののリスポーンのインスタンスを生成する
		m_HorizontalTriangle[i] = std::make_unique<tito::MoveUserInterface>();
		m_HorizontalTrianglecol[i] = std::make_unique<Collider::Box2D>();

	}
	//必要な情報をセットする
	m_HorizontalTriangle[0]->Create(
		L"Resources/Textures/HorizontalTrianglel.png"
		, DirectX::SimpleMath::Vector2(-1120, 0)
		, DirectX::SimpleMath::Vector2::One
		, tito::ANCHOR::MIDDLE_RIGHT
		, tito::POSITION_ANCHOR::MIDDLE_RIGHT
	);
	//必要な情報をセットする
	m_HorizontalTriangle[1]->Create(
		L"Resources/Textures/HorizontalTriangle.png"
		, DirectX::SimpleMath::Vector2(-90,0)
		, DirectX::SimpleMath::Vector2::One
		, tito::ANCHOR::MIDDLE_RIGHT
		, tito::POSITION_ANCHOR::MIDDLE_RIGHT
	);

	for (int i = 0; i < 2; i++)
	{
		//当たり判定の初期化
		//位置、サイズを修正した値を渡す
		m_HorizontalTrianglecol[i]->Initialize(
			m_HorizontalTriangle[i]->TexPositionCalculation(),
			m_HorizontalTriangle[i]->TexSizeCalculation()
		);
	}

	CreateDeviceDependentResources();
	//m_select[Planet::GRAND_CANYON]->Initialize(this, stageSelectScene);
	//m_select[Planet::CLOUDY]->Initialize(this, stageSelectScene);
	m_select[Planet::TOWN]->Initialize(this, stageSelectScene);
	m_select[Planet::TUTORIAL]->Initialize(this, stageSelectScene);

	for (int i = 0; i < COUNT; i++)
	{
		//背景を惑星と回る惑星を初期化
		m_background[i]->Initialize();

		//等間隔に並べる
		m_background[i]->SetPosition(SimpleMath::Vector3(static_cast<float>(WIDTH) * i, 0.0f, 0.0f));

		//背景惑星を大きさ調整n
		m_background[i]->SetScale(SimpleMath::Vector3::One * static_cast<float>(SCALE));
	}

	m_pCurrentState = m_select[Planet::TUTORIAL].get();
	m_selectNum = static_cast<int>(Planet::TUTORIAL);
}

void StageSelect::Update(const bool& selectFlag, const bool& selectStartFlag, const bool& retuneSelectStartFlag)
{
	int selectNum = m_selectNum;
	//選択
		//決定されたら操作なし
	if (!selectStartFlag)
	{
		if (!retuneSelectStartFlag)
		{
			//キー入力
			auto mouse = KeyboardSingleton::GetInstance()->GetMouseState();
			auto mouseTr = KeyboardTracker::GetInstance()->GetMouseTracker();

			m_HorizontalTriangle[0]->SetScale(DirectX::SimpleMath::Vector2(1.f, 1.f));

			if (m_HorizontalTrianglecol[0]->CheckHitPoint(mouse.x, mouse.y))
			{

				m_HorizontalTriangle[0]->SetScale(DirectX::SimpleMath::Vector2(1.2f, 1.2f));
				if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
					m_selectNum--;
				if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
					m_flag[0] = true;

			}
			if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
			{
				m_flag[0] = false;
				m_flag[1] = false;
			}

			if (m_flag[0])
				m_HorizontalTriangle[0]->SetBrightness(0.5f);
			else 
				m_HorizontalTriangle[0]->SetBrightness(1);

			m_HorizontalTriangle[1]->SetScale(DirectX::SimpleMath::Vector2(1.f, 1.f));
			if (m_HorizontalTrianglecol[1]->CheckHitPoint(mouse.x, mouse.y))
			{
				m_HorizontalTriangle[1]->SetScale(DirectX::SimpleMath::Vector2(1.2f, 1.2f));
				if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
					m_selectNum++;
				if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
					m_flag[1] = true;
			}
			if (m_flag[1])
				m_HorizontalTriangle[1]->SetBrightness(0.5f);
			else
				m_HorizontalTriangle[1]->SetBrightness(1);

			//惑星の外に出たら調整
			if (m_selectNum < 0) m_selectNum = Planet::COUNT - 1;
			if (m_selectNum >= Planet::COUNT) m_selectNum = 0;
		}
	}
	//ステージが変わったら変更
	if (selectNum != m_selectNum) 
	{
		m_pCurrentState = m_select[m_selectNum].get();
	}

	//ステージの更新
	m_pCurrentState->Update(selectFlag, selectStartFlag);
}

void StageSelect::Render()
{
	m_pCurrentState->Render();

	//ゲージとベースを描画する
	for (int i = 0; i < 2; i++)
	{
		m_HorizontalTriangle[i]->Render();
	}


}

void StageSelect::Finalize()
{
	m_pCurrentState->Finalize();
}

