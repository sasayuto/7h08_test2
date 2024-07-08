#pragma once
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Player/PlayerComponent.h"

/// <summary>
/// 羽のクラスを定義する
/// </summary>
class LeftTire : public PlayerComponent
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
	LeftTire(
		IPlayerComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LeftTire()override;

	/// <summary>
	/// 初期化する
	/// </summary>
	/// <param name="angle">反射ベクトル</param>
	void Initialize(const DirectX::SimpleMath::Vector3& reflectionVector)override;

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
	///爆発処理
	/// </summary>
	void Explosion()override;

	/// <summary>
	/// 後処理
	/// </summary>
	void Finalize()override;

	/// <summary>
	/// 加速処理
	/// </summary>
	void Speed()override;	

};