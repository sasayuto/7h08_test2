#pragma once
#include "DeviceResources.h"

/// <summary>
/// Texturesクラスを定義する
/// </summary>
class SingletonDeviceResources
{
public:
	/// <summary>
	/// 描画クラスのインスタンスを取得する
	/// </summary>
	/// <returns>描画クラスのインスタンス</returns>
	static SingletonDeviceResources* GetInstance();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SingletonDeviceResources();

	DX::DeviceResources* GetDeviceResources() { return m_DeviceResources; };
	void SetDeviceResources(DX::DeviceResources* deviceResources) { m_DeviceResources = deviceResources; };

	// 共通ステートオブジェクトのポインタ
	DirectX::CommonStates* GetCommonStates() { return m_commonStates; };
	void SetCommonStates(DirectX::CommonStates* commonStates) { m_commonStates = commonStates; };

	DirectX::SimpleMath::Matrix* GetProj() { return &m_proj; };

	void Initialize();

private:
	// 描画のインスタンスへのポインタ
	static std::unique_ptr<SingletonDeviceResources> m_SingletonDeviceResources;

	DX::DeviceResources* m_DeviceResources;

	// 共通ステートオブジェクトのポインタ
	DirectX::CommonStates* m_commonStates;

	DirectX::SimpleMath::Matrix m_proj;
};


