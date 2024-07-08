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

#include"ImaseLib/UserInterface.h"
class OperationTaskUI
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

	int m_windowWidth, m_windowHeight;
	int m_textureWidth, m_textureHeight;

	DirectX::SimpleMath::Vector2 m_position;

	tito::ANCHOR m_anchor;
	tito::POSITION_ANCHOR m_positionAnchor;
	float m_remderRatio;
	float m_transparency;
	float m_green;

	//描画スタート時間
	float m_timer;

	//透明度
	bool m_taskSuccessFlag;

	//関数
public:
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	OperationTaskUI();
	~OperationTaskUI();

	void LoadTexture(const wchar_t* path);

	void Create(
		DirectX::SimpleMath::Vector2 position
		, tito::ANCHOR anchor
		, tito::POSITION_ANCHOR positionAnchor
	);

	void Render();

	/// <summary>
	/// 更新する
	/// </summary>
	void Update(const float& elapsedTime);

	/// <summary>
	/// 更新する
	/// </summary>
	void ReduceTransparency(const float& elapsedTime);
	void SetPosition(DirectX::SimpleMath::Vector2 position);
	DirectX::SimpleMath::Vector2 GetPosition() { return m_position; }
	void SetAnchor(tito::ANCHOR anchor);
	tito::ANCHOR GetAnchor() { return m_anchor; }

	void SetRemderRatio(float ratio) { m_remderRatio = ratio; }
	float GetRemderRatio() { return m_remderRatio; }

	void SetGreen(float green) { m_green = green; }
	float GetGreen() { return m_green; }
	void SetTaskSuccessFlag(const bool& taskSuccessFlag) { m_taskSuccessFlag = taskSuccessFlag; }

	void SetTransparency(float transparency) { m_transparency = transparency; }
	float GetTransparency() { return m_transparency; }
private:

	void CreateShader();
	DirectX::DX11::VertexPositionColorTexture m_vertex;

};