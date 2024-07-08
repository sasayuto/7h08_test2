#include "pch.h"
#include "CascadeShadowMapManager.h"
#include <iomanip>
#include"Scene/GameObjects/Models/Draw.h"

const int CascadeShadowMapManager::CARE_EYE(30);
const int CascadeShadowMapManager::SHADOWMAP_SIZE(4096);

//初期回転
const DirectX::SimpleMath::Quaternion CascadeShadowMapManager::INITIAL_ROTATE(
	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(-135),						//X回転
		DirectX::XMConvertToRadians(45),						//Y回転
		DirectX::XMConvertToRadians(0)						//Z回転
	)
);

const float CascadeShadowMapManager::SUNSET_TIME(4);						//日没時間	()
const float CascadeShadowMapManager::SUNSHINE_HOURS(180.0f / 100.0f);				//日照時間	(m/s)

CascadeShadowMapManager::CascadeShadowMapManager():
	m_lightRotate(),
	m_lightDir()
{
}

void CascadeShadowMapManager::Initialize(DX::DeviceResources* deviceResources, DirectX::SimpleMath::Vector3 targetPosition, const int cascadeNum, float maxCascadeShadowDistance)
{
	m_maxCascadeShadowDistance = maxCascadeShadowDistance + CARE_EYE;
	//平面に回転するクオータニオン
	//４５度起き上がらせたx方向ベクトル(太陽の光の方向ベクトル)
	m_lightDir = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), INITIAL_ROTATE);

	//cascadeの割合
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
	////平面に回転するクオータニオン
	//DirectX::SimpleMath::Quaternion q;
	//q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(elapsedTime * SUNSHINE_HOURS));
	//m_lightRotate = q * m_lightRotate;

	//４５度起き上がらせたx方向ベクトル(太陽の光の方向ベクトル)
	//m_lightDir = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitX, m_lightRotate * INITIAL_ROTATE);


	DirectX::SimpleMath::Vector3 lightPos = -m_lightDir * (m_maxCascadeShadowDistance) + targetPosition;

	// ビュー行列を作成
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

