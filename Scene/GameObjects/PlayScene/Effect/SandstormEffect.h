//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// メニュークラス
//
//-------------------------------------------------------------------------------------

#pragma once

#include "ImaseLib/ParticleUtility.h"
#include "ImaseLib/ParticleSandstorm.h"
#include <random>
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
class BenchManager;
class StreetLightManager;
/// <summary>
/// 煙のエフェクトのクラスを定義する
/// </summary>
class SandstormEffect
{
public:

	static const float SPEED;
	static const float COLLIDER_ADJUSTMENT;
	static const int SANDSTORM_OFFENSIVE_POWER = 200;
	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }


	//大まかな当たり判定のゲッター
	Collider::Box* GetCollider() { return m_colloder.get(); }

	//位置のセッター、ゲッター
	bool GetSurvival() const { return m_survival; }
	void SetSurvival(const bool& survival) { m_survival = survival; }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SandstormEffect();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SandstormEffect();

	////初期化
	void Initialize(BenchManager* benchManager, StreetLightManager* streetLightManager);


	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">フレーム時間</param>
	/// <param name="position">描画位置</param>
	/// <param name="rotate">描画調整角度</param>
	void Update(const float& elapsedTime);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

	void SetpositionRandam(const float& min, const float& max);

private:
	//パーティクルのポインタ
	std::unique_ptr<ParticleSandstorm> m_particle;

	//パーティクルのポインタ
	std::unique_ptr<Collider::Box> m_colloder;

	DirectX::SimpleMath::Vector3 m_position;

	//描画クールタイム
	float m_timer;

	bool m_survival;

	BenchManager* m_pBenchManager;

	StreetLightManager* m_pStreetLightManager;
};
