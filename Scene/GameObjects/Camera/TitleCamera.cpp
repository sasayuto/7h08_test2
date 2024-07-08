//--------------------------------------------------------------------------------------
#include "pch.h"
#include "TitleCamera.h"
#include"Scene/GameObjects/Models/Draw.h"
using namespace DirectX;

const float SPEED_RATE = 0.07f;	// 距離の差分に対する割合

//--------------------------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------------------------
TitleCamera::TitleCamera() :
	m_view(SimpleMath::Matrix::Identity),
	m_smooth(),
	m_eye(DirectX::SimpleMath::Vector3::Zero),
	m_up(DirectX::SimpleMath::Vector3::Zero),
	m_target(DirectX::SimpleMath::Vector3::Zero)
{
}

TitleCamera::~TitleCamera()
{
}

//--------------------------------------------------------------------------------------
// 更新
//--------------------------------------------------------------------------------------
void TitleCamera::Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate)
{
	//eye,target,upの初期位置
	SimpleMath::Vector3 eye(0.0f, 2.0f, 8.0f);
	SimpleMath::Vector3 target(position+DirectX::SimpleMath::Vector3(0,1,0));
	SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	//ぷれいやーの回転
	eye = SimpleMath::Vector3::Transform(eye, rotate);
	up = SimpleMath::Vector3::Transform(up, rotate);

	//移動
	m_eye += (eye - m_eye) * 0.1f;

	//差分を足す
	m_target += (target - m_target) * 0.1f;

	m_up = up;

	//ビュー行列の作成
	m_view = SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);

	m_dir = -DirectX::SimpleMath::Vector3(m_view._13, m_view._23, m_view._33);
	//ビュー行列をセットする
	Draw::GetInstance()->SetView(m_view);
}

