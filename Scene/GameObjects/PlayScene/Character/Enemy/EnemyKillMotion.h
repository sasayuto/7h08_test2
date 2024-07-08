#pragma once
#include"Scene/GameObjects/PlayScene/Character/Player/IState.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
class Enemy;

/// <summary>
/// 敵の死亡状態のクラスを定義する
/// </summary>
class EnemyKillMotion :public IState
{

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	EnemyKillMotion(Enemy* parent);

	/// <summary>
	/// プレイヤーの動き
	/// </summary>
	/// <param name="elapsedTime">1フレーム時間</param>
	void Motion(const float& elapsedTime)override;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyKillMotion();

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
	Enemy* m_pEnemy;

	//死亡した時の回転
	DirectX::SimpleMath::Quaternion m_killrotate;

	//次の動きまでの時間
	float m_nextMotionTime;
};
