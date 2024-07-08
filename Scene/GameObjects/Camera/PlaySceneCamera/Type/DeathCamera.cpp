//--------------------------------------------------------------------------------------
#include "pch.h"
#include "DeathCamera.h"
#include"../PlaySceneCamera.h"
using namespace DirectX;

const DirectX::SimpleMath::Vector3 DeathCamera::EYE_INITIAL_VALUE(0, 0, 25);	//視点の初期値

//--------------------------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------------------------
DeathCamera::DeathCamera() :
	StatePlaySceneCamera(),
	m_mauseRotate(SimpleMath::Matrix::Identity),
	m_yTmp(0.0f),
	m_xTmp(0.0f), m_x(0), m_y(0),
	m_targetAnimationX(0),
	m_target()
{
}

void DeathCamera::Reset()
{
	m_yTmp = 0;
}

//--------------------------------------------------------------------------------------
// 更新
//--------------------------------------------------------------------------------------
void DeathCamera::Update(
	const int& playerHP,
	const SimpleMath::Quaternion& rot, 
	const SimpleMath::Vector3& playerPosition)
{
	//マウスの処理
	//Mouse();

	//eye,target,upの初期位置
	SimpleMath::Vector3 eye(EYE_INITIAL_VALUE);
	SimpleMath::Vector3 target(playerPosition);
	SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	//カメラの位置を注視点の５分の一下にする
	target += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, eye.z / 5.0f, 0.0f), rot);

	//ぷれいやーの回転
	eye = SimpleMath::Vector3::Transform(eye,rot);
	up = SimpleMath::Vector3::Transform(up, rot);

	//カメラの情報を親にセット
	GetParent()->SetTargetPosition(((target - GetParent()->GetTargetPosition()) * PlaySceneCamera::TARGET_SPEED_RATE) + GetParent()->GetTargetPosition());
	GetParent()->SetEyePosition((((eye + target) - GetParent()->GetEyePosition()) * PlaySceneCamera::EYE_SPEED_RATE) + GetParent()->GetEyePosition());
	GetParent()->SetUpPosition(up);

	//HPが０より上だったら通常のカメラ
	if (playerHP > 0)
		GetParent()->SetIState(GetParent()->GetNormalCamera());
}

