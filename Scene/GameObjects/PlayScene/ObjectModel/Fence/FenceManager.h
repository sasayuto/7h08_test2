#pragma once
#include"Fence.h"
#include"../MoveObjects/MoveObjectsManager.h"
class Enemy;
class Player;
class Airship;
class BulletManager;
class SandstormEffect;
/// <summary>
/// オブジェクトの管理者のクラスを定義する
/// </summary>
class FenceManager : public MoveObjectsManager
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="mapLoader">マップのアドレス</param>
	FenceManager();
};