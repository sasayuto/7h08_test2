#pragma once

/// <summary>
/// タイトルカメラクラスを定義する
/// </summary>
class StageSelectCamera
{
public:
	// カメラのビュー行列の取得関数
	DirectX::SimpleMath::Matrix GetCameraMatrix() const { return m_view; };

	//カメラの位置の取得関数
	DirectX::SimpleMath::Vector3 GetEyePosition() const { return m_eye; }
	void SetEyePosition(const DirectX::SimpleMath::Vector3& eye) { m_eye = eye; }

	//カメラの注視点の取得関数
	DirectX::SimpleMath::Vector3 GetTargetPosition() const { return m_target; }
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& target) { m_target = target; }

	//カメラの注視点の取得関数
	DirectX::SimpleMath::Vector3 GetDir() const { return m_dir; }
	void SetDir(const DirectX::SimpleMath::Vector3& dir) { m_dir = dir; }

	//カメラの位置の取得関数
	DirectX::SimpleMath::Vector3 GetUpPosition() const { return m_up; }
	void SetUpPosition(const DirectX::SimpleMath::Vector3& up) { m_up = up; }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StageSelectCamera();

	/// <summary>
	/// カメラの更新
	/// </summary>
	void Update(const DirectX::SimpleMath::Vector3& target);

private:
	// 生成されたビュー行列
	DirectX::SimpleMath::Matrix m_view;


	// 生成されたビュー行列
	DirectX::SimpleMath::Vector3 m_target;

	// 生成されたビュー行列
	DirectX::SimpleMath::Vector3 m_eye;

	// 生成されたビュー行列
	DirectX::SimpleMath::Vector3 m_up;

	// 生成されたビュー行列
	DirectX::SimpleMath::Vector3 m_dir;

	//カメラの動きを滑らかにする
	float m_smooth;
};
