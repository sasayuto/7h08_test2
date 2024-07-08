#pragma once

class Sun;
/// <summary>
/// Texturesクラスを定義する
/// </summary>
class Textures
{
public:
	//デバイスのセッター、ゲッター
	Sun* GetSun() { return m_pSun; }
	void SetSun(Sun* sun) { m_pSun = sun; }

	//ウィンドウサイズのセッター、ゲッター
	int GetWindowWidth() const { return m_windowWidth; }
	int GetWindowHeight() const { return m_windowHeight; }

	//ウィンドウサイズのセッター、ゲッター
	int GetFullScreenNoneWindowWidth() const { return m_fullScreenNoneWindowWidth; }
	int GetFullScreenNoneWindowHeight() const { return m_fullScreenNoneWindowHeight; }

	void SetWindowSize(const int& windowWidth, const int& windowHeight) { m_windowHeight = windowHeight; m_windowWidth = windowWidth; }
	void SetFullScreenNoneWindowSize(const int& windowWidth, const int& windowHeight) { m_fullScreenNoneWindowHeight = windowHeight; m_fullScreenNoneWindowWidth = windowWidth; }

public:

	//テクスチャーのリソース取得
	ID3D11ShaderResourceView* GetSmoke() { return m_smoke.Get(); };
	ID3D11ShaderResourceView* GetHouse_01NormalMap() { return m_House_01NormalMap.Get(); };
	ID3D11ShaderResourceView* GetNoNormalMap() { return m_NoNormalMap.Get(); };
	ID3D11ShaderResourceView* GetCoinlight() { return m_Coinlight.Get(); };
	ID3D11ShaderResourceView* GetPillarTexture_01NormalMap() { return m_PillarTexture_01NormalMap.Get(); };

public:
	/// <summary>
	/// 描画クラスのインスタンスを取得する
	/// </summary>
	/// <returns>描画クラスのインスタンス</returns>
	static Textures*  GetInstance();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Textures();

	void LoadResource();

private:
	// 描画のインスタンスへのポインタ
	static std::unique_ptr<Textures> m_textures;

	//カメラのポインタ
	int m_windowHeight, m_windowWidth;

	//フルスクリーンじゃないときのウィンドウサイズ(シェーダーでは比率なので大きさが変わってしまうから)
	int m_fullScreenNoneWindowHeight, m_fullScreenNoneWindowWidth;

	//コンテキストのポインタ
	ID3D11DeviceContext1* m_pContext;

	//デバイスのポインタ
	ID3D11Device1* m_pDevice;

	Sun* m_pSun;
	//プロジェクション行列
	DirectX::SimpleMath::Matrix m_proj;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Coinlight;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_smoke;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_House_01NormalMap;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_NoNormalMap;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_PillarTexture_01NormalMap;
};


