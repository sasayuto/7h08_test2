#pragma once
#include"CrabRobot.h"


//蟹ロボット１のクラスを定義する
class CrabRobotCustom_00 :public CrabRobot
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="Hp">敵のHP</param>
	/// <param name="offensivePower">敵のパワー</param>
	CrabRobotCustom_00(const int& Hp, const int& offensivePower);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CrabRobotCustom_00();

	/// <summary>
	/// 初期化する
	/// </summary>
	/// <param name="bulletManager">球の管理者のアドレス</param>
	/// <param name="crabRobotManager">蟹ロボットの管理者のアドレス</param>
	/// <param name="airshipManager">飛行船の管理者のアドレス</param>
	/// <param name="floor">床のアドレス</param>
	/// <param name="sandstormManager">砂嵐のアドレス</param>
	void Initialize(
		BulletManager* bulletManager,
		CrabRobotManager* crabRobotManager,
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
