#pragma once
#include"ICrabRobotState.h"
#include"../CrabRobot.h"

/// <summary>
/// 敵の死亡状態のクラスを定義する
/// </summary>
class CrabRobotKillMotion :public ICrabRobotState
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
	/// <param name="parent">親のアドレス</param>
	CrabRobotKillMotion(CrabRobot* crabRobot);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CrabRobotKillMotion();

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
	//親のポインタ
	CrabRobot* m_pCrabRobot;

	//死亡した時の回転
	DirectX::SimpleMath::Quaternion m_killrotate;

	//次の動きまでの時間
	float m_nextMotionTime;
};
