//--------------------------------------------------------------------------------------
// File: Particle.h
//
// パーティクルクラス
// 未拡張の場合はPosition情報のみ
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
	//データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Brightness;
		DirectX::SimpleMath::Vector4	EyePosition;
	};

	//ビルボードしたいときに渡す（Drawにビルボードの処理あり）
	DirectX::SimpleMath::Matrix& GetBillboard() { return m_billboard; }

	void SetEmissiveColor(const DirectX::SimpleMath::Vector3& emissiveColor) { m_emissiveColor = emissiveColor; }
	DirectX::SimpleMath::Vector3 GetEmissiveColor() const { return m_emissiveColor; }

	void SetBrightness(const float& brightness) { m_brightness = brightness; }
	float GetBrightness() const { return m_brightness; }

	//変数
private:

	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
	// テクスチャハンドル
	std::vector<ID3D11ShaderResourceView*> m_texture;
	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	DirectX::SimpleMath::Matrix m_billboard;

	std::vector<DirectX::VertexPositionColorTexture> m_vertices;
	std::list<ParticleUtility> m_particleUtility;

	float m_brightness;
	DirectX::SimpleMath::Vector3 m_emissiveColor;
	//関数
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
