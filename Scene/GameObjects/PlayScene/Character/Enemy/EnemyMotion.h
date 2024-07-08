#pragma once
#include"Scene/GameObjects/PlayScene/Character/Player/IState.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Enemy.h"
class EnemyManager;
class Enemy;

/// <summary>
/// 敵の通常状態のクラスを定義する
/// </summary>
class EnemyMotion :public IState
{
public:
	/// <summary>
	/// コンテキスト
	/// </summary>
	/// <param name="parent">敵のアドレス</param>
	/// <param name="enemyManager">敵のマネージャーのアドレス</param>
	/// <param name="player">プレイヤーのアドレス</param>
	EnemyMotion(
		Enemy* parent,
		EnemyManager* enemyManager, 
		Player* player
	);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyMotion();

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
	/// <summary>
/// プレイヤーの動き
/// </summary>
/// <param name="elapsedTime">1フレーム時間</param>
	void Motion(const float& elapsedTime)override;

private:
	//プレイヤーのポインタ
	Player* m_pPlayer;

	//敵のポインタ
	Enemy* m_pEnemy;

	//敵のマネージャーのポインタ
	EnemyManager* m_pEnemyManager;
};
