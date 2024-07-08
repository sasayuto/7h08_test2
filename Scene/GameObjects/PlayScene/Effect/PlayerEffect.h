//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// メニュークラス
//
//-------------------------------------------------------------------------------------

#pragma once

#include "ImaseLib/ParticleUtility.h"
#include "ImaseLib/Particle.h"
#include <random>

/// <summary>
/// 煙のエフェクトのクラスを定義する
/// </summary>
class PlayerEffect
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerEffect();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerEffect();

	////初期化
	void Initialize();


	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">フレーム時間</param>
	/// <param name="position">描画位置</param>
	/// <param name="rotate">描画調整角度</param>
	void Update(
		const float& elapsedTime, 
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& rotate,
		const int& HP
	);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

private:
	//パーティクルのポインタ
	std::unique_ptr<Particle> m_particle;

	//描画クールタイム
	float m_timer;
};
