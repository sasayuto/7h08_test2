#pragma once
#include <combaseapi.h>
#include <pch.h>

// ITurretComponentインタフェースを定義する
interface  IPlayerComponent
{
	// 親を取得する
	virtual IPlayerComponent* GetParent() = 0;

	// デストラクタ
	virtual ~IPlayerComponent() = default;

	// 初期化する
	virtual void Initialize() = 0;

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	virtual void Update(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle) = 0;

	// 描画する
	virtual void Render() = 0;

	// 爆発処理
	virtual void Explosion(float gravity) = 0;

	// 描画する
	virtual void Speed() = 0;

	// 後処理をおこなう
	virtual void Finalize() = 0;
};
