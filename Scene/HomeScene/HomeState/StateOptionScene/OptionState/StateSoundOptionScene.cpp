//--------------------------------------------------------------------------------------
// File: StateSoundOptionScene.cpp
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "StateSoundOptionScene.h"

using namespace DirectX;
StateSoundOptionScene::StateSoundOptionScene(OptionScene::FSM* fsm):
	m_bgmGaueg(nullptr),
	m_soundEffectGaueg(nullptr),
	m_fsm(nullptr)
{
	m_fsm = fsm;
}

StateSoundOptionScene::~StateSoundOptionScene()
{
}

// 初期化
void StateSoundOptionScene::Initialize()
{
	CreateDeviceDependentResources();
	std::ifstream obj("Resources/json/Json_SoundOptionDate.Json");
	Json::CharReaderBuilder reader;
	Json::Value root;

	// ファイルが開かれているかを確認します。
	if (obj.is_open()) {
		std::string errors;

		// ファイルからJSONをパースします。
		if (Json::parseFromStream(reader, obj, &root, &errors))
		{
			// JSONに "house" が存在し、配列であるかどうかを確認します。
			if (root.isMember("SoundOption") && root["SoundOption"].isArray())
			{
				// "house" 配列を取得します。
				const Json::Value& drawData = root["SoundOption"][0];
				float SOUND_BGM_VOLUME = drawData["SOUND_BGM_VOLUME"][0].asFloat();		//球クールタイム	(s)

				//bgmのゲージを初期化
				m_bgmGaueg->Initialize(
					DirectX::SimpleMath::Vector2(0, 0),
					DirectX::SimpleMath::Vector2::One,
					tito::ANCHOR::MIDDLE_CENTER,
					tito::POSITION_ANCHOR::MIDDLE_CENTER,
					SOUND_BGM_VOLUME
				);

				float SOUND_EFFECT_VOLUME = drawData["SOUND_EFFECT_VOLUME"][0].asFloat();		//球クールタイム	(s)

				//効果音のゲージを初期化
				m_soundEffectGaueg->Initialize(
					DirectX::SimpleMath::Vector2(0, -100),
					DirectX::SimpleMath::Vector2::One,
					tito::ANCHOR::MIDDLE_CENTER,
					tito::POSITION_ANCHOR::MIDDLE_CENTER,
					SOUND_EFFECT_VOLUME
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
	m_Letter[0]->LoadTexture(L"Resources/Textures/BgmSoundLetter.png");
	m_Letter[1]->LoadTexture(L"Resources/Textures/SeSoundLetter.png");

}

// 更新
void StateSoundOptionScene::Update(const float& elapsedTime)
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
	auto mouse = KeyboardSingleton::GetInstance()->GetMouseState();

	if (kbTracker.pressed.Tab)
		m_fsm->RequestTransition(OptionScene::OptionState::OPTION_SCENE);


	if (m_fsm->GetOwner()->GetParentFSM()->GetOwner()->GetReturnLetter()->GetMouseFlag())
		if (KeyboardTracker::GetInstance()->Decision())
			m_fsm->RequestTransition(OptionScene::OptionState::OPTION_SCENE);

	m_bgmGaueg->Update();
	m_soundEffectGaueg->Update();


	// JSONオブジェクトを作成
	Json::Value root;
	// "Gun" キーの配列を作成
	Json::Value GunArray(Json::arrayValue);
	Json::Value GunElement;

	//項目名を決める
	GunElement["SOUND_BGM_VOLUME"] = Json::arrayValue;
	//ここに書き出したい値を書く
	GunElement["SOUND_BGM_VOLUME"].append(m_bgmGaueg->GetRatio());

	//項目名を決める
	GunElement["SOUND_EFFECT_VOLUME"] = Json::arrayValue;
	//ここに書き出したい値を書く
	GunElement["SOUND_EFFECT_VOLUME"].append(m_soundEffectGaueg->GetRatio());

	//値をいれる
	GunArray.append(GunElement);
	// rootオブジェクトに "Gun"を追加
	root["SoundOption"] = GunArray;
	// JSONデータを文字列に変換
	Json::StreamWriterBuilder writer;
	std::string jsonString = Json::writeString(writer, root);
	// JSONデータをファイルに書き出し
	std::ofstream outputFile(L"Resources/Json/Json_SoundOptionDate.json");
	if (outputFile.is_open())
	{
		outputFile << jsonString;
		outputFile.close();
	}

}

// 描画
void StateSoundOptionScene::Render()
{
	m_bgmGaueg->Render();
	m_soundEffectGaueg->Render();
	for (int i = 0; i < 2; i++)
	{
		m_Letter[i]->Render();
	}


}

// 終了処理
void StateSoundOptionScene::Finalize()
{
}

void StateSoundOptionScene::Enter()
{
}

void StateSoundOptionScene::Exit()
{
}

void StateSoundOptionScene::CreateDeviceDependentResources()
{
	//BGMゲージのインスタンスを取得
	m_bgmGaueg = std::make_unique<VolumeGaueg>();

	//BGMゲージのインスタンスを取得
	m_soundEffectGaueg = std::make_unique<VolumeGaueg>();

	for (int i = 0; i < 2; i++)
	{
		m_Letter[i] = std::make_unique<tito::UserInterface>();
	}

}

