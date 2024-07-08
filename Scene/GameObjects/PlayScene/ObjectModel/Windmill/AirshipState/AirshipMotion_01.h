#pragma once

#include"IAirshipState.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
/// <summary>
/// 敵の通常状態のクラスを定義する
/// </summary>
class AirshipMotion_01 :public IStateAirship
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
	/// <param name="parent">敵のアドレス</param>
	/// <param name="enemyManager">敵のマネージャーのアドレス</param>
	/// <param name="player">プレイヤーのアドレス</param>
	AirshipMotion_01(Airship* parent, Player* player);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~AirshipMotion_01();

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
	//プレイヤーのポインタ
	Player* m_pPlayer;

	//敵のポインタ
	Airship* m_pAirship;
};
