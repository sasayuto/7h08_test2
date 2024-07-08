#pragma once

#include"ImaseLib/DepthStencil.h"
#include"ImaseLib/RenderTexture.h"
#include"Scene/GameObjects/PlayScene/ShadowMap/CascadeShadowMapManager.h"
class Sun;
/// <summary>
/// Drawクラスを定義する
/// </summary>
class Draw
{
public:
	//ビュー行列のセッター
	void SetView(const DirectX::SimpleMath::Matrix& view) { m_view = view; }
	DirectX::SimpleMath::Matrix GetView() { return m_view; }

	//カメラの視点の位置のセッター
	void SetCameraPosition(const DirectX::SimpleMath::Vector3& cameraPosition) { m_cameraPosition = cameraPosition; };

	//カメラの視点の位置のセッター
	void SetCameraDir(const DirectX::SimpleMath::Vector3& cameraDir) { m_cameraDir = cameraDir; };

	//カメラの注視点の位置のセッター
	void SetCameraTarget(const DirectX::SimpleMath::Vector3& cameraTarget) { m_cameraTarget = cameraTarget; };
	DirectX::SimpleMath::Vector3 GetEyePosition()const { return m_cameraPosition; }

	const static float FOG_LENGTH;
	static const int CASCADE_LIGHT_MAX_NUM ;

	void SetFogFar(const float& FogFar) { m_FogFar = FogFar; }
	void SetFogNear(const float& FogNear) { m_FogNear = FogNear; }

	float GetFogFar() const { return m_FogFar; }
	float GetFogNear() const { return m_FogNear; }
		//カメラのUpのセッター
	void SetCameraUp(const DirectX::SimpleMath::Vector3& cameraUp) { m_cameraUp = cameraUp; };

	//カメラのUpのセッター
	void SetSun(Sun* sun) { m_sun = sun; };

	static const float SHADOW_UPDATE_SECONDS;
	/// <summary>
	/// スクリーン画面のセッター
	/// </summary>
	/// <param name="width">縦</param>
	/// <param name="height">横</param>
	void SetWindowSize(const int& width, const int& height) { m_width = width; m_height = height; }

public:
	/// <summary>
	/// 描画クラスのインスタンスを取得する
	/// </summary>
	/// <returns>描画クラスのポインタ</returns>
	static Draw* GetInstance();

	/// <summary>
	/// //コンストラクタ
	/// </summary>
	Draw();

	/// <summary>
	/// //初期化する
	/// </summary>
	void Initialize();

	/// <summary>
	/// //初期化する
	/// </summary>
	void Update(float elapsedTime);

	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="model">モデルの種類</param>
	/// <param name="world">ワールド行列</param>
	/// <param name="drawingDistance">描画距離</param>
	void Render(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	);


//
//	/// <summary>
//	/// 描画する
//	/// </summary>
//	/// <param name="model">モデルの種類</param>
//	/// <param name="world">ワールド行列</param>
//	void RenderDisutance(
//		DirectX::Model* model,
//		const DirectX::SimpleMath::Matrix& world
//	);
//	/// <summary>
//	/// 描画する
//	/// </summary>
//	/// <param name="model">モデルの種類</param>
//	/// <param name="world">ワールド行列</param>
//	void RenderDisutancesss(
//		DirectX::Model* model,
//		const DirectX::SimpleMath::Matrix& world
//	);
//	/// <summary>
///// モデルの影を描画
///// </summary>
///// <param name="model">影にしたいモデル</param>
///// <param name="position">位置</param>
///// <param name="rotate">回転</param>
//	void ShadowDrawWeightSavingDistance(
//		DirectX::Model* model,
//		const DirectX::SimpleMath::Vector3& position,
//		const DirectX::SimpleMath::Quaternion& rotate,
//		const bool& DrawAll = false
//	);

		/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="model">モデルの種類</param>
	/// <param name="world">ワールド行列</param>
	/// <param name="drawingDistance">描画距離</param>
	void ShadowMapRender(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world,
		std::function<void()> additionalProcessing = nullptr
	);
	void ShadowMapRender(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world,
		ID3D11ShaderResourceView* normalMapTex,
		std::function<void()> additionalProcessing = nullptr
	);

	void ShadowMapRenderNoPicture(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world,
		std::function<void()> additionalProcessing = nullptr
	);

	void DynamicShadowMapTexCreateStart(int index, float timer);
	void StaticShadowMapTexCreateStart(int index, float timer);
	DirectX::SimpleMath::Vector3 m_cascadeTatgetPos;

	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="model">モデルの種類</param>
	/// <param name="world">ワールド行列</param>
	/// <param name="drawingDistance">描画距離</param>
	void ShadowMapTexCreate(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	);

	void ShadowMapTexCreateNoPicture(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	);

	void ShadowMapTexCreateNoPictureLight(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	);

	void ShadowMapTexCreateEnd();
	void ShadowMapTexCreateEndCon();

	void DrawEndUpdate();


	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="model">モデルの種類</param>
	/// <param name="world">ワールド行列</param>
	void Rendersss(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	);

	/// <summary>
	/// ライトが逆のモデルがあったため仮でライトを逆にして描画
	/// </summary>
	/// <param name="model">モデルの種類</param>
	/// <param name="world">ワールド行列</param>
	void kari(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	);

	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="model">モデルの種類</param>
	/// <param name="world">ワールド行列</param>
	void LightRender(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	);

	/// <summary>
	/// メッシュ描画する
	/// </summary>
	/// <param name="model">モデルの種類</param>
	/// <param name="world">ワールド行列</param>
	void MeshRender(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	);


	/// <summary>
	/// モデルの影を描画
	/// </summary>
	/// <param name="model">影にしたいモデル</param>
	/// <param name="position">位置</param>
	/// <param name="rotate">回転</param>
	void ShadowMapDraw(
		DirectX::Model* model,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate
	);

	/// <summary>
	/// 当たり判定のテストモデルCube
	/// </summary>
	/// <param name="size">モデルのサイズ</param>
	/// <param name="position">モデルのサイズ位置</param>
	/// <param name="rotate">モデルの回転</param>
	void TestCubeModel(
		const DirectX::SimpleMath::Vector3& size,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate = DirectX::SimpleMath::Quaternion::Identity
	);

	/// <summary>
	/// 当たり判定のテストモデル
	/// </summary>
	/// <param name="size">モデルのサイズ</param>
	/// <param name="position">モデルのサイズ位置</param>
	/// <param name="rotate">モデルの回転</param>
	void TestSphereModel(
		const float& radian,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate = DirectX::SimpleMath::Quaternion::Identity
	);

	/// <summary>
	/// 描画するか（小さいオブジェクトは視野外にでたときも描画しない）
	/// </summary>
	/// <param name="position">オブジェクトの位置</param>
	/// <param name="drawingDistance">描画距離</param>
	/// <returns>trueで描画しない</returns>
	bool VisibilityRange(
		const DirectX::SimpleMath::Vector3& position
	);
	/// <summary>
	/// 描画するか（小さいオブジェクトは視野外にでたときも描画しない）
	/// </summary>
	/// <param name="position">オブジェクトの位置</param>
	/// <param name="ModelExtents">カメラを後ろに下げる距離（モデルの半径）</param>
	/// <returns>trueで描画しない</returns>
	bool VisibilityRange(
		const DirectX::SimpleMath::Vector3& position,
		const float& ModelExtents
	);

	/// <summary>
	/// 描画するか（大きいオブジェクトは視野外でも描画）
	/// </summary>
	/// <param name="position">オブジェクトの位置</param>
	/// <returns>trueで描画しない</returns>
	bool DistanceRange(
		const DirectX::SimpleMath::Vector3& position
	);

	/// <summary>
	/// 更新を行う距離
	/// </summary>
	/// <param name="position">オブジェクトの位置</param>
	/// <param name="drawingDistance">描画距離</param>
	/// <returns>trueで描画しない</returns>
	bool UpdateDistance(
		const DirectX::SimpleMath::Vector3& position,
		const float& updateDistance = 0.0f
	);

	/// <summary>
	/// 更新を行う距離
	/// </summary>
	/// <param name="position">オブジェクトの位置</param>
	/// <param name="drawingDistance">描画距離</param>
	/// <returns>trueで描画しない</returns>
	bool DespawnDistance(
		const DirectX::SimpleMath::Vector3& position,
		const float& despawnDistance
	);

	/// <summary>
	/// カメラの距離による描画順の設定（listで使える）
	/// </summary>
	/// <param name="position_1"></param>
	/// <param name="position_2"></param>
	/// <returns></returns>
	bool CameraDistanceSort(
		const DirectX::SimpleMath::Vector3& position_1,
		const DirectX::SimpleMath::Vector3& position_2
	);

	/// <summary>
	/// ビルボードの処理
	/// </summary>
	/// <param name="billboard"></param>
	void CreateBillboard(DirectX::SimpleMath::Matrix& billboard);

private:
	// 描画のインスタンスへのポインタ
	static std::unique_ptr<Draw> m_draw;

	//コンテキストのポインタ
	ID3D11DeviceContext1* m_pContext;

	//デバイスのポインタ
	ID3D11Device1* m_pDevice;

	//スクリーン画面サイズ
	int m_height, m_width;

	//射影行列
	DirectX::SimpleMath::Matrix* m_proj;

	Sun* m_sun;

	//ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// 共通ステートオブジェクトのポインタ
	DirectX::CommonStates* m_commonStates;

	//カメラの視点の位置
	DirectX::SimpleMath::Vector3 m_cameraPosition;

	//カメラの方向の位置
	DirectX::SimpleMath::Vector3 m_cameraDir;

	//カメラの注視点の位置
	DirectX::SimpleMath::Vector3 m_cameraTarget;

	//カメラのUpの位置
	DirectX::SimpleMath::Vector3 m_cameraUp;
private:

	// ピクセルシェーダー（トーラス用）
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_Torus;

	// ピクセルシェーダー（トーラス用）
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_Shadow;

private:
	// 定数バッファの構造体
	struct ConstantBuffer
	{
		float att0;		// 一定減衰係数
		float att1;		// 線形減衰係数
		float att2;		// 次減衰係数
		DirectX::XMVECTOR SpotLight;	// ライトの位置
		DirectX::XMVECTOR lightPosition;	// ライトの位置
		DirectX::XMVECTOR LightAmbient;	// ライトの位置
		DirectX::XMVECTOR EyePosition;	// ライトの位置
		float FogNear;			// ライトの位置
		float FogFar;	// ライトの位置
	};

	float m_staticCascadeUpdateDistance;
	float m_keepStaticCascadeUpdateDistance;
	//霧の開始位置
	float m_FogNear;
	float m_FogFar;
	// 減衰係数
	float m_att[3];
	std::unique_ptr<CascadeShadowMapManager> m_cascadeShadowMapManager;

	int m_cascadeIndex;
	// 定数バッファへのポインタ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	//描画距離
	float m_drawDistance;

		private:
			// 頂点シェーダー
			Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VS_Depth;

			// ピクセルシェーダー
			Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_Depth;

			// 頂点シェーダー
			Microsoft::WRL::ComPtr<ID3D11VertexShader> m_NoPicture_VS_Depth;

			// ピクセルシェーダー
			Microsoft::WRL::ComPtr<ID3D11PixelShader> m_NoPicture_PS_Depth;

			// 頂点シェーダー
			Microsoft::WRL::ComPtr<ID3D11VertexShader> m_NoPictureVS;

			// ピクセルシェーダー
			Microsoft::WRL::ComPtr<ID3D11PixelShader> m_NoPicturePS;

			// 頂点シェーダー
			Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VS;

			// ピクセルシェーダー
			Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS;

			// 頂点シェーダー
			Microsoft::WRL::ComPtr<ID3D11VertexShader> m_NoormalVS;

			// ピクセルシェーダー
			Microsoft::WRL::ComPtr<ID3D11PixelShader> m_NoormalPS;

			// ジオメトリシェーダ
			Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GS;

private:

	// 定数バッファの構造体
	struct ConstantBuffer2
	{
		DirectX::XMMATRIX lightViewProj[4];	// ライトの投影空間へ座標変換する行列
		DirectX::XMMATRIX MovelightViewProj[4];	// ライトの投影空間へ座標変換する行列
		DirectX::XMVECTOR lightDistance[4];	// ライトの位置
		DirectX::XMVECTOR StaticTargetPosition;	// ライトの位置
		DirectX::XMVECTOR DynamicTargetPosition;	// ライトの位置
		DirectX::XMVECTOR lightDir;	// ライトの位置
		DirectX::XMVECTOR lightAmbient;		// ライトの環境光
		float FogNear;			// ライトの位置
		float FogFar;	// ライトの位置
	};

	// 定数バッファへのポインタ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer2;

	// サンプラー
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;

	// サンプラー
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_NormalMapSampler;

	DX::DeviceResources* m_deviceResources;

	//時間
	float m_timer;
public:

	void SetDrawDistance(const float& drawDistance) { m_drawDistance = drawDistance; }
};


