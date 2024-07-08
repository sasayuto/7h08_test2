#pragma once
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"Bullet.h"
/// <summary>
/// タレットの球のクラスを定義する
/// </summary>
class Bullet_Turret :public Bullet
{
public:
	static const float FALL_SPEED_ACCELERATION;	//落下の加速度			(m/s)


	/// <summary>
	/// コンストラクタ
	/// </summary>
	Bullet_Turret();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Bullet_Turret();

	/// <summary>
/// 処理を実行する
/// </summary>
	void Update()override;

private:
	//重力
	float m_gravity;
};