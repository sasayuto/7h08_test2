#pragma once
#include"ITurretState.h"
#include"../Turret.h"

/// <summary>
/// タレットの死亡状態のクラスを定義する
/// </summary>
class TurretKillMotion :public ITurretState
{
private:
	/// <summary>
	/// 動き
	/// </summary>
	void Motion();

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">タレットのアドレス</param>
	TurretKillMotion(Turret* turret);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TurretKillMotion();

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 処理を実行する
	/// </summary>
	/// <param name="elapsedTime">フレーム時間</param>
	void Update(const float& elapsedTime)override;

	/// <summary>
	/// 描画する
	/// </summary>
	void Render()override;

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize()override;

private:
	//タレットのポインタ
	Turret* m_pTurret;

	//死亡した時の回転
	DirectX::SimpleMath::Quaternion m_killrotate;

	//次の動きまでの時間
	float m_nextMotionTime;
};
