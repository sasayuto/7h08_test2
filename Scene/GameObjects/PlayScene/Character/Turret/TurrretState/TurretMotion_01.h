#pragma once
#include"ITurretState.h"
class TurretManager;
class Turret;

/// <summary>
/// タレットの通常状態1のクラスを定義する
/// </summary>
class TurretMotion_01 :public ITurretState
{

public:		
	/// <summary>
	/// プレイヤーの動き
	/// </summary>
	void Motion();

public:
	/// <summary>
	/// コンテキスト
	/// </summary>
	/// <param name="parent">タレットのアドレス</param>
	/// <param name="enemyManager">タレットのマネージャーのアドレス</param>
	TurretMotion_01(Turret* turret, TurretManager* turretManager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TurretMotion_01();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">１フレーム時間</param>
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

	//タレットのマネージャーのポインタ
	TurretManager* m_pTurretManager;
};
