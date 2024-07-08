#pragma once
#include"FuelSupplyPoint.h"
#include"HpSupplyPoint.h"
#include"Coin.h"

/// <summary>
/// コインの管理者のクラスを定義する
/// </summary>
class CoinManager
{
public:
	//コイン数のゲッター
	unsigned int GetCount()const{ return m_coinCount; }

	//シーン変更フラグのゲッター
	bool GetSceneFlag()const { return m_sceneFlag; }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CoinManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CoinManager();

	//初期化する
	void Intialize(std::string failName);

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
	/// シャドウマップ用の画像を作る
	/// </summary>
	void RenderShadowTex();

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
	//アイテムのポインタ
	std::vector<std::unique_ptr<Item>> m_supplyPointList;

	//コイン数
	unsigned int m_coinCount;

	//シーン変更のフラグ
	bool m_sceneFlag;
};