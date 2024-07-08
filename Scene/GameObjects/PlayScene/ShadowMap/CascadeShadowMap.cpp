#include "pch.h"
#include "CascadeShadowMap.h"
#include"CascadeShadowMapManager.h"
using namespace DirectX;
CascadeShadowMap::CascadeShadowMap()
{

}

void CascadeShadowMap::Initialize(
	DX::DeviceResources* deviceResources, 
	float lightDistance, 
	DirectX::SimpleMath::Vector3 targetPosition, 
	DirectX::SimpleMath::Vector3 lightDir,
	float maxCascadeShadowDistance
)
{
	targetPosition;
	auto device = deviceResources->GetD3DDevice();

	RECT rect = { 0, 0, CascadeShadowMapManager::SHADOWMAP_SIZE, CascadeShadowMapManager::SHADOWMAP_SIZE };

	m_ShadowMapDS = std::make_unique<Imase::DepthStencil>(DXGI_FORMAT_D32_FLOAT);
	m_ShadowMapDS->SetDevice(device);
	m_ShadowMapDS->SetWindow(rect);

	m_ShadowMapRT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
	m_ShadowMapRT->SetDevice(device);
	m_ShadowMapRT->SetWindow(rect);

	m_MoveShadowMapDS = std::make_unique<Imase::DepthStencil>(DXGI_FORMAT_D32_FLOAT);
	m_MoveShadowMapDS->SetDevice(device);
	m_MoveShadowMapDS->SetWindow(rect);

	m_MoveShadowMapRT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
	m_MoveShadowMapRT->SetDevice(device);
	m_MoveShadowMapRT->SetWindow(rect);

	m_LightDistance = lightDistance;

	// シャドウ マップの視点からの奥行き範囲
	float nearClip = 0.1f;
	float farClip = m_LightDistance;

	m_proj = SimpleMath::Matrix::CreateOrthographic(farClip * 2, farClip * 2, nearClip, (maxCascadeShadowDistance) * 2);

}
