#pragma once
#include"../../MoveObjects/MoveObjectsParts/MoveObjectsComponent.h"
/// <summary>
/// ボディークラスを定義する
/// </summary>
class BenchBackWood : public MoveObjectsComponent
{
public:
	static const float FALL_SPEED_ACCELERATION;		//落下の加速度		(m/s)
	static const float EXPLOSIVE_ROTATE;		//モデルの回転の速さ(°/s）
	static const float EXPLOSIVE_RANDOM_POWER;	//爆発のランダムな方向のパワー		(m/s)
	static const float EXPLOSIVE_POWER;			//爆発の方向のパワー		(m/s)

public:
	/// <summary>
	/// 処理を実行する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	BenchBackWood(
		IMoveObjectsComponent* parent,
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& angle
	);
	
};
