//--------------------------------------------------------------------------------------
// File: DebugCamera.cpp
//
// デバッグ用カメラクラス
//
// Date: 2018.4.15
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "DebugCamera.h"
#include "Mouse.h"

using namespace DirectX;
using namespace Imase;

const float DebugCamera::DEFAULT_CAMERA_DISTANCE = 1.00f;

//--------------------------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------------------------
DebugCamera::DebugCamera(int windowWidth, int windowHeight)
	: m_yAngle(0.0f), m_yTmp(0.0f), m_xAngle(0.0f), m_xTmp(0.707f), m_x(0), m_y(0), m_scrollWheelValue(0), m_screenW(windowWidth), m_screenH(windowHeight),
	m_keepTargetPosition(), m_AdditionPercentageRight(0),m_wasd{}
{
	SetWindowSize(windowWidth, windowHeight);

	// マウスのフォイール値をリセット
	Mouse::Get().ResetScrollWheelValue();
}


//--------------------------------------------------------------------------------------
// 更新
//--------------------------------------------------------------------------------------
void Imase::DebugCamera::Update(const DirectX::Mouse::ButtonStateTracker& tracker, const DirectX::Keyboard::KeyboardStateTracker& kbtracker, DirectX::SimpleMath::Vector3 selectTarget)
{
	auto state = tracker.GetLastState();
	auto kb = kbtracker.GetLastState();

	// 相対モードなら
	if (state.positionMode == Mouse::Mode::MODE_RELATIVE)
	{
		// マウスの左ボタンが押されていたらカメラを移動させる
		if (state.rightButton)
		{
			RelativeMotion(state.x, state.y);
		}
	}
	else
	{
		// マウスの左ボタンが押された
		if (tracker.rightButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
		{
			// マウスの座標を取得
			m_x = state.x;
			m_y = state.y;
		}
		else if (tracker.rightButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
		{
			// 現在の回転を保存
			m_xAngle = m_xTmp;
			m_yAngle = m_yTmp;
		}
		// マウスの左ボタンが押されていたらカメラを移動させる
		if (state.rightButton)
		{
			AbsoluteMotion(state.x, state.y);
		}
	}

	// マウスのフォイール値を取得
	m_scrollWheelValue = state.scrollWheelValue;
	if (m_scrollWheelValue > 0)
	{
		m_scrollWheelValue = 0;
		Mouse::Get().ResetScrollWheelValue();
	}

	// ビュー行列を算出する
	SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(m_yTmp);
	SimpleMath::Matrix rotX = SimpleMath::Matrix::CreateRotationX(m_xTmp);

	SimpleMath::Matrix rt = rotY * rotX;

	SimpleMath::Vector3 eye(0.0f, 0.0f, 1.0f);
	SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	if (state.rightButton)
	{
		//左右押されたら初期数値とタイムを０にする
		if (kbtracker.pressed.W)m_AdditionPercentageRight += 0.1f, m_wasd[0] = 0;
		if (kbtracker.pressed.S)m_AdditionPercentageRight += 0.1f, m_wasd[1] = 0;
		if (kbtracker.pressed.A)m_AdditionPercentageRight += 0.1f, m_wasd[2] = 0;
		if (kbtracker.pressed.D)m_AdditionPercentageRight += 0.1f, m_wasd[3] = 0;
		if (kbtracker.pressed.E)m_AdditionPercentageRight += 0.1f, m_wasd[4] = 0;
		if (kbtracker.pressed.F)m_AdditionPercentageRight += 0.1f, m_wasd[5] = 0;

		float elapsedTime = 0.016666f;
		//加速度
		if (kb.W)	m_AdditionPercentageRight += 0.005f;
		else  m_wasd[0] += elapsedTime;
		if (kb.S)	m_AdditionPercentageRight += 0.005f;
		else m_wasd[1] += elapsedTime;
		if (kb.A)	m_AdditionPercentageRight += 0.005f;
		else  m_wasd[2] += elapsedTime;
		if (kb.D)	m_AdditionPercentageRight += 0.005f;
		else m_wasd[3] += elapsedTime;
		if (kb.E)	m_AdditionPercentageRight += 0.005f;
		else  m_wasd[4] += elapsedTime;
		if (kb.F)	m_AdditionPercentageRight += 0.005f;
		else m_wasd[5] += elapsedTime;

		if (m_wasd[0] >= 0.1f)
			if (m_wasd[1] >= 0.1f)
				if (m_wasd[2] >= 0.1f)
					if (m_wasd[3] >= 0.1f)
						if (m_wasd[4] >= 0.1f)
							if (m_wasd[5] >= 0.1f)
								m_AdditionPercentageRight = 0;


		//乗倍して２次元的に数値の変化をする
		float AdditionPercentageRight =m_AdditionPercentageRight;

		DirectX::SimpleMath::Vector3 move = DirectX::SimpleMath::Vector3::Zero;
		if (kb.D)
				move.x += 1;
		if (kb.A)
			move.x += -1;
		if (kb.W)
			move.z += -1;
		if (kb.S)
			move.z += 1;
		move.Normalize();
		move *= m_AdditionPercentageRight;
		m_keepTargetPosition += DirectX::SimpleMath::Vector3::Transform(move, rt.Invert());

		if (kbtracker.pressed.E)
			m_keepTargetPosition.y += 0.1f * AdditionPercentageRight;
		if (kbtracker.pressed.F)
			m_keepTargetPosition.y += -0.1f * AdditionPercentageRight;

	}
	if (kbtracker.pressed.Z)
	{
		m_keepTargetPosition = selectTarget;
	}
	target = m_keepTargetPosition;

	eye = SimpleMath::Vector3::Transform(eye, rt.Invert());
	eye *= (DEFAULT_CAMERA_DISTANCE - m_scrollWheelValue / 100);

	up = SimpleMath::Vector3::Transform(up, rt.Invert());

	m_target = target;
	m_eye = eye + m_target;

	m_view = SimpleMath::Matrix::CreateLookAt(m_eye, m_target, up);
}

void DebugCamera::AbsoluteMotion(int x, int y)
{
	// マウスポインタの位置のドラッグ開始位置からの変位 (相対値)
	float dx = (x - m_x) * m_sx;
	float dy = (y - m_y) * m_sy;

	if (dx != 0.0f || dy != 0.0f)
	{
		// Ｙ軸の回転
		float yAngle = dx * XM_PI;
		// Ｘ軸の回転
		float xAngle = dy * XM_PI;

		m_xTmp = m_xAngle + xAngle;
		m_yTmp = m_yAngle + yAngle;
	}
}

void DebugCamera::RelativeMotion(int x, int y)
{
	// マウスポインタの位置のドラッグ開始位置からの変位 (相対値)
	float dx = x * m_sx;
	float dy = y * m_sy;

	// Ｙ軸の回転
	float yAngle = dx * XM_PI;
	// Ｘ軸の回転
	float xAngle = dy * XM_PI;

	m_xTmp += xAngle;
	m_yTmp += yAngle;
}

DirectX::SimpleMath::Matrix DebugCamera::GetCameraMatrix()
{
	return m_view;
}

DirectX::SimpleMath::Vector3 DebugCamera::GetEyePosition()
{
	return m_eye;
}

DirectX::SimpleMath::Vector3 DebugCamera::GetTargetPosition()
{
	return m_target;
}

void DebugCamera::SetWindowSize(int windowWidth, int windowHeight)
{
	// 画面サイズに対する相対的なスケールに調整
	m_sx = 1.0f / float(windowWidth);
	m_sy = 1.0f / float(windowHeight);
}

void DebugCamera::GetWindowSize(int & windowWidth, int & windowHeight)
{
	windowWidth = m_screenW;
	windowHeight = m_screenH;
}
