//--------------------------------------------------------------------------------------
// File: UserInterface.h
//
// ユーザーインターフェースクラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "NumberManager.h"
#include"Scene/GameObjects/Models/Textures.h"

#include "ImaseLib/BinaryFile.h"


using namespace DirectX;

/// <summary>
/// インプットレイアウト
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> tito::NumberManager::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(SimpleMath::Vector3)+ sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// コンストラクタ
/// </summary>
tito::NumberManager::NumberManager()
	:m_windowHeight(0)
	,m_windowWidth(0)
	,m_texture(nullptr)
	,m_res(nullptr)
	,m_position(SimpleMath::Vector2::Zero)
	,m_anchor(ANCHOR::TOP_LEFT),
	m_transparency(1),
	m_number()
{

}

/// <summary>
/// デストラクタ
/// </summary>
tito::NumberManager::~NumberManager()
{
}

/// <summary>
/// 生成関数
/// </summary>
/// <param name="pDR">ユーザーリソース等から持ってくる</param>
void tito::NumberManager::Create(
	DirectX::SimpleMath::Vector2 position
	,DirectX::SimpleMath::Vector2 scale
	, const int& number
	, ANCHOR anchor
)
{
	auto device = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	m_scale = scale;
	m_number = number;
	m_position = position;
	m_anchor = anchor;

	//シェーダーの作成
	CreateShader();

	//画像の読み込み
	DirectX::CreateWICTextureFromFile(device, L"Resources/Textures/Number_01.png", m_res.ReleaseAndGetAddressOf(), m_texture.ReleaseAndGetAddressOf());

	// プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);

	m_states = std::make_unique<CommonStates>(device);

	//ウィンドウサイズを取得（シェーダーは比率なのでフルスクリーンの対応ウィンドウサイズ）
	m_windowHeight = Textures::GetInstance()->GetFullScreenNoneWindowHeight();
	m_windowWidth = Textures::GetInstance()->GetFullScreenNoneWindowWidth();
}

/// <summary>
/// Shader作成部分だけ分離した関数
/// </summary>
void tito::NumberManager::CreateShader()
{
	auto device = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/NumberVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/NumberGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/NumberPS.cso");

	//インプットレイアウトの作成
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	// 頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	// ジオメトリシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}

	// ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	//シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);
}




/// <summary>
/// 描画関数
/// </summary>
void tito::NumberManager::Render()
{
	auto context = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

		// 頂点情報
		// Position.xy	:拡縮用スケール
		// Position.z	:アンカータイプ(0～8)の整数で指定
		// Color.xy　	:アンカー座標(ピクセル指定:1280 ×720)
		// Color.zw		:画像サイズ
		// Tex.xy		:ウィンドウサイズ（バッファも同じ。こちらは未使用）
	VertexPositionColorTexture vertex[1] = {
		VertexPositionColorTexture(SimpleMath::Vector3(m_scale.x,m_scale.y, static_cast<float>(m_anchor))
		, SimpleMath::Vector4(m_position.x, m_position.y,0,0)
		, SimpleMath::Vector2(static_cast<float>(m_number),m_transparency))
	};

	//シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.windowSize = SimpleMath::Vector4(static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight), 0, 0);
	//受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	// 深度バッファに書き込み参照する
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// カリングは左周り
	context->RSSetState(m_states->CullNone());

	//シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	//インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	// 板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch->End();

	//シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}
