//--------------------------------------------------------------------------------------
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
/// 光るエフェクトのクラスを定義
/// </summary>
class LightEffect
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	LightEffect();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LightEffect();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();


	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">1フレーム時間</param>
	/// <param name="position">描画位置</param>
	void Update(
		const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position
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
