#pragma once
#include "IStateAirshipFactory.h"

class Player;
class Airship;
class IStateAirship;

/// <summary>
/// StateEnemyFactoryのクラスを定義する
/// </summary>
class StateAirshipFactory : public IStateAirshipFactory
{
public:
	/// <summary>
	/// 通常の状態を生成
	/// </summary>
	/// <param name="parent">親のアイテムのアドレス</param>
	/// <param name="coinManager">プレイヤーのアドレス</param>
	/// <returns>通常の状態のポインタ</returns>
	static std::unique_ptr<IStateAirship> CreateAirshipMotion(
		Airship* enemy,
		Player* player
	);

	/// <summary>
	/// 通常２の状態を生成
	/// </summary>
	/// <param name="parent">親のアイテムのアドレス</param>
	/// <param name="coinManager">プレイヤーのアドレス</param>
	/// <returns>通常２の状態のポインタ</returns>
	static std::unique_ptr<IStateAirship> CreateAirshipMotion_01(
		Airship* enemy,
		Player* player
	);

};

