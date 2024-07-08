//--------------------------------------------------------------------------------------
// File: ParticleUtil.h
//
// パーティクルユーティリティクラス
//
//-------------------------------------------------------------------------------------

#pragma once
class ParticleUtility
{
	//変数
private:


	//関数
private:
	//座標
	DirectX::SimpleMath::Vector3 m_position;

	//速度
	DirectX::SimpleMath::Vector3 m_velocity;

	//加速度
	DirectX::SimpleMath::Vector3 m_accele;

	//回転
	DirectX::SimpleMath::Vector3 m_rotateSpeed;

	//スケール
	DirectX::SimpleMath::Vector3 m_nowScale;
	DirectX::SimpleMath::Vector3 m_startScale;
	DirectX::SimpleMath::Vector3 m_endScale;

	//生存時間
	float m_life;
	float m_startLife;

	//カラー
	DirectX::SimpleMath::Color m_nowColor;
	DirectX::SimpleMath::Color m_startColor;
	DirectX::SimpleMath::Color m_endColor;

	//関数
public:
	//コンストラクタ（初期設定）
	ParticleUtility(
		float life,
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Vector3 velocity,
		DirectX::SimpleMath::Vector3 accele,
		DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
		DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor,
		DirectX::SimpleMath::Vector3 rotateSpeed = DirectX::SimpleMath::Vector3::Zero
	);
	//デストラクタ
	~ParticleUtility();

	// 更新
	bool Update(float elapsedTime);

	// 更新
	void RotateUpdate();

	//getter
	DirectX::SimpleMath::Vector3 GetPosition()const { return m_position; }

	DirectX::SimpleMath::Vector3 GetVelocity()const { return m_velocity; }

	DirectX::SimpleMath::Vector3 GetAccele() const { return m_accele; }

	DirectX::SimpleMath::Vector3 GetNowScale() const { return m_nowScale; }
	DirectX::SimpleMath::Vector3 GetStartScale() const { return m_startScale; }
	DirectX::SimpleMath::Vector3 GetEndScale()const { return m_endScale; }

	float GetLife() const { return m_life; }
	float GetStartLife() const { return m_startLife; }
	DirectX::SimpleMath::Color GetNowColor()const { return m_nowColor; }
	DirectX::SimpleMath::Color GetStartColor() const { return m_startColor; }
	DirectX::SimpleMath::Color GetEndColor()const { return m_endColor; }



};

