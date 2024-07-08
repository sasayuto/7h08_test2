//--------------------------------------------------------------------------------------
// File: UserInterface.h
//
// ���[�U�[�C���^�[�t�F�[�X�N���X
//
//-------------------------------------------------------------------------------------

#pragma once

#include "StepTimer.h"
#include <DeviceResources.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <vector>

#include"UserInterface.h"
namespace tito
{
	class OperationUI
	{
	public:
		//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
		struct ConstBuffer
		{
			DirectX::SimpleMath::Vector4	windowSize;
		};
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
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		Microsoft::WRL::ComPtr<ID3D11Resource> m_res;
		// ���_�V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
		// �s�N�Z���V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
		// �W�I���g���V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

		int m_windowWidth , m_windowHeight;
		int m_textureWidth, m_textureHeight;

		DirectX::SimpleMath::Vector2 m_position;

		ANCHOR m_anchor;
		POSITION_ANCHOR m_positionAnchor;
		float m_remderRatio;
		float m_transparency; 
		float m_brightness;

		//�`��X�^�[�g����
		float m_timer;


		//�����x
		bool m_brightnessFlag;

//�֐�
	public:
		static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

		OperationUI();
		~OperationUI();

		void LoadTexture(const wchar_t* path);
		
		void Create(const wchar_t* path
			, DirectX::SimpleMath::Vector2 position
			,ANCHOR anchor
			,POSITION_ANCHOR positionAnchor
		);

		void Render();

		/// <summary>
		/// �X�V����
		/// </summary>
		void Update(const float& elapsedTime);

		/// <summary>
		/// �X�V����
		/// </summary>
		void ReduceTransparency(const float& elapsedTime);

		void SetPosition(DirectX::SimpleMath::Vector2 position);
		DirectX::SimpleMath::Vector2 GetPosition() { return m_position;}
		void SetAnchor(tito::ANCHOR anchor);
		tito::ANCHOR GetAnchor() { return m_anchor; }

		void SetRemderRatio(float ratio) { m_remderRatio = ratio; }
		float GetRemderRatio() { return m_remderRatio; }

		void SetBrightness(float brightness) { m_brightness = brightness; }
		float GetBrightness() { return m_brightness; }

		void SetTransparency(float transparency) { m_transparency = transparency; }
		float GetTransparency() { return m_transparency; }
	private:

		void CreateShader();
		DirectX::DX11::VertexPositionColorTexture m_vertex;

	};
}