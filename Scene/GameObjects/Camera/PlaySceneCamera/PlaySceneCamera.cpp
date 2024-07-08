//--------------------------------------------------------------------------------------
#include "pch.h"
#include "PlaySceneCamera.h"
#include"Type/NormalCamera.h"
#include"Type/DeathCamera.h"
#include"Type/PlayerCameraFactory.h"
#include"Scene/GameObjects/Models/Draw.h"
using namespace DirectX;

const float PlaySceneCamera::EYE_SPEED_RATE = 0.1f;		// カメラの位置への距離の差分に対する割合
const float PlaySceneCamera::TARGET_SPEED_RATE = 0.07f;	// 注視点への距離の差分に対する割合
const float PlaySceneCamera::MOUSE_SENSITIVITY = 0.4f;	// マウス感度
const float PlaySceneCamera::MOUSE_SMOOTH = 0.90f;		// マウスを徐々に戻す

//--------------------------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------------------------
PlaySceneCamera::PlaySceneCamera() :
	m_view(SimpleMath::Matrix::Identity),
	m_eye(SimpleMath::Vector3::Zero),
	m_up(DirectX::SimpleMath::Vector3::Zero),
	m_target(DirectX::SimpleMath::Vector3::Zero),
	m_NormalCamera(nullptr),
	m_DeathCamera(nullptr),
	m_pCurrentState(nullptr)
{
}

PlaySceneCamera::~PlaySceneCamera()
{
}

void PlaySceneCamera::Initialize()
{
	//通常のカメラを生成
	m_NormalCamera = PlayerCameraFactory::CreateNormalCamera(this);

	//デスのカメラを生成
	m_DeathCamera = PlayerCameraFactory::CreateDeathCamera(this);

	//現在の状態に通常のカメラをセット
	m_pCurrentState = m_NormalCamera.get();
}

//--------------------------------------------------------------------------------------
// 更新
//--------------------------------------------------------------------------------------
void PlaySceneCamera::Update(
	const int& playerHP,
	const SimpleMath::Quaternion& rotate,
	const SimpleMath::Vector3& position
)
{
	//現在の状態を更新する
	m_pCurrentState->Update(playerHP,rotate,position);

	//ビュー行列の作成
	m_view = SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);

	//カメラの方向を計算
	m_dir = -DirectX::SimpleMath::Vector3(m_view._13, m_view._23, m_view._33);

	//ビュー行列をセットする
	Draw::GetInstance()->SetView(m_view);
}
