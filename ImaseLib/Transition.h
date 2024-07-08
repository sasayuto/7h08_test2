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
namespace tito
{
	class Transition
	{
	public:
//�ϐ�
	private:
		// ���̓��C�A�E�g
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

		// �v���~�e�B�u�o�b�`
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
		//�R�����X�e�[�g
		std::unique_ptr<DirectX::CommonStates> m_states;
		// ���_�V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
		// �s�N�Z���V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
		// �W�I���g���V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

		float m_remderRatio;

//�֐�
	public:
		static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

		Transition();
		~Transition();

		void Create();

		void Render();

		void SetRemderRatio(float ratio) {	m_remderRatio = ratio;}

		float GetRemderRatio() { return m_remderRatio; }
	private:

		void CreateShader();
	};
}