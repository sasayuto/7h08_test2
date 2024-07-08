#pragma once

#include"ImaseLib/DepthStencil.h"
#include"ImaseLib/RenderTexture.h"
#include"Scene/GameObjects/PlayScene/ShadowMap/CascadeShadowMapManager.h"
class Sun;
/// <summary>
/// Draw�N���X���`����
/// </summary>
class Draw
{
public:
	//�r���[�s��̃Z�b�^�[
	void SetView(const DirectX::SimpleMath::Matrix& view) { m_view = view; }
	DirectX::SimpleMath::Matrix GetView() { return m_view; }

	//�J�����̎��_�̈ʒu�̃Z�b�^�[
	void SetCameraPosition(const DirectX::SimpleMath::Vector3& cameraPosition) { m_cameraPosition = cameraPosition; };

	//�J�����̎��_�̈ʒu�̃Z�b�^�[
	void SetCameraDir(const DirectX::SimpleMath::Vector3& cameraDir) { m_cameraDir = cameraDir; };

	//�J�����̒����_�̈ʒu�̃Z�b�^�[
	void SetCameraTarget(const DirectX::SimpleMath::Vector3& cameraTarget) { m_cameraTarget = cameraTarget; };
	DirectX::SimpleMath::Vector3 GetEyePosition()const { return m_cameraPosition; }

	const static float FOG_LENGTH;
	static const int CASCADE_LIGHT_MAX_NUM ;

	void SetFogFar(const float& FogFar) { m_FogFar = FogFar; }
	void SetFogNear(const float& FogNear) { m_FogNear = FogNear; }

	float GetFogFar() const { return m_FogFar; }
	float GetFogNear() const { return m_FogNear; }
		//�J������Up�̃Z�b�^�[
	void SetCameraUp(const DirectX::SimpleMath::Vector3& cameraUp) { m_cameraUp = cameraUp; };

	//�J������Up�̃Z�b�^�[
	void SetSun(Sun* sun) { m_sun = sun; };

	static const float SHADOW_UPDATE_SECONDS;
	/// <summary>
	/// �X�N���[����ʂ̃Z�b�^�[
	/// </summary>
	/// <param name="width">�c</param>
	/// <param name="height">��</param>
	void SetWindowSize(const int& width, const int& height) { m_width = width; m_height = height; }

public:
	/// <summary>
	/// �`��N���X�̃C���X�^���X���擾����
	/// </summary>
	/// <returns>�`��N���X�̃|�C���^</returns>
	static Draw* GetInstance();

	/// <summary>
	/// //�R���X�g���N�^
	/// </summary>
	Draw();

	/// <summary>
	/// //����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// //����������
	/// </summary>
	void Update(float elapsedTime);

	/// <summary>
	/// �`�悷��
	/// </summary>
	/// <param name="model">���f���̎��</param>
	/// <param name="world">���[���h�s��</param>
	/// <param name="drawingDistance">�`�拗��</param>
	void Render(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	);


//
//	/// <summary>
//	/// �`�悷��
//	/// </summary>
//	/// <param name="model">���f���̎��</param>
//	/// <param name="world">���[���h�s��</param>
//	void RenderDisutance(
//		DirectX::Model* model,
//		const DirectX::SimpleMath::Matrix& world
//	);
//	/// <summary>
//	/// �`�悷��
//	/// </summary>
//	/// <param name="model">���f���̎��</param>
//	/// <param name="world">���[���h�s��</param>
//	void RenderDisutancesss(
//		DirectX::Model* model,
//		const DirectX::SimpleMath::Matrix& world
//	);
//	/// <summary>
///// ���f���̉e��`��
///// </summary>
///// <param name="model">�e�ɂ��������f��</param>
///// <param name="position">�ʒu</param>
///// <param name="rotate">��]</param>
//	void ShadowDrawWeightSavingDistance(
//		DirectX::Model* model,
//		const DirectX::SimpleMath::Vector3& position,
//		const DirectX::SimpleMath::Quaternion& rotate,
//		const bool& DrawAll = false
//	);

		/// <summary>
	/// �`�悷��
	/// </summary>
	/// <param name="model">���f���̎��</param>
	/// <param name="world">���[���h�s��</param>
	/// <param name="drawingDistance">�`�拗��</param>
	void ShadowMapRender(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world,
		std::function<void()> additionalProcessing = nullptr
	);
	void ShadowMapRender(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world,
		ID3D11ShaderResourceView* normalMapTex,
		std::function<void()> additionalProcessing = nullptr
	);

	void ShadowMapRenderNoPicture(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world,
		std::function<void()> additionalProcessing = nullptr
	);

	void DynamicShadowMapTexCreateStart(int index, float timer);
	void StaticShadowMapTexCreateStart(int index, float timer);
	DirectX::SimpleMath::Vector3 m_cascadeTatgetPos;

	/// <summary>
	/// �`�悷��
	/// </summary>
	/// <param name="model">���f���̎��</param>
	/// <param name="world">���[���h�s��</param>
	/// <param name="drawingDistance">�`�拗��</param>
	void ShadowMapTexCreate(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	);

	void ShadowMapTexCreateNoPicture(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	);

	void ShadowMapTexCreateNoPictureLight(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	);

	void ShadowMapTexCreateEnd();
	void ShadowMapTexCreateEndCon();

	void DrawEndUpdate();


	/// <summary>
	/// �`�悷��
	/// </summary>
	/// <param name="model">���f���̎��</param>
	/// <param name="world">���[���h�s��</param>
	void Rendersss(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	);

	/// <summary>
	/// ���C�g���t�̃��f�������������߉��Ń��C�g���t�ɂ��ĕ`��
	/// </summary>
	/// <param name="model">���f���̎��</param>
	/// <param name="world">���[���h�s��</param>
	void kari(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	);

	/// <summary>
	/// �`�悷��
	/// </summary>
	/// <param name="model">���f���̎��</param>
	/// <param name="world">���[���h�s��</param>
	void LightRender(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	);

	/// <summary>
	/// ���b�V���`�悷��
	/// </summary>
	/// <param name="model">���f���̎��</param>
	/// <param name="world">���[���h�s��</param>
	void MeshRender(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	);


	/// <summary>
	/// ���f���̉e��`��
	/// </summary>
	/// <param name="model">�e�ɂ��������f��</param>
	/// <param name="position">�ʒu</param>
	/// <param name="rotate">��]</param>
	void ShadowMapDraw(
		DirectX::Model* model,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate
	);

	/// <summary>
	/// �����蔻��̃e�X�g���f��Cube
	/// </summary>
	/// <param name="size">���f���̃T�C�Y</param>
	/// <param name="position">���f���̃T�C�Y�ʒu</param>
	/// <param name="rotate">���f���̉�]</param>
	void TestCubeModel(
		const DirectX::SimpleMath::Vector3& size,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate = DirectX::SimpleMath::Quaternion::Identity
	);

	/// <summary>
	/// �����蔻��̃e�X�g���f��
	/// </summary>
	/// <param name="size">���f���̃T�C�Y</param>
	/// <param name="position">���f���̃T�C�Y�ʒu</param>
	/// <param name="rotate">���f���̉�]</param>
	void TestSphereModel(
		const float& radian,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate = DirectX::SimpleMath::Quaternion::Identity
	);

	/// <summary>
	/// �`�悷�邩�i�������I�u�W�F�N�g�͎���O�ɂł��Ƃ����`�悵�Ȃ��j
	/// </summary>
	/// <param name="position">�I�u�W�F�N�g�̈ʒu</param>
	/// <param name="drawingDistance">�`�拗��</param>
	/// <returns>true�ŕ`�悵�Ȃ�</returns>
	bool VisibilityRange(
		const DirectX::SimpleMath::Vector3& position
	);
	/// <summary>
	/// �`�悷�邩�i�������I�u�W�F�N�g�͎���O�ɂł��Ƃ����`�悵�Ȃ��j
	/// </summary>
	/// <param name="position">�I�u�W�F�N�g�̈ʒu</param>
	/// <param name="ModelExtents">�J���������ɉ����鋗���i���f���̔��a�j</param>
	/// <returns>true�ŕ`�悵�Ȃ�</returns>
	bool VisibilityRange(
		const DirectX::SimpleMath::Vector3& position,
		const float& ModelExtents
	);

	/// <summary>
	/// �`�悷�邩�i�傫���I�u�W�F�N�g�͎���O�ł��`��j
	/// </summary>
	/// <param name="position">�I�u�W�F�N�g�̈ʒu</param>
	/// <returns>true�ŕ`�悵�Ȃ�</returns>
	bool DistanceRange(
		const DirectX::SimpleMath::Vector3& position
	);

	/// <summary>
	/// �X�V���s������
	/// </summary>
	/// <param name="position">�I�u�W�F�N�g�̈ʒu</param>
	/// <param name="drawingDistance">�`�拗��</param>
	/// <returns>true�ŕ`�悵�Ȃ�</returns>
	bool UpdateDistance(
		const DirectX::SimpleMath::Vector3& position,
		const float& updateDistance = 0.0f
	);

	/// <summary>
	/// �X�V���s������
	/// </summary>
	/// <param name="position">�I�u�W�F�N�g�̈ʒu</param>
	/// <param name="drawingDistance">�`�拗��</param>
	/// <returns>true�ŕ`�悵�Ȃ�</returns>
	bool DespawnDistance(
		const DirectX::SimpleMath::Vector3& position,
		const float& despawnDistance
	);

	/// <summary>
	/// �J�����̋����ɂ��`�揇�̐ݒ�ilist�Ŏg����j
	/// </summary>
	/// <param name="position_1"></param>
	/// <param name="position_2"></param>
	/// <returns></returns>
	bool CameraDistanceSort(
		const DirectX::SimpleMath::Vector3& position_1,
		const DirectX::SimpleMath::Vector3& position_2
	);

	/// <summary>
	/// �r���{�[�h�̏���
	/// </summary>
	/// <param name="billboard"></param>
	void CreateBillboard(DirectX::SimpleMath::Matrix& billboard);

private:
	// �`��̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<Draw> m_draw;

	//�R���e�L�X�g�̃|�C���^
	ID3D11DeviceContext1* m_pContext;

	//�f�o�C�X�̃|�C���^
	ID3D11Device1* m_pDevice;

	//�X�N���[����ʃT�C�Y
	int m_height, m_width;

	//�ˉe�s��
	DirectX::SimpleMath::Matrix* m_proj;

	Sun* m_sun;

	//�r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// ���ʃX�e�[�g�I�u�W�F�N�g�̃|�C���^
	DirectX::CommonStates* m_commonStates;

	//�J�����̎��_�̈ʒu
	DirectX::SimpleMath::Vector3 m_cameraPosition;

	//�J�����̕����̈ʒu
	DirectX::SimpleMath::Vector3 m_cameraDir;

	//�J�����̒����_�̈ʒu
	DirectX::SimpleMath::Vector3 m_cameraTarget;

	//�J������Up�̈ʒu
	DirectX::SimpleMath::Vector3 m_cameraUp;
private:

	// �s�N�Z���V�F�[�_�[�i�g�[���X�p�j
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_Torus;

	// �s�N�Z���V�F�[�_�[�i�g�[���X�p�j
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_Shadow;

private:
	// �萔�o�b�t�@�̍\����
	struct ConstantBuffer
	{
		float att0;		// ��茸���W��
		float att1;		// ���`�����W��
		float att2;		// �������W��
		DirectX::XMVECTOR SpotLight;	// ���C�g�̈ʒu
		DirectX::XMVECTOR lightPosition;	// ���C�g�̈ʒu
		DirectX::XMVECTOR LightAmbient;	// ���C�g�̈ʒu
		DirectX::XMVECTOR EyePosition;	// ���C�g�̈ʒu
		float FogNear;			// ���C�g�̈ʒu
		float FogFar;	// ���C�g�̈ʒu
	};

	float m_staticCascadeUpdateDistance;
	float m_keepStaticCascadeUpdateDistance;
	//���̊J�n�ʒu
	float m_FogNear;
	float m_FogFar;
	// �����W��
	float m_att[3];
	std::unique_ptr<CascadeShadowMapManager> m_cascadeShadowMapManager;

	int m_cascadeIndex;
	// �萔�o�b�t�@�ւ̃|�C���^
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	//�`�拗��
	float m_drawDistance;

		private:
			// ���_�V�F�[�_�[
			Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VS_Depth;

			// �s�N�Z���V�F�[�_�[
			Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_Depth;

			// ���_�V�F�[�_�[
			Microsoft::WRL::ComPtr<ID3D11VertexShader> m_NoPicture_VS_Depth;

			// �s�N�Z���V�F�[�_�[
			Microsoft::WRL::ComPtr<ID3D11PixelShader> m_NoPicture_PS_Depth;

			// ���_�V�F�[�_�[
			Microsoft::WRL::ComPtr<ID3D11VertexShader> m_NoPictureVS;

			// �s�N�Z���V�F�[�_�[
			Microsoft::WRL::ComPtr<ID3D11PixelShader> m_NoPicturePS;

			// ���_�V�F�[�_�[
			Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VS;

			// �s�N�Z���V�F�[�_�[
			Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS;

			// ���_�V�F�[�_�[
			Microsoft::WRL::ComPtr<ID3D11VertexShader> m_NoormalVS;

			// �s�N�Z���V�F�[�_�[
			Microsoft::WRL::ComPtr<ID3D11PixelShader> m_NoormalPS;

			// �W�I���g���V�F�[�_
			Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GS;

private:

	// �萔�o�b�t�@�̍\����
	struct ConstantBuffer2
	{
		DirectX::XMMATRIX lightViewProj[4];	// ���C�g�̓��e��Ԃ֍��W�ϊ�����s��
		DirectX::XMMATRIX MovelightViewProj[4];	// ���C�g�̓��e��Ԃ֍��W�ϊ�����s��
		DirectX::XMVECTOR lightDistance[4];	// ���C�g�̈ʒu
		DirectX::XMVECTOR StaticTargetPosition;	// ���C�g�̈ʒu
		DirectX::XMVECTOR DynamicTargetPosition;	// ���C�g�̈ʒu
		DirectX::XMVECTOR lightDir;	// ���C�g�̈ʒu
		DirectX::XMVECTOR lightAmbient;		// ���C�g�̊���
		float FogNear;			// ���C�g�̈ʒu
		float FogFar;	// ���C�g�̈ʒu
	};

	// �萔�o�b�t�@�ւ̃|�C���^
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer2;

	// �T���v���[
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;

	// �T���v���[
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_NormalMapSampler;

	DX::DeviceResources* m_deviceResources;

	//����
	float m_timer;
public:

	void SetDrawDistance(const float& drawDistance) { m_drawDistance = drawDistance; }
};


