//--------------------------------------------------------------------------------------
// File: UserInterface.h
//
// ユーザーインターフェースクラス
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
//変数
	private:
		// 入力レイアウト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

		// プリミティブバッチ
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
		//コモンステート
		std::unique_ptr<DirectX::CommonStates> m_states;
		// 頂点シェーダ
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
		// ピクセルシェーダ
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
		// ジオメトリシェーダ
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

		float m_remderRatio;

//関数
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