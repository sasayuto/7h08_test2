////--------------------------------------------------------------------------------------
#include "pch.h"
//#include "Camera.h"
//#include"Scene/GameObjects/Models/Draw.h"
//using namespace DirectX;
//
//const float EYE_SPEED_RATE = 0.1f;		// カメラの位置への距離の差分に対する割合
//const float TARGET_SPEED_RATE = 0.07f;	// 注視点への距離の差分に対する割合
//const float MOUSE_SENSITIVITY = 0.4f;	// マウス感度
//const float MOUSE_SMOOTH = 0.90f;		// マウスを徐々に戻す
//
////--------------------------------------------------------------------------------------
//// コンストラクタ
////--------------------------------------------------------------------------------------
//PlayCamera::PlayCamera() :
//	m_view(SimpleMath::Matrix::Identity),
//	m_eye(SimpleMath::Vector3::Zero),
//	m_mauseRotate(SimpleMath::Matrix::Identity),
//	m_yTmp(0.0f),
//	m_xTmp(0.0f), m_x(0), m_y(0),
//	m_targetAnimationX(0)
//{
//}
//
////--------------------------------------------------------------------------------------
//// 更新
////--------------------------------------------------------------------------------------
//void PlayCamera::Update(const SimpleMath::Quaternion& rot, const SimpleMath::Vector3& playerPosition, const DirectX::SimpleMath::Vector3& eyee)
//{
//	//マウスの処理
//	Mouse();
//
//	//eye,target,upの初期位置
//	SimpleMath::Vector3 eye(eyee);
//	SimpleMath::Vector3 target(playerPosition);
//	SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);
//
//	//カメラの位置を注視点の５分の一下にする
//	target += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, eye.z / 5.0f, 0.0f), rot);
//
//	//ぷれいやーの回転
//	eye = SimpleMath::Vector3::Transform(eye, m_mauseRotate.Invert());
//	up = SimpleMath::Vector3::Transform(up, m_mauseRotate.Invert());
//
//	//マウスの回転
//	eye = SimpleMath::Vector3::Transform(eye, rot);
//	up = SimpleMath::Vector3::Transform(up, rot);
//
//	///ホントはここに書きたくない（修正しろ）
//	if (KeyboardSingleton::GetInstance()->Right()) m_targetAnimationX += 0.02f;
//	if (KeyboardSingleton::GetInstance()->Left()) m_targetAnimationX -= 0.02f;
//	m_targetAnimationX *= 0.95f;
//	SimpleMath::Vector3 posanimw = SimpleMath::Vector3::Transform(SimpleMath::Vector3(m_targetAnimationX, 0, 0), rot);
//	m_target = target + posanimw;
//	///
//
//	//注視点をプラスし差分をかける
//	m_eye += ((eye + target) - m_eye) * EYE_SPEED_RATE;
//
//	m_up = up;
//
//	//ビュー行列の作成
//	m_view = SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
//
//	//ビュー行列をセットする
//	Draw::GetInstance()->SetView(m_view);
//}
//
//void PlayCamera::Mouse()
//{
//	auto state = KeyboardSingleton::GetInstance()->GetMouseState();
//	auto mouseTracker = KeyboardTracker::GetInstance()->GetMouseTracker();
//
//	// マウスの左ボタンが押された
//	if (mouseTracker.rightButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
//	{
//		// マウスの座標を取得
//		m_x = state.x;
//		m_y = state.y;
//	}
//	// マウスのボタンが押されていたらカメラを移動させる
//	if (state.rightButton)		Motion(state.x, state.y);
//
//	//徐々に視点を戻す
//	m_xTmp *= MOUSE_SMOOTH;
//	m_yTmp *= MOUSE_SMOOTH;
//
//	//マウスのビュー行列を算出する
//	SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(XMConvertToRadians(m_yTmp));
//	SimpleMath::Matrix rotX = SimpleMath::Matrix::CreateRotationX(XMConvertToRadians(m_xTmp));
//	m_mauseRotate = rotY* rotX;
//
//}
//
//void PlayCamera::Motion(const int& x, const int& y)
//{
//	// マウスポインタの位置のドラッグ開始位置からの変位 (相対値)
//	float dx = static_cast<float>(x) - m_x;
//	float dy = static_cast<float>(y) - m_y;
//
//	// Ｙ軸の回転
//	float yAngle = dx * MOUSE_SENSITIVITY;
//
//	// Ｘ軸の回転
//	float xAngle = dy * MOUSE_SENSITIVITY;
//
//	//角度を代入
//	m_xTmp = xAngle;
//	m_yTmp = yAngle;
//
//}
//
