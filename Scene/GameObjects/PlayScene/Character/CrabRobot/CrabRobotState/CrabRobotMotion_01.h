#pragma once
#include"ICrabRobotState.h"
class CrabRobotManager;
class CrabRobot;

/// <summary>
/// 敵の通常状態のクラスを定義する
/// </summary>
class CrabRobotMotion_01 :public ICrabRobotState
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
	/// <param name="parent">蟹ロボットのアドレス</param>
	/// <param name="enemyManager">ロボットのマネージャーのアドレス</param>
	CrabRobotMotion_01(CrabRobot* crabRobot, CrabRobotManager* crabRobotManager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CrabRobotMotion_01();

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
	//敵のポインタ
	CrabRobot* m_pCrabRobot;

	//敵のマネージャーのポインタ
	CrabRobotManager* m_pCrabRobotManager;
};
