#pragma once
#include"WindmillComponent.h"
/// <summary>
/// ボディークラスを定義する
/// </summary>
class WindmillRoom : public WindmillComponent
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
	WindmillRoom(
		IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& angle
	);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~WindmillRoom()override;
	
	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	void Update(
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& angle
	)override;

	/// <summary>
	/// 描画する
	/// </summary>
	void Render()override;
	
	/// <summary>
	/// 後処理
	/// </summary>
	void Finalize()override;

	/// <summary>
	/// 家の当たり判定
	/// </summary>
	/// <param name="objectsManager">家のポインタ</param>
	/// <returns>当たったら"true"</returns>

};
