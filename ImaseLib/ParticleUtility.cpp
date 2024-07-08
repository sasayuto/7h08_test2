//--------------------------------------------------------------------------------------
// File: ParticleUtil.cpp
//
// パーティクルユーティリティクラス
// positionや速度などパーティクル１つに必要な要素を格納
//
//-------------------------------------------------------------------------------------
#include "pch.h"
#include "Particleutility.h"


using namespace DirectX;

/// <summary>
/// コンストラクタ
/// 引数は初期設定用の数値
/// </summary>
/// <param name="life">生存時間</param>
/// <param name="pos">座標</param>
/// <param name="velocity">速度</param>
/// <param name="accele">加速度</param>
/// <param name="startScale">初期サイズ</param>
/// <param name="endScale">最終サイズ</param>
/// <param name="startColor">初期色</param>
/// <param name="endColor">最終色</param>
ParticleUtility::ParticleUtility(
	float life,
	DirectX::SimpleMath::Vector3 pos,
	DirectX::SimpleMath::Vector3 velocity,
	DirectX::SimpleMath::Vector3 accele,
	DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
	DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor,
	DirectX::SimpleMath::Vector3 rotateSpeed
)
{
	m_startLife =
		m_life = life;

	m_position = pos;
	m_velocity = velocity;
	m_accele = accele;

	m_startScale =
		m_nowScale = startScale;
	m_endScale = endScale;

	m_startColor =
		m_nowColor = startColor;
	m_endColor = endColor;

	m_rotateSpeed = rotateSpeed;
}
/// <summary>
/// デストラクタ
/// </summary>
ParticleUtility::~ParticleUtility()
{
}
/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">Game等からStepTimerを受け取る</param>
/// <returns>生存時間(life)がある間はtrue</returns>
bool ParticleUtility::Update(float elapsedTime)
{
	// スケール
	m_nowScale = SimpleMath::Vector3::Lerp(m_startScale, m_endScale, 1.0f - m_life / m_startLife);
	// 色
	m_nowColor = SimpleMath::Color::Lerp(m_startColor, m_endColor, 1.0f - m_life / m_startLife);
	// 速度の計算
	m_velocity += m_accele * elapsedTime;
	// 座標の計算
	m_position += m_velocity * elapsedTime;
	m_life -= elapsedTime;
	// ライフが０で自身を消してもらう
	if (m_life < 0.0f)
	{
		return false;
	}

	return true;
}

void ParticleUtility::RotateUpdate()
{
	SimpleMath::Quaternion q = SimpleMath::Quaternion::Identity;
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, m_life * m_rotateSpeed.x);
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, m_life * m_rotateSpeed.y);
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, m_life * m_rotateSpeed.z);
	m_position += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0, 0, 1), q);
}


