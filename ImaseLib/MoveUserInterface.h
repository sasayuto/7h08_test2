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

#include"UserInterface.h"
namespace tito
{
	class MoveUserInterface
	{
	public:
		//データ受け渡し用コンスタントバッファ(送信側)
		struct ConstBuffer
		{
			DirectX::SimpleMath::Vector4	windowSize;
		};
//変数
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

		DX::StepTimer                           m_timer;
		// 入力レイアウト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

		// プリミティブバッチ
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
		//コモンステート
		std::unique_ptr<DirectX::CommonStates> m_states;
		// テクスチャハンドル
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		Microsoft::WRL::ComPtr<ID3D11Resource> m_res;
		// 頂点シェーダ
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
		// ピクセルシェーダ
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
		// ジオメトリシェーダ
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

		int m_windowWidth , m_windowHeight;
		int m_textureWidth, m_textureHeight;

		DirectX::SimpleMath::Vector2 m_scale;
		DirectX::SimpleMath::Vector2 m_baseScale;
		DirectX::SimpleMath::Vector2 m_position;

		ANCHOR m_anchor;
		POSITION_ANCHOR m_positionAnchor;
		float m_remderRatio;
		float m_transparency;
//関数
	public:
		static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

		MoveUserInterface();
		~MoveUserInterface();

		void LoadTexture(const wchar_t* path);
		
		void Create(const wchar_t* path
			, DirectX::SimpleMath::Vector2 position
			,DirectX::SimpleMath::Vector2 scale
			,ANCHOR anchor
			,POSITION_ANCHOR positionAnchor
		);

		void Render();

		void SetScale(DirectX::SimpleMath::Vector2 scale);
		DirectX::SimpleMath::Vector2 GetScale() { return m_scale; }
		DirectX::SimpleMath::Vector2 GetBaseScale() { return m_baseScale; }
		void SetPosition(DirectX::SimpleMath::Vector2 position);
		DirectX::SimpleMath::Vector2 GetPosition() { return m_position;}
		void SetAnchor(tito::ANCHOR anchor);
		tito::ANCHOR GetAnchor() { return m_anchor; }

		void SetRemderRatio(float ratio) { m_remderRatio = ratio; }
		float GetRemderRatio() { return m_remderRatio; }

		void SetTransparency(float transparency) { m_transparency = transparency; }
		float GetTransparency() { return m_transparency; }
		float GetBrightness() { return m_brightness; };
		void SetBrightness(float brightness) { m_brightness = brightness; };

		//修正位置
		DirectX::SimpleMath::Vector2 TexPositionCalculation();

		//修正画像サイズ
		DirectX::SimpleMath::Vector2 TexSizeCalculation();


	private:

		float m_brightness;
		void CreateShader();
		DirectX::DX11::VertexPositionColorTexture m_vertex;

	};
}