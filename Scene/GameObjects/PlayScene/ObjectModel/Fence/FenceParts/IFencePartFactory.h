#pragma once
#include <combaseapi.h>

struct IMoveObjectsComponent;
/// <summary>
/// IPlayerPartFactoryインタフェースを定義する
/// </summary>
interface IFencePartFactory
{
	/// <summary>
	///　ライトを生成する
	/// </summary>
	/// <param name="parent">親のアドレス</param>
	/// <param name="position">親の位置</param>
	/// <param name="angle">親の角度</param>
	/// <returns>ライトのアドレス</returns>
	virtual std::unique_ptr<IMoveObjectsComponent> Create(
		const IMoveObjectsComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;
};