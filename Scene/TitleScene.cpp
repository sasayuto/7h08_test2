#include "pch.h"
#include "TitleScene.h"
#include "GameTitle.h"
using namespace DirectX;

TitleScene::TitleScene() :
	m_menuSelect(nullptr),
	m_transitionState(nullptr),
	m_returnLetter(nullptr)
{

}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	m_transitionState->Initialize();
	m_returnLetter->Initialize();
	m_menuSelect->Initialize(this);
	m_menuBackGroundUI->Initialize();
}

void TitleScene::Update(float elapsedTime)
{
	//キー入力
	auto keyboardTraker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
	if (KeyboardTracker::GetInstance()->Decision())
		m_transitionState->SetAnimationFlag(true);

	m_menuSelect->Update(m_transitionState->GetStageSelct(), m_transitionState->GetAnimationFlag());

	m_transitionState->Update(elapsedTime);

	//タブが押されたら前の画面に戻る
	if (keyboardTraker.pressed.Tab)
		m_transitionState->SetAnimationReturnFlag(true);

	if (m_transitionState->GetStageReturnSelct())
		ChangeScene<GameTitle>();
	UNREFERENCED_PARAMETER(elapsedTime);
}

void TitleScene::Render()
{
	m_menuBackGroundUI->Render();
	m_menuSelect->Render();
	m_returnLetter->Render();

	m_transitionState->Render();

	auto* debugFont = SingletonDebugFont::GetInstance();
	debugFont->AddString(L"TitleScene", SimpleMath::Vector2(0.0f, debugFont->GetFontHeight()));

}

void TitleScene::Finalize()
{
	SaveGunData();
}

void TitleScene::SaveGunData()
{
	// JSONオブジェクトを作成
	Json::Value root;
	// "Gun" キーの配列を作成
	Json::Value GunArray(Json::arrayValue);
	Json::Value GunElement;

	//項目名を決める
	GunElement["BULLET_COOL_TIME"] = Json::arrayValue;
	//ここに書き出したい値を書く
	GunElement["BULLET_COOL_TIME"].append(0.125f);

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

void TitleScene::CreateDeviceDependentResources()
{	
	//背景のインスタンスを生成
	m_menuSelect = std::make_unique<MenuSelect>();

	m_transitionState = std::make_unique<TransitionState>();

	m_returnLetter = std::make_unique<ReturnLetter>();

	m_menuBackGroundUI = std::make_unique<MenuBackGroundUI>();
}

void TitleScene::CreateWindowSizeDependentResources()
{
}

void TitleScene::OnDeviceLost()
{
	Finalize();
}
