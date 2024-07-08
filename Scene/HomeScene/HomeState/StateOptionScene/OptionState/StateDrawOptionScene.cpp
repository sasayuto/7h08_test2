//--------------------------------------------------------------------------------------
// File: StateIteme.cpp
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "StateDrawOptionScene.h"
#include "Scene/GameObjects/Models/Draw.h"

using namespace DirectX;

const int StateDrawOptionScene::DRAW_MAX_DISTANCE(1000);
const int StateDrawOptionScene::DRAW_MIN_DISTANCE(300);

StateDrawOptionScene::StateDrawOptionScene(OptionScene::FSM* fsm):
	m_drawDistance(0)
{
	m_fsm = fsm;
}

StateDrawOptionScene::~StateDrawOptionScene()
{
}

// 初期化
void StateDrawOptionScene::Initialize()
{	
	CreateDeviceDependentResources();
	std::ifstream obj("Resources/json/Json_DrawOptionDate.Json");
	Json::CharReaderBuilder reader;
	Json::Value root;

	// ファイルが開かれているかを確認します。
	if (obj.is_open()) {
		std::string errors;

		// ファイルからJSONをパースします。
		if (Json::parseFromStream(reader, obj, &root, &errors))
		{
			// JSONに "house" が存在し、配列であるかどうかを確認します。
			if (root.isMember("DrawOption") && root["DrawOption"].isArray())
			{
				// "house" 配列を取得します。
				const Json::Value& drawData = root["DrawOption"][0];
				float drawDistance = drawData["DRAW_DISTANCE"][0].asFloat();		//球クールタイム	(s)

				//割合を計算
				float drawDistanceRatio = (drawDistance - DRAW_MIN_DISTANCE) / (DRAW_MAX_DISTANCE - DRAW_MIN_DISTANCE);
				//bgmのゲージを初期化
				m_drawDistanceGaueg->Initialize(
					DirectX::SimpleMath::Vector2(0, 0),
					DirectX::SimpleMath::Vector2::One,
					tito::ANCHOR::MIDDLE_CENTER,
					tito::POSITION_ANCHOR::MIDDLE_CENTER,
					drawDistanceRatio
				);

				float drawDisance = drawData["DRAW_DITANCE"][0].asFloat();		//球クールタイム	(s)

				//割合を計算
				float drawDisanceRatio = (drawDisance - DRAW_MIN_DISTANCE) / (DRAW_MAX_DISTANCE - DRAW_MIN_DISTANCE);

				//効果音のゲージを初期化
				m_soundEffectGaueg->Initialize(
					DirectX::SimpleMath::Vector2(0, -100),
					DirectX::SimpleMath::Vector2::One,
					tito::ANCHOR::MIDDLE_CENTER,
					tito::POSITION_ANCHOR::MIDDLE_CENTER,
					drawDisanceRatio
				);

			}
		}
		else {
			std::cerr << "JSONのパースエラー: " << errors << std::endl;
		}
		obj.close();
	}
	else {
		std::cerr << "JSONファイルを開く際にエラーが発生しました。" << std::endl;
	}

	for (int i = 0; i < 2; i++)
	{
		m_Letter[i]->Create(
			L"Resources/Textures/OptionLetter.png",
			DirectX::SimpleMath::Vector2(-130.0f, static_cast<float>(-(i * 100)))
			, DirectX::SimpleMath::Vector2(1, 1)
			, tito::ANCHOR::MIDDLE_RIGHT
			, tito::POSITION_ANCHOR::MIDDLE_CENTER
		);
	}
	m_Letter[0]->LoadTexture(L"Resources/Textures/DrawingDisLetter.png");
	m_Letter[1]->LoadTexture(L"Resources/Textures/EffectDrawingDisLetter.png");

}

// 更新
void StateDrawOptionScene::Update(const float& elapsedTime)
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();

	if (kbTracker.pressed.Tab)
		m_fsm->RequestTransition(OptionScene::OptionState::OPTION_SCENE);
	auto mouse = KeyboardSingleton::GetInstance()->GetMouseState();

	if (m_fsm->GetOwner()->GetParentFSM()->GetOwner()->GetReturnLetter()->GetMouseFlag())
		if (KeyboardTracker::GetInstance()->Decision())
			m_fsm->RequestTransition(OptionScene::OptionState::OPTION_SCENE);


	m_drawDistanceGaueg->Update();
	m_soundEffectGaueg->Update();


	// JSONオブジェクトを作成
	Json::Value root;
	// "Gun" キーの配列を作成
	Json::Value GunArray(Json::arrayValue);
	Json::Value GunElement;

	//描画距離の範囲から秒後距離を求める
	m_drawDistance = DRAW_MIN_DISTANCE +
		(m_drawDistanceGaueg->GetRatio() * (DRAW_MAX_DISTANCE - DRAW_MIN_DISTANCE));
	//項目名を決める
	GunElement["DRAW_DISTANCE"] = Json::arrayValue;
	//ここに書き出したい値を書く
	GunElement["DRAW_DISTANCE"].append(m_drawDistance);

	//描画距離の範囲から秒後距離を求める（仮）
	int dra = DRAW_MIN_DISTANCE +
		(m_soundEffectGaueg->GetRatio() * (DRAW_MAX_DISTANCE - DRAW_MIN_DISTANCE));
	//項目名を決める
	GunElement["DRAW_DITANCE"] = Json::arrayValue;
	//ここに書き出したい値を書く
	GunElement["DRAW_DITANCE"].append(dra);

	//値をいれる
	GunArray.append(GunElement);
	// rootオブジェクトに "Gun"を追加
	root["DrawOption"] = GunArray;
	// JSONデータを文字列に変換
	Json::StreamWriterBuilder writer;
	std::string jsonString = Json::writeString(writer, root);
	// JSONデータをファイルに書き出し
	std::ofstream outputFile(L"Resources/Json/Json_DrawOptionDate.json");
	if (outputFile.is_open())
	{
		outputFile << jsonString;
		outputFile.close();
	}
	Draw::GetInstance()->SetDrawDistance(m_drawDistance * m_drawDistance);
	Draw::GetInstance()->SetFogFar(m_drawDistance);
	Draw::GetInstance()->SetFogNear(m_drawDistance - Draw::FOG_LENGTH);


}

// 描画
void StateDrawOptionScene::Render()
{
	m_drawDistanceGaueg->Render();
	m_soundEffectGaueg->Render();

	for (int i = 0; i < 2; i++)
	{
		m_Letter[i]->Render();
	}
}

// 終了処理
void StateDrawOptionScene::Finalize()
{
}

void StateDrawOptionScene::Enter()
{
}

void StateDrawOptionScene::Exit()
{
	Draw::GetInstance()->SetDrawDistance(m_drawDistance * m_drawDistance);
	Draw::GetInstance()->SetFogFar(m_drawDistance);
	Draw::GetInstance()->SetFogNear(m_drawDistance - Draw::FOG_LENGTH);
}

void StateDrawOptionScene::CreateDeviceDependentResources()
{
	//BGMゲージのインスタンスを取得
	m_drawDistanceGaueg = std::make_unique<VolumeGaueg>();

	//BGMゲージのインスタンスを取得
	m_soundEffectGaueg = std::make_unique<VolumeGaueg>();

	for (int i = 0; i < 2; i++)
	{
		m_Letter[i] = std::make_unique<tito::UserInterface>();
	}

}

