//--------------------------------------------------------------------------------------
#include "pch.h"
#include "NormalCamera.h"
#include"../PlaySceneCamera.h"
using namespace DirectX;

const DirectX::SimpleMath::Vector3 NormalCamera::EYE_INITIAL_VALUE(0, 0, 7);	//視点の初期値

//--------------------------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------------------------
NormalCamera::NormalCamera() :
	StatePlaySceneCamera(),
	m_mauseRotate(SimpleMath::Matrix::Identity),
	m_yTmp(0.0f),
	m_xTmp(0.0f), m_x(0), m_y(0),
	m_targetAnimationX(0)
{
}

void NormalCamera::Reset()
{	
	//角度を

	m_xTmp = 0;
	m_yTmp = 0;
	m_targetAnimationX = 0;
	GetParent()->SetEyePosition(DirectX::SimpleMath::Vector3(0,0,7));

}

//--------------------------------------------------------------------------------------
// 更新
//--------------------------------------------------------------------------------------
void NormalCamera::Update(
	const int& playerHP,
	const SimpleMath::Quaternion& rot, 
	const SimpleMath::Vector3& playerPosition
)
{
	//マウスの処理
	Mouse();
	//eye,target,upの初期位置
	SimpleMath::Vector3 eye(EYE_INITIAL_VALUE);
	SimpleMath::Vector3 target(playerPosition);
	SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	//カメラの位置を注視点の５分の一下にする
	target += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, eye.z / 5.0f, 0.0f), rot);

	//ぷれいやーの回転
	eye = SimpleMath::Vector3::Transform(eye, m_mauseRotate.Invert());
	up = SimpleMath::Vector3::Transform(up, m_mauseRotate.Invert());

	//マウスの回転
	eye = SimpleMath::Vector3::Transform(eye, rot);
	up = SimpleMath::Vector3::Transform(up, rot);

	///ホントはここに書きたくない（修正しろ）

	//曲がった時に横に少しずらす
	if (KeyboardSingleton::GetInstance()->Right()) m_targetAnimationX += 0.02f;
	if (KeyboardSingleton::GetInstance()->Left()) m_targetAnimationX -= 0.02f;
	m_targetAnimationX *= 0.95f;
	SimpleMath::Vector3 posanimw = SimpleMath::Vector3::Transform(SimpleMath::Vector3(m_targetAnimationX, 0, 0), rot);

	//カメラの情報を親にセット
	GetParent()->SetTargetPosition(target + posanimw);
	GetParent()->SetEyePosition((((eye + target)- GetParent()->GetEyePosition())* PlaySceneCamera::TARGET_SPEED_RATE)+ GetParent()->GetEyePosition());
	GetParent()->SetUpPosition(up);
	
	//HPが０で死亡カメラ
	if (playerHP <= 0)
		GetParent()->SetIState(GetParent()->GetDeathCamera());

}

void NormalCamera::Mouse()
{
	//マウスを取得
	auto state = KeyboardSingleton::GetInstance()->GetMouseState();
	auto mouseTracker = KeyboardTracker::GetInstance()->GetMouseTracker();

	// マウスの左ボタンが押された
	if (mouseTracker.rightButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		// マウスの座標を取得
		m_x = state.x;
		m_y = state.y;
	}
	// マウスのボタンが押されていたらカメラを移動させる
	if (state.rightButton)		Motion(state.x, state.y);

	//徐々に視点を戻す
	m_xTmp *= PlaySceneCamera::MOUSE_SMOOTH;
	m_yTmp *= PlaySceneCamera::MOUSE_SMOOTH;

	//マウスのビュー行列を算出する
	SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(XMConvertToRadians(m_yTmp));
	SimpleMath::Matrix rotX = SimpleMath::Matrix::CreateRotationX(XMConvertToRadians(m_xTmp));
	m_mauseRotate = rotY* rotX;

}

void NormalCamera::Motion(const int& x, const int& y)
{
	// マウスポインタの位置のドラッグ開始位置からの変位 (相対値)
	float dx = static_cast<float>(x) - m_x;
	float dy = static_cast<float>(y) - m_y;

	// Ｙ軸の回転
	float yAngle = dx * PlaySceneCamera::MOUSE_SENSITIVITY;

	// Ｘ軸の回転
	float xAngle = dy * PlaySceneCamera::MOUSE_SENSITIVITY;

	//角度を代入
	m_xTmp = xAngle;
	m_yTmp = yAngle;

}

