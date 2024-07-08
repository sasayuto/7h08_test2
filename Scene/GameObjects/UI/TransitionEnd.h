//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// メニュークラス
//
//-------------------------------------------------------------------------------------

#pragma once

#include "ImaseLib/Transition.h"

class TransitionEnd
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TransitionEnd();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TransitionEnd();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pDR">デバイスリソーシーズのポインタ</param>
	void Initalize();

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">1フレーム時間</param>
	void Update(const float& elapsedTime);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

private:
	//遷移のポインタ
	std::unique_ptr<tito::Transition> m_transition;

	//スタート
	float m_state;
};