#pragma once
#include"Scene/GameObjects/PlayScene/Character/Player/IState.h"
#include"Player.h"

class Player;

/// <summary>
/// 死亡状態のクラスを定義する
/// </summary>
class KillMotion :public IState
{
public:
	static const float FALL_SPEED_ACCELERATION;	//落下の加速度			(m/s)
	static const float EXPLOSIVE_POWER_XZ;		//爆発の横のパワー		(m/s)
	static const float EXPLOSIVE_A;				//爆発の横のパワー		(m/s)
	static const float EXPLOSIVE_ROTATE;		//モデルの回転の速さ	(°/s）
	static const float NEXT_MOTION_TIME;		//次の状態までの時間	(s)

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	KillMotion(Player* parent);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~KillMotion();

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

	/// <summary>
	/// プレイヤーの動き
	/// </summary>
	/// <param name="elapsedTime">1フレーム時間</param>
	void Motion(const float& elapsedTime)override;
private:
	//親のアドレス
	Player* m_pPlayer;

	//死亡した時の回転
	DirectX::SimpleMath::Quaternion m_killrotate;

	//次の動きまでの時間
	float m_nextMotionTime;
};
