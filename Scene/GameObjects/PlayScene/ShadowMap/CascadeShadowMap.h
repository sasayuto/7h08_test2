#pragma once

#include "ImaseLib/RenderTexture.h"
#include "ImaseLib/DepthStencil.h"
#include"DeviceResources.h"
class CascadeShadowMap
{
public:

	// コンストラクタ
	CascadeShadowMap();

	// 初期化
	void Initialize(DX::DeviceResources* deviceResources,
		float lightDistance,
		DirectX::SimpleMath::Vector3 targetPosition, 
		DirectX::SimpleMath::Vector3 lightDir,
		float maxCascadeShadowDistance
	);

	DirectX::SimpleMath::Matrix GetProj()const { return m_proj; };
	DX::RenderTexture* GetMoveRenderTexture() { return m_MoveShadowMapRT.get(); }
	DX::RenderTexture* GetRenderTexture() { return m_ShadowMapRT.get(); }
	Imase::DepthStencil* GetMoveDepthStencil() { return m_MoveShadowMapDS.get(); }
	Imase::DepthStencil* GetDepthStencil() { return m_ShadowMapDS.get(); }
	// ライトの回転
	float GetLightDistance() { return m_LightDistance; };

private:
	// シャドウマップ用（レンダーテクスチャ）
	std::unique_ptr<DX::RenderTexture> m_ShadowMapRT;
	// シャドウマップ用（デプスステンシル）
	std::unique_ptr<Imase::DepthStencil> m_ShadowMapDS;
	// シャドウマップ用（レンダーテクスチャ）
	std::unique_ptr<DX::RenderTexture> m_MoveShadowMapRT;

	// シャドウマップ用（デプスステンシル）
	std::unique_ptr<Imase::DepthStencil> m_MoveShadowMapDS;

	// ライトの位置
	DirectX::SimpleMath::Matrix m_proj;
	// ライトの回転
	float m_LightDistance;
};


