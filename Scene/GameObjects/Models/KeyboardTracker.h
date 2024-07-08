#pragma once
#include "Keyboard.h"
#include "Mouse.h"

//けせ
#include"ImaseLib/UserInterface.h"
#include"Scene/GameObjects/Models/Textures.h"
//

/// <summary>
/// KeyboardTrackerクラスを定義する
/// </summary>
class KeyboardTracker
{
public:
	//キーボードトラッカーのゲッター
	DirectX::Keyboard::KeyboardStateTracker GetKeyboardTracker() { return m_keyboardTracker; };

	//マウストラッカーのゲッター
	DirectX::Mouse::ButtonStateTracker GetMouseTracker() { return m_mouseTracker; };

public:
	/// <summary>
	/// 描画クラスのインスタンスを取得する
	/// </summary>
	/// <returns>描画クラスのインスタンス</returns>
	static KeyboardTracker*  GetInstance();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	KeyboardTracker();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 決定ボタン
	/// </summary>
	/// <returns>決定ボタンが押されたらtrue</returns>
	bool Decision();

	/// <summary>
	/// 左ボタン
	/// </summary>
	/// <returns>左ボタンが押されたらtrue</returns>
	bool Left();

	/// <summary>
	/// 右ボタン
	/// </summary>
	/// <returns>右ボタンが押されたらtrue</returns>
	bool Right();

	/// <summary>
	/// 上ボタン
	/// </summary>
	/// <returns>上ボタンが押されたらtrue</returns>
	bool Up();

	/// <summary>
	/// 下ボタン
	/// </summary>
	/// <returns>下ボタンが押されたらtrue</returns>
	bool Down();

private:
	// 描画のインスタンスへのポインタ
	static std::unique_ptr<KeyboardTracker> m_tracker;

	// キーボードステートトラッカー
	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;

	// マウスステートトラッカー
	DirectX::Mouse::ButtonStateTracker m_mouseTracker;

};

class KeyboardSingleton
{
public:
	//キーボードのゲッター
	DirectX::Keyboard::State GetKeyboardState() { return m_keyboardState; };

	//マウスのゲッター
	DirectX::Mouse::State GetMouseState() { return m_mouseState; };

	/// <summary>
	/// 描画クラスのインスタンスを取得する
	/// </summary>
	/// <returns>描画クラスのインスタンス</returns>
	static KeyboardSingleton* GetInstance();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	KeyboardSingleton();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 左回転ボタン
	/// </summary>
	/// <returns>左ボタンが押されたらtrue</returns>
	bool Left();

	/// <summary>
	/// 右回転ボタン
	/// </summary>
	/// <returns>右ボタンが押されたらtrue</returns>
	bool Right();

	/// <summary>
	/// 上昇ボタン
	/// </summary>
	/// <returns>上ボタンが押されたらtrue</returns>
	bool Up();

	/// <summary>
	/// 下降ボタン
	/// </summary>
	/// <returns>下ボタンが押されたらtrue</returns>
	bool Down();

	/// <summary>
	/// 左ロールボタン
	/// </summary>
	/// <returns>左ボタンが押されたらtrue</returns>
	bool LeftRool();

	/// <summary>
	/// 左ロールボタン
	/// </summary>
	/// <returns>左ボタンが押されたらtrue</returns>
	bool RightRool();

	/// <summary>
	/// 左回避ボタン
	/// </summary>
	/// <returns></returns>
	bool AvoidanceLeft();

	/// <summary>
	/// 右回避ボタン
	/// </summary>
	/// <returns></returns>
	bool AvoidanceRight();

private:
	// 描画のインスタンスへのポインタ
	static std::unique_ptr<KeyboardSingleton> m_keyboardSingleton;

	//キーボード
	DirectX::Keyboard::State m_keyboardState;

	//マウス
	DirectX::Mouse::State m_mouseState;

};

/// <summary>
/// 画像の位置を求める
/// </summary>
/// <param name="position"></param>
/// <param name="textuerSize"></param>
/// <param name="scale"></param>
/// <param name="anchor"></param>
/// <param name="positionAnchor"></param>
/// <returns></returns>
static DirectX::SimpleMath::Vector2 TexPositionCorrection(
	const DirectX::SimpleMath::Vector2& position,
	const int& textuerSize_X,
	const int& textuerSize_Y,
	const DirectX::SimpleMath::Vector2& scale,
	const tito::ANCHOR& anchor,
	const tito::POSITION_ANCHOR& positionAnchor
)
{
	//画像のアンカーの分割数
	const int TEXTURE_ANCHOR_RATIO_NUM = 3;
	DirectX::SimpleMath::Vector2 Pos = position;

	//画像サイズの比率を１２８０，７２０で揃えてるのでフルスクリーンになった時に位置を合わせる計算
	DirectX::SimpleMath::Vector2 windowSizeRatio = DirectX::SimpleMath::Vector2(
		(static_cast<float>(Textures::GetInstance()->GetWindowWidth()) / static_cast<float>(Textures::GetInstance()->GetFullScreenNoneWindowWidth())),
		(static_cast<float>(Textures::GetInstance()->GetWindowHeight()) / static_cast<float>(Textures::GetInstance()->GetFullScreenNoneWindowHeight()))
	);
	Pos.x = position.x * windowSizeRatio.x;
	Pos.y = position.y * windowSizeRatio.y;

	//当たり判定のために位置を割り出す
	int anc = static_cast<int>(anchor);
	Pos.x -=
		(
			(textuerSize_X * windowSizeRatio.x * scale.x) -
			(
				textuerSize_X * 
				(TEXTURE_ANCHOR_RATIO_NUM - 1 - (anc % TEXTURE_ANCHOR_RATIO_NUM)) * 
				scale.x * 
				windowSizeRatio.x
				)
			) / 
		2.f;

	Pos.y -=
		(
			(textuerSize_Y * windowSizeRatio.y * scale.y) -
			(textuerSize_Y * (anc / TEXTURE_ANCHOR_RATIO_NUM) * scale.y * windowSizeRatio.y)
			) /
		2.f;

	DirectX::SimpleMath::Vector2 windouSize = DirectX::SimpleMath::Vector2(static_cast<float>(Textures::GetInstance()->GetWindowWidth()), static_cast<float>(Textures::GetInstance()->GetWindowHeight()));

	//当たり判定のために位置を割り出す
	int PosAnc = static_cast<int>(positionAnchor);
	Pos.x += (windouSize.x * (PosAnc % 3)) / 2.0f;
	Pos.y -= (windouSize.y * (PosAnc / 3)) / 2.0f;

	//UIの位置Yはマイナスになっていくのでマウスの位置と合わせるために-1翔
	Pos.y *= -1;
	return Pos;
}

/// <summary>
/// 画像の大きさを調整
/// </summary>
/// <param name="textuerSize_X">画像サイズX</param>
/// <param name="textuerSize_Y">画像サイズY</param>
/// <returns>修正後の画像サイズ</returns>
static DirectX::SimpleMath::Vector2 TexSizeCorrection(
	const int& textuerSize_X,
	const int& textuerSize_Y
)
{
	//画像サイズの比率を１２８０，７２０で揃えてるのでフルスクリーンになった時に位置を合わせる計算
	DirectX::SimpleMath::Vector2 windowSizeRatio = DirectX::SimpleMath::Vector2(
		(static_cast<float>(Textures::GetInstance()->GetWindowWidth()) / static_cast<float>(Textures::GetInstance()->GetFullScreenNoneWindowWidth())),
		(static_cast<float>(Textures::GetInstance()->GetWindowHeight()) / static_cast<float>(Textures::GetInstance()->GetFullScreenNoneWindowHeight()))
	);
	//中心からのサイズ
	return DirectX::SimpleMath::Vector2(textuerSize_X * windowSizeRatio.x, textuerSize_Y * windowSizeRatio.y) / 2.0f;
}
