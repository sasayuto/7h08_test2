#pragma once
#include"Scene/GameObjects/PlayScene/Character/Player/IState.h"
#include"Player.h"
#include"Scene/GameObjects/PlayScene/Item/SupplyPointManager.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/EnemyManager.h"
#include"Scene/GameObjects/PlayScene/Item/RespawnManager.h"
#include"Scene/GameObjects/PlayScene/Item/CoinManager.h"
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"
#include"Scene/GameObjects/PlayScene/Effect/PlayerEffect.h"
#include"Scene/GameObjects/PlayScene/Effect/BloodEffect.h"

class Player;
class EnemyManager;

/// <summary>
/// 停止状態のクラスを定義する
/// </summary>
class PlayerStopMotion :public IState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="respawnManager">球の管理者のアドレス</param>
	/// <param name="respawnManager">リスポーン地点の管理者のアドレス</param>
	/// <param name="supplyPointManager">アイテムの管理者のアドレス</param>
	/// <param name="enemyManager">敵の管理者のアドレス</param>
	/// <param name="coinManager">コインの管理者のアドレス</param>
	PlayerStopMotion(
		Player* parent,
		BulletManager* bulletManager,
		RespawnManager* respawnManager,
		SupplyPointManager* supplyPointManager,
		EnemyManager* enemyManager,
		CoinManager* coinManager
	);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerStopMotion();

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 処理を実行する
	/// </summary>
	/// <param name="elapsedTime">1フレーム時間</param>
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
	//親のポインタ
	Player* m_pPlayer;

	//リスポーン地点の管理者のポインタ
	RespawnManager* m_pRespawnManager;

	//アイテムの管理者のポインタ
	SupplyPointManager* m_pSupplyPointManager;

	//敵の管理者のポインタ
	EnemyManager* m_pEnemyManager;

	//コインの管理者のポインタ
	CoinManager* m_pCoinManager;

	//球の管理者のアドレス
	BulletManager* m_pBulletManager;
};
