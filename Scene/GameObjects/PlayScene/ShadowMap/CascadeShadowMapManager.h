#pragma once


#include"CascadeShadowMap.h"
class RenderTexture;
#include"ImaseLib/DepthStencil.h"
class CascadeShadowMapManager
{
public:
	// シャドウマップのサイズ
	static const int SHADOWMAP_SIZE;
	static const int CARE_EYE;
	//位置
	static const DirectX::SimpleMath::Quaternion INITIAL_ROTATE;

	static const float SUNSET_TIME;
	static const float SUNSHINE_HOURS;

	// コンストラクタ
	CascadeShadowMapManager();

	void Initialize(DX::DeviceResources* deviceResources, DirectX::SimpleMath::Vector3 targetPosition,const int cascadeNum,float maxCascadeShadowDistance);
	// 初期化	
	// 更新
	void Update(float elapsedTime,float timer, DirectX::SimpleMath::Vector3 targetPosition);


	void Render();


	DirectX::SimpleMath::Matrix GetLightView()const { return m_LightView; };
	DirectX::SimpleMath::Matrix GetMoveLightView() const { return m_MoveLightView; };
	DirectX::SimpleMath::Matrix GetLightProj(int index);
	float GetLightDistance(int index);

	DirectX::SimpleMath::Vector3 GetLightDir()const { return m_lightDir; };

	DX::RenderTexture* GetRenderTexture(int index);
	//用（デプスステンシ
	Imase::DepthStencil* GetDepthStencil(int index);
	DX::RenderTexture* GetMoveRenderTexture(int index);
	//用（デプスステンシ
	Imase::DepthStencil* GetMoveDepthStencil(int index);

	// デバイスに依存するリソースを作成する関数
	void CreateDeviceDependentResources();



private:
	std::vector<std::unique_ptr<CascadeShadowMap>> m_cascadeShadowMap;
	DirectX::SimpleMath::Vector3 m_lightDir;
	DirectX::SimpleMath::Quaternion m_lightRotate;

	float m_maxCascadeShadowDistance;
	DirectX::SimpleMath::Quaternion Rotate(float x, float y, float z);

	// ライトの位置
	DirectX::SimpleMath::Matrix m_LightView;

	// ライトの位置
	DirectX::SimpleMath::Matrix m_MoveLightView;


};


