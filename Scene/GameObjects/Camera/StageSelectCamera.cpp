//--------------------------------------------------------------------------------------
#include "pch.h"
#include "StageSelectCamera.h"
#include"Scene/GameObjects/Models/Draw.h"
using namespace DirectX;

const float TARGET_SPEED_RATE = 0.1f;		// カメラの位置への距離の差分に対する割合

//--------------------------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------------------------
StageSelectCamera::StageSelectCamera() :
	m_view(SimpleMath::Matrix::Identity),
	m_smooth(),
	m_target()
{
}

//--------------------------------------------------------------------------------------
// 更新
//--------------------------------------------------------------------------------------
void StageSelectCamera::Update(const DirectX::SimpleMath::Vector3& enemytarget)
{
	//eye,target,upの初期位置
	SimpleMath::Vector3 eye(0.0f, 50.0f, 15.0f);
	SimpleMath::Vector3 target(enemytarget);
	SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	m_eye = eye;
	//差分を足す
	m_target += (target - m_target) * TARGET_SPEED_RATE;

	m_up = up;
	//ビュー行列の作成
	m_view = SimpleMath::Matrix::CreateLookAt(eye, m_target, up);
	m_dir = -DirectX::SimpleMath::Vector3(m_view._13, m_view._23, m_view._33);

	//ビュー行列をセットする
	Draw::GetInstance()->SetView(m_view);
}

