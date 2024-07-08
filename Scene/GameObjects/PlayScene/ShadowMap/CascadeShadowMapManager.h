#pragma once


#include"CascadeShadowMap.h"
class RenderTexture;
#include"ImaseLib/DepthStencil.h"
class CascadeShadowMapManager
{
public:
	// �V���h�E�}�b�v�̃T�C�Y
	static const int SHADOWMAP_SIZE;
	static const int CARE_EYE;
	//�ʒu
	static const DirectX::SimpleMath::Quaternion INITIAL_ROTATE;

	static const float SUNSET_TIME;
	static const float SUNSHINE_HOURS;

	// �R���X�g���N�^
	CascadeShadowMapManager();

	void Initialize(DX::DeviceResources* deviceResources, DirectX::SimpleMath::Vector3 targetPosition,const int cascadeNum,float maxCascadeShadowDistance);
	// ������	
	// �X�V
	void Update(float elapsedTime,float timer, DirectX::SimpleMath::Vector3 targetPosition);


	void Render();


	DirectX::SimpleMath::Matrix GetLightView()const { return m_LightView; };
	DirectX::SimpleMath::Matrix GetMoveLightView() const { return m_MoveLightView; };
	DirectX::SimpleMath::Matrix GetLightProj(int index);
	float GetLightDistance(int index);

	DirectX::SimpleMath::Vector3 GetLightDir()const { return m_lightDir; };

	DX::RenderTexture* GetRenderTexture(int index);
	//�p�i�f�v�X�X�e���V
	Imase::DepthStencil* GetDepthStencil(int index);
	DX::RenderTexture* GetMoveRenderTexture(int index);
	//�p�i�f�v�X�X�e���V
	Imase::DepthStencil* GetMoveDepthStencil(int index);

	// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateDeviceDependentResources();



private:
	std::vector<std::unique_ptr<CascadeShadowMap>> m_cascadeShadowMap;
	DirectX::SimpleMath::Vector3 m_lightDir;
	DirectX::SimpleMath::Quaternion m_lightRotate;

	float m_maxCascadeShadowDistance;
	DirectX::SimpleMath::Quaternion Rotate(float x, float y, float z);

	// ���C�g�̈ʒu
	DirectX::SimpleMath::Matrix m_LightView;

	// ���C�g�̈ʒu
	DirectX::SimpleMath::Matrix m_MoveLightView;


};


