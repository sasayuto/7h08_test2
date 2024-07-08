//--------------------------------------------------------------------------------------
// File: HomeScene.cpp
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "HomeScene.h"
#include"Scene/HomeScene/HomeState/StateHomeScene/StateHomeScene.h"
#include"Scene/HomeScene/HomeState/StateOptionScene/OptionScene.h"
#include"Scene/HomeScene/HomeState/StatePlayerCustomScene.h"
#include"Scene/HomeScene/HomeState/StateStageSelectScene.h"
using namespace DirectX;

// 初期化
void HomeScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	m_transitionState->Initialize();
	m_returnLetter->Initialize();
	m_CloudyBackGround->Initialize();
	m_CloudyBackGround->SetScale(DirectX::SimpleMath::Vector3(1000, 1000, 1000));
	for (int i = 0; i < HomeState::COUNT; i++)
	{
		m_State[i]->Initialize();	
		m_fsm->RegisterState(static_cast<HomeState>(i), m_State[i].get());
	}
	m_fsm->Start(HomeState::HOME_SCENE);
	m_stoneFloor->Initialize();

}

// 更新
void HomeScene::Update(float elapsedTime)
{
	Mouse::Get().SetVisible(Mouse::Mode::MODE_RELATIVE);

	UNREFERENCED_PARAMETER(elapsedTime);
	m_camera->Update(
		DirectX::SimpleMath::Vector3(10,0,0),
		DirectX::SimpleMath::Quaternion::Identity
	);
	//カメラの情報をセット（ビルボード、ソート、描画範囲などを決めるため。しないならセットしなくてもよい）
	Draw::GetInstance()->SetCameraTarget(m_camera->GetTargetPosition());
	Draw::GetInstance()->SetCameraPosition(m_camera->GetEyePosition());
	Draw::GetInstance()->SetCameraUp(m_camera->GetUpPosition());
	Draw::GetInstance()->SetCameraDir(m_camera->GetDir());
	m_stoneFloor->Update();

	//ステートの更新
	m_fsm->Update(elapsedTime);
	m_transitionState->Update(elapsedTime);
	m_returnLetter->Update(elapsedTime);

}

// 描画
void HomeScene::Render()
{
	for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
	{
		Draw::GetInstance()->DynamicShadowMapTexCreateStart(i, 0);
	}

	//影になるオブジェクトはこの間に書く
		for (int i = 0; i < Draw::CASCADE_LIGHT_MAX_NUM; i++)
		{
			Draw::GetInstance()->StaticShadowMapTexCreateStart(i, 0);
			//////球の描写
			//m_coinManager->RenderShadowTex();
		}
	Draw::GetInstance()->ShadowMapTexCreateEnd();

	//背景
	m_CloudyBackGround->Render();
	Draw::GetInstance()->ShadowMapTexCreateEndCon();

	//コイン地点の描画
	m_stoneFloor->Render();

	m_fsm->Render();
	m_returnLetter->Render();
	m_transitionState->Render();
}

// 終了処理
void HomeScene::Finalize()
{
	m_fsm->Finalize();
	SaveGunData();
}

// デバイスに依存するリソースを作成する関数
void HomeScene::CreateDeviceDependentResources()
{
	m_transitionState = std::make_unique<TransitionState>();

	m_returnLetter = std::make_unique<ReturnLetter>();

	m_camera = std::make_unique<TitleCamera>();
	m_stoneFloor = std::make_unique<StoneFloor>();

	m_CloudyBackGround = std::make_unique<CloudyBackGround>();
	m_fsm = std::make_unique<FSM>(this);

	m_State[HomeState::HOME_SCENE] = std::make_unique<StateHomeScene>(m_fsm.get());

	m_State[HomeState::OPTION_SCENE] = std::make_unique<OptionScene>(m_fsm.get());

	m_State[HomeState::PLAYER_CUSTOM_SCENE] = std::make_unique<StatePlayerCustomScene>(m_fsm.get());

	m_State[HomeState::STAGE_SELECT_SCENE] = std::make_unique<StateStageSelectScene>(m_fsm.get());

}

// ウインドウサイズに依存するリソースを作成する関数
void HomeScene::CreateWindowSizeDependentResources()
{

}

// デバイスロストした時に呼び出される関数
void HomeScene::OnDeviceLost()
{
	Finalize();
}

void HomeScene::SaveGunData()
{
	// JSONオブジェクトを作成
	Json::Value root;
	// "Gun" キーの配列を作成
	Json::Value GunArray(Json::arrayValue);
	Json::Value GunElement;

	//項目名を決める
	GunElement["BULLET_COOL_TIME"] = Json::arrayValue;
	//ここに書き出したい値を書く
	GunElement["BULLET_COOL_TIME"].append(0.325f);

	//項目名を決める
	GunElement["PLAYER_MAX_SPEED"] = Json::arrayValue;
	//ここに書き出したい値を書く
	GunElement["PLAYER_MAX_SPEED"].append(15.0f / 60.0f);

	//項目名を決める
	GunElement["PLAYER_ACCELERATION"] = Json::arrayValue;
	//ここに書き出したい値を書く
	GunElement["PLAYER_ACCELERATION"].append(0.5f / 60.0f);

	//項目名を決める
	GunElement["PLAYER_BEND_ACCELERATION"] = Json::arrayValue;
	//ここに書き出したい値を書く
	GunElement["PLAYER_BEND_ACCELERATION"].append(6.0f / 60.0f);

	//項目名を決める
	GunElement["PLAYER_MAX_HP"] = Json::arrayValue;
	//ここに書き出したい値を書く
	GunElement["PLAYER_MAX_HP"].append(20000);

	//項目名を決める
	GunElement["PLAYER_MAX_FUEL"] = Json::arrayValue;
	//ここに書き出したい値を書く
	GunElement["PLAYER_MAX_FUEL"].append(5000);

	//項目名を決める
	GunElement["PLAYER_OFFENSIVE_POWER"] = Json::arrayValue;
	//ここに書き出したい値を書く
	GunElement["PLAYER_OFFENSIVE_POWER"].append(2);

	//値をいれる
	GunArray.append(GunElement);
	// rootオブジェクトに "Gun"を追加
	root["PlayerData"] = GunArray;
	// JSONデータを文字列に変換
	Json::StreamWriterBuilder writer;
	std::string jsonString = Json::writeString(writer, root);
	// JSONデータをファイルに書き出し
	std::ofstream outputFile(L"Resources/Json/Json_playerDate.json");
	if (outputFile.is_open())
	{
		outputFile << jsonString;
		outputFile.close();
	}
}
