#include "pch.h"
#include "SingletonDeviceResources.h"

using namespace DirectX;
std::unique_ptr<SingletonDeviceResources> SingletonDeviceResources::m_SingletonDeviceResources = nullptr;

SingletonDeviceResources::SingletonDeviceResources()
{
}

void SingletonDeviceResources::Initialize()
{
	RECT WindouSize = m_DeviceResources->GetOutputSize();
	// 射影行列の作成
	m_proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f), static_cast<float>(WindouSize.right) / static_cast<float>(WindouSize.bottom), 0.1f, 10000);

}

SingletonDeviceResources* SingletonDeviceResources::GetInstance()
{
	//すでに生成されてるかチェック
	if (m_SingletonDeviceResources == nullptr)
	{
		//画像のインスタンスを生成する
		m_SingletonDeviceResources = std::make_unique<SingletonDeviceResources>();
	}
	//画像のインスタンスを返す
	return m_SingletonDeviceResources.get();
}

