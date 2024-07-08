#pragma once

#include "ImaseLib/RenderTexture.h"
#include "ImaseLib/DepthStencil.h"
#include"DeviceResources.h"
class CascadeShadowMap
{
public:

	// �R���X�g���N�^
	CascadeShadowMap();

	// ������
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
	// ���C�g�̉�]
	float GetLightDistance() { return m_LightDistance; };

private:
	// �V���h�E�}�b�v�p�i�����_�[�e�N�X�`���j
	std::unique_ptr<DX::RenderTexture> m_ShadowMapRT;
	// �V���h�E�}�b�v�p�i�f�v�X�X�e���V���j
	std::unique_ptr<Imase::DepthStencil> m_ShadowMapDS;
	// �V���h�E�}�b�v�p�i�����_�[�e�N�X�`���j
	std::unique_ptr<DX::RenderTexture> m_MoveShadowMapRT;

	// �V���h�E�}�b�v�p�i�f�v�X�X�e���V���j
	std::unique_ptr<Imase::DepthStencil> m_MoveShadowMapDS;

	// ���C�g�̈ʒu
	DirectX::SimpleMath::Matrix m_proj;
	// ���C�g�̉�]
	float m_LightDistance;
};


