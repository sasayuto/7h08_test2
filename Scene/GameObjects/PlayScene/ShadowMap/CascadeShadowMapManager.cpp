#include "pch.h"
#include "CascadeShadowMapManager.h"
#include <iomanip>
#include"Scene/GameObjects/Models/Draw.h"

const int CascadeShadowMapManager::CARE_EYE(30);
const int CascadeShadowMapManager::SHADOWMAP_SIZE(4096);

//������]
const DirectX::SimpleMath::Quaternion CascadeShadowMapManager::INITIAL_ROTATE(
	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(-135),						//X��]
		DirectX::XMConvertToRadians(45),						//Y��]
		DirectX::XMConvertToRadians(0)						//Z��]
	)
);

const float CascadeShadowMapManager::SUNSET_TIME(4);						//���v����	()
const float CascadeShadowMapManager::SUNSHINE_HOURS(180.0f / 100.0f);				//���Ǝ���	(m/s)

CascadeShadowMapManager::CascadeShadowMapManager():
	m_lightRotate(),
	m_lightDir()
{
}

void CascadeShadowMapManager::Initialize(DX::DeviceResources* deviceResources, DirectX::SimpleMath::Vector3 targetPosition, const int cascadeNum, float maxCascadeShadowDistance)
{
	m_maxCascadeShadowDistance = maxCascadeShadowDistance + CARE_EYE;
	//���ʂɉ�]����N�I�[�^�j�I��
	//�S�T�x�N���オ�点��x�����x�N�g��(���z�̌��̕����x�N�g��)
	m_lightDir = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), INITIAL_ROTATE);

	//cascade�̊���
	float lightDistancePercent[10] = { 5,15,50,100,100,100,100,100,100,100 };

	for (int i = 0; i < cascadeNum; i++)
	{
		lightDistancePercent[i] *= 0.01f;
		auto cascadeShadowMap = std::make_unique<CascadeShadowMap>();
		cascadeShadowMap->Initialize(deviceResources, maxCascadeShadowDistance * lightDistancePercent[i] , targetPosition, m_lightDir, m_maxCascadeShadowDistance);
		m_cascadeShadowMap.push_back(std::move(cascadeShadowMap));
	}
}

DirectX::SimpleMath::Matrix CascadeShadowMapManager::GetLightProj(int index)
{
	return m_cascadeShadowMap[index]->GetProj();
}

float CascadeShadowMapManager::GetLightDistance(int index)
{
	return m_cascadeShadowMap[index]->GetLightDistance();
}

void CascadeShadowMapManager::Update(float elapsedTime, float timer, DirectX::SimpleMath::Vector3 targetPosition)
{
	////���ʂɉ�]����N�I�[�^�j�I��
	//DirectX::SimpleMath::Quaternion q;
	//q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(elapsedTime * SUNSHINE_HOURS));
	//m_lightRotate = q * m_lightRotate;

	//�S�T�x�N���オ�点��x�����x�N�g��(���z�̌��̕����x�N�g��)
	//m_lightDir = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitX, m_lightRotate * INITIAL_ROTATE);


	DirectX::SimpleMath::Vector3 lightPos = -m_lightDir * (m_maxCascadeShadowDistance) + targetPosition;

	// �r���[�s����쐬
	m_MoveLightView = DirectX::SimpleMath::Matrix::CreateLookAt(
		lightPos,
		lightPos + m_lightDir,
		DirectX::SimpleMath::Vector3::UnitY
	);

	if (timer >= Draw::SHADOW_UPDATE_SECONDS)
		m_LightView = m_MoveLightView;
}


void CascadeShadowMapManager::Render()
{
}

DX::RenderTexture* CascadeShadowMapManager::GetRenderTexture(int index)
{
	return m_cascadeShadowMap[index]->GetRenderTexture();
}

Imase::DepthStencil* CascadeShadowMapManager::GetDepthStencil(int index)
{
	return m_cascadeShadowMap[index]->GetDepthStencil();
}
DX::RenderTexture* CascadeShadowMapManager::GetMoveRenderTexture(int index)
{
	return m_cascadeShadowMap[index]->GetMoveRenderTexture();
}

Imase::DepthStencil* CascadeShadowMapManager::GetMoveDepthStencil(int index)
{
	return m_cascadeShadowMap[index]->GetMoveDepthStencil();
}

void CascadeShadowMapManager::CreateDeviceDependentResources()
{
}
DirectX::SimpleMath::Quaternion CascadeShadowMapManager::Rotate(float x, float y, float z)
{
	return DirectX:: SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(x), DirectX::XMConvertToRadians(y), DirectX::XMConvertToRadians(z));
}

