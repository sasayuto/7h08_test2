#pragma once

#include "ImaseLib/SceneManager.h"
#include "UserResources.h"
#include "ImaseLib/DebugCamera.h"
#include "ImaseLib/DepthStencil.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include <DirectXCollision.h>
#include"Scene/AdjustmentArrow.h"


enum class SelectProject
{
	EDIT,
	FILE,
	COUNT
};
class ModelSampleScene : public Imase::Scene<UserResources>
{
public:
	// コンストラクタ
	ModelSampleScene();

	// 初期化
	void Initialize() override;

	// 更新
	void Update(float elapsedTime) override;

	// 更新
	void EditUpdate(float elapsedTime);

	// 更新
	void FileSaveUpdate(float elapsedTime);

	// 描画
	void Render() override;

	// 終了処理
	void Finalize() override;

	// デバイスに依存するリソースを作成する関数
	void CreateDeviceDependentResources() override;

	// ウインドウサイズに依存するリソースを作成する関数
	void CreateWindowSizeDependentResources() override;

	// デバイスロストした時に呼び出される関数
	void OnDeviceLost() override;

	int GetSpotLightNum()const { return m_spotLightNum; }
	void SetSpotLightNum(int spotLightNum) { m_spotLightNum = spotLightNum; }

/// <summary>
/// 保存
/// </summary>
private:

	SelectProject m_selectProject;

private:

	// デバッグカメラへのポインタ
	std::unique_ptr<Imase::DebugCamera> m_debugCamera;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// 射影行列
	DirectX::SimpleMath::Matrix m_proj;
	DirectX::SimpleMath::Quaternion Rotate(float x, float y, float z);
private:

	// 床モデルへのポインタ
	std::unique_ptr<DirectX::Model> m_floorModel;

private:

	// トーラスのモデル
	std::unique_ptr<DirectX::Model> m_torusModel;

	std::unique_ptr<DirectX::Model> m_torusMel;

private:
private:
	DirectX::SimpleMath::Vector3 m_keepExtents;
	DirectX::SimpleMath::Quaternion m_keepRotate;
	void CollJson();

	std::unique_ptr<Collider::Box2D> m_uiCol[10];
	DirectX::SimpleMath::Color m_uiColor[10];
	float m_eyeToObjectDistance;
	// ライトの回転

private:
	// 減衰係数デバッグ表示のカーソル位置
	int m_cursor;

	int m_spotLightNum;
	int SPOT_LIGHT_MAX_NUM = 1;

	float m_AdditionPercentageLeft;
	float m_AdditionPercentageRight;
	float m_apTimerLeft;
	float m_apTimerRight;
	// スポットライトのモデルへのポインタ
	std::unique_ptr<DirectX::Model> m_spotLightModel;

	DirectX::SimpleMath::Vector3 RaycastFromMousePosition(const DirectX::SimpleMath::Vector2& mousePosition, const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix);
	DirectX::SimpleMath::Vector3 m_mouseRayDir;
	DirectX::SimpleMath::Quaternion m_mouseRayDirRotate;

	DirectX::SimpleMath::Vector3 m_RayPostion;
	float m_rayLength;
	DirectX::SimpleMath::Vector3 m_RayExtents;
	std::unique_ptr<AdjustmentArrow> m_AdjustmentArrow;
	int m_MouseSelectNum;
	std::vector<std::unique_ptr<DirectX::BoundingOrientedBox>> m_CubeCol;
	struct CopyColliderDate
	{
		DirectX::SimpleMath::Vector3 Position;
		DirectX::SimpleMath::Vector3 Extents =DirectX::SimpleMath::Vector3::One;
		DirectX::SimpleMath::Quaternion Rotate;
		bool CopyFlag=false;
	};
	//コピーコライダーデータ
	CopyColliderDate m_copyColliderDate;

	//ファイル名前
	std::wstring m_ModelName;
	std::wstring m_JsonColName;
	//ファイル名前
	std::string m_JsonName;
	int m_ModelNum;

	void SaveGunData();

	// 横回転
	float m_yAngle, m_yTmp;

	// 縦回転
	float m_xAngle, m_xTmp;

	// ドラッグされた座標
	DirectX::SimpleMath::Vector3 m_keeppos;
	int m_x, m_y;

	float m_sx, m_sy;


	void UIUpdate();
};


