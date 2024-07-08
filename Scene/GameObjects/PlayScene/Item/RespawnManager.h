#pragma once
#include"Respawn.h"
struct IPlayerComponent;


/// <summary>
/// リスポーン地点の管理者のクラスを定義する
/// </summary>
class RespawnManager
{
public:
	//リスポーンの位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetRespawnPosition() const{ return m_respawnPosition; }
	void SetRespawnPosition(const DirectX::SimpleMath::Vector3& respawnPosition) { m_respawnPosition = respawnPosition; }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	RespawnManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~RespawnManager();

	//初期化する
	void Intialize();

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">1フレーム時間</param>
	void Update(const float& elapsedTime);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();

	/// <summary>
	/// プレイヤーと球の当たり判定
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	void CheckHitCharacter(Player* player);

private:
	//リスポーン地点のポインタ
	std::vector<std::unique_ptr<Item>> m_RespawnList;

	//リスポーン地点のセットポジション
	DirectX::SimpleMath::Vector3 m_respawnPosition;
};