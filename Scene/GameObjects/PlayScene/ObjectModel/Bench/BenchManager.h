#pragma once
#include"Bench.h"
#include"../MoveObjects/MoveObjectsManager.h"
class Enemy;
class Player;
class Airship;
class BulletManager;
class SandstormEffect;
/// <summary>
/// オブジェクトの管理者のクラスを定義する
/// </summary>
class BenchManager : public MoveObjectsManager
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="mapLoader">マップのアドレス</param>
	BenchManager();
};