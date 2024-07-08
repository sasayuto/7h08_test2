#pragma once
#include"Airship.h"


//敵のクラスを定義する
class AirshipCustom_00 :public Airship
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="Hp">敵のHP</param>
	/// <param name="Fuel">敵の燃料</param>
	/// <param name="offensivePower">敵のパワー</param>
	AirshipCustom_00(const int& Hp, const int& Fuel, const int& offensivePower);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~AirshipCustom_00();

	/// <summary>
	/// 初期化する
	/// </summary>
	/// <param name="bulletManager">球のアドレス</param>
	/// <param name="enemyManager">敵のマネージャーのアドレス</param>
	/// <param name="player">プレイヤーのアドレス</param>
	void Initialize(
		BulletManager* bulletManager,
		ObjectsManager* objectsManager,
		Player* player
	)override;

	/// <summary>
/// 動きをリセット
/// </summary>
	void Reset()override;

private:
	int m_maxHp;

	int m_maxFuel;

	int m_OffensivePower;
};
