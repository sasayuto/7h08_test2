//--------------------------------------------------------------------------------------
// File: Particle.h
//
// �p�[�e�B�N���N���X
// ���g���̏ꍇ��Position���̂�
//
//-------------------------------------------------------------------------------------

#pragma once

#include "StepTimer.h"
#include <DeviceResources.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <list>
#include "ParticleUtility.h"

class Particle
{
public:
	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Brightness;
		DirectX::SimpleMath::Vector4	EyePosition;
	};

	//�r���{�[�h�������Ƃ��ɓn���iDraw�Ƀr���{�[�h�̏�������j
	DirectX::SimpleMath::Matrix& GetBillboard() { return m_billboard; }

	void SetEmissiveColor(const DirectX::SimpleMath::Vector3& emissiveColor) { m_emissiveColor = emissiveColor; }
	DirectX::SimpleMath::Vector3 GetEmissiveColor() const { return m_emissiveColor; }

	void SetBrightness(const float& brightness) { m_brightness = brightness; }
	float GetBrightness() const { return m_brightness; }

	//�ϐ�
private:

	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	// �e�N�X�`���n���h��
	std::vector<ID3D11ShaderResourceView*> m_texture;
	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	DirectX::SimpleMath::Matrix m_billboard;

	std::vector<DirectX::VertexPositionColorTexture> m_vertices;
	std::list<ParticleUtility> m_particleUtility;

	float m_brightness;
	DirectX::SimpleMath::Vector3 m_emissiveColor;
	//�֐�
public:
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	Particle();
	~Particle();

	void LoadTexture(ID3D11ShaderResourceView* texture);

	void Create(ID3D11ShaderResourceView* Texture);

	void Update(float elapsedTim);

	void RotateUpdate();

	void Add(ParticleUtility* particleUtility);

	void Render();
private:

	void CreateShader();
};
