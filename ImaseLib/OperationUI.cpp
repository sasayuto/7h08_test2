//--------------------------------------------------------------------------------------
// File: OperationUI.h
//
// ユーザーインターフェースクラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "OperationUI.h"
#include"Scene/GameObjects/Models/Textures.h"

#include "ImaseLib/BinaryFile.h"


using namespace DirectX;

/// <summary>
/// インプットレイアウト
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> tito::OperationUI::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(SimpleMath::Vector3)+ sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// コンストラクタ
/// </summary>
tito::OperationUI::OperationUI()
	:m_windowHeight(0)
	,m_windowWidth(0)
	,m_textureHeight(0)
	,m_textureWidth(0)
	,m_texture(nullptr)
	,m_res(nullptr)
	,m_position(SimpleMath::Vector2::Zero)
	,m_anchor(ANCHOR::TOP_LEFT)
	,m_remderRatio(1.0f),
	m_positionAnchor(),
	m_timer(0),
	m_transparency(0),
	m_brightness(1),
	m_brightnessFlag(true)
{

}

/// <summary>
/// デストラクタ
/// </summary>
tito::OperationUI::~OperationUI()
{
}

/// <summary>
/// テクスチャリソース読み込み関数
/// </summary>
/// <param name="path">相対パス(Resources/Textures/・・・.pngなど）</param>
void tito::OperationUI::LoadTexture(const wchar_t* path)
{
	auto device = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	DirectX::CreateWICTextureFromFile(device, path, m_res.ReleaseAndGetAddressOf(), m_texture.ReleaseAndGetAddressOf());
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(m_res.As(&tex));

	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;

}

/// <summary>
/// 生成関数
/// </summary>
/// <param name="pDR">ユーザーリソース等から持ってくる</param>
void tito::OperationUI::Create(const wchar_t* path
	, DirectX::SimpleMath::Vector2 position
	, ANCHOR anchor
	,POSITION_ANCHOR positionAnchor)
{
	auto device = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	m_position = position;
	m_anchor = anchor;
	m_positionAnchor = positionAnchor;
	//シェーダーの作成
	CreateShader();

	//画像の読み込み
	LoadTexture(path);

	// プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);

	m_states = std::make_unique<CommonStates>(device);
	
	//ウィンドウサイズを取得（シェーダーは比率なのでフルスクリーンの対応ウィンドウサイズ）
	m_windowHeight = Textures::GetInstance()->GetFullScreenNoneWindowHeight();
	m_windowWidth = Textures::GetInstance()->GetFullScreenNoneWindowWidth();

}


void tito::OperationUI::SetPosition(DirectX::SimpleMath::Vector2 position)
{
	m_position = position;
}
/// <summary>
/// Shader作成部分だけ分離した関数
/// </summary>
void tito::OperationUI::CreateShader()
{
	auto device = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/OperationUIVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/OperationUIGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/OperationUIPS.cso");

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
void tito::OperationUI::Render()
{
	auto context = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	// 頂点情報
	// Position.xy	:拡縮用スケール
	// Position.z	:アンカータイプ(0～8)の整数で指定
	// Color.xy　	:アンカー座標(ピクセル指定:1280 ×720)
	// Color.zw		:画像サイズ
	// Tex.xy		:ウィンドウサイズ（バッファも同じ。こちらは未使用）
	m_vertex = {
		VertexPositionColorTexture(SimpleMath::Vector3(m_position.x, -m_position.y, static_cast<float>(m_anchor))
		, SimpleMath::Vector4(m_brightness,m_transparency,0, static_cast<float>(m_positionAnchor))
		, SimpleMath::Vector2(static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight)))
	};

	//シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.windowSize = SimpleMath::Vector4(static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight), 1, 1);
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

	//半透明描画指定
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	// 透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

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
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertex, 1);
	m_batch->End();

	//シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

void tito::OperationUI::Update(const float& elapsedTime)
{
	if (m_brightness >= 1.0f) m_brightnessFlag = false;
	if (m_brightness <= 0.5f) m_brightnessFlag = true;

	if (m_brightnessFlag) m_brightness += elapsedTime/2;
	else                    m_brightness -= elapsedTime/2;

	if (m_transparency >= 1.0f)
		return;

	m_transparency += elapsedTime;
}

void tito::OperationUI::ReduceTransparency(const float& elapsedTime)
{
	if (m_transparency <= 0.0f)
		return;

	m_transparency -= elapsedTime;
}
