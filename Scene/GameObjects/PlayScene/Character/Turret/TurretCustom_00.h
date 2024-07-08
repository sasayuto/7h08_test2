#pragma once
#include"Turret.h"


//TurretCustom_00のクラスを定義する
class TurretCustom_00 :public Turret
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="Hp">敵のHP</param>
	/// <param name="Fuel">敵の燃料</param>
	/// <param name="offensivePower">敵のパワー</param>
	TurretCustom_00(const int& Hp, const int& offensivePower);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TurretCustom_00();

	/// <summary>
	/// 初期化する
	/// </summary>
	/// <param name="bulletManager">球のアドレス</param>
	/// <param name="turretManager">タレットの管理者のアドレス</param>
	/// <param name="airshipManager">飛行船の管理者のアドレス</param>
	/// <param name="floor">床のアドレス</param>
	/// <param name="sandstormManager">砂嵐の管理者のアドレス</param>
	void Initialize(
		BulletManager* bulletManager,
		TurretManager* turretManager,
		AirshipManager* airshipManager,
		Floor* floor,
		SandstormManager* sandstormManager
	)override;

	/// <summary>
	/// 動きをリセット
	/// </summary>
	void Reset()override;

private:
	//最大HP
	int m_maxHp;

	//攻撃力
	int m_OffensivePower;
};
