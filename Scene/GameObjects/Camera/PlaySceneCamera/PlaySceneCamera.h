//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
#pragma once
#include"StatePlaySceneCamera.h"
/// <summary>
/// プレイカメラクラスを定義する
/// </summary>
class PlaySceneCamera
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

	//死亡の状態
	StatePlaySceneCamera* GetDeathCamera() { return m_DeathCamera.get(); }

	//停止の状態
	StatePlaySceneCamera* GetNormalCamera() { return m_NormalCamera.get(); }

	//現在の状態セット
	void SetIState(StatePlaySceneCamera* Istate) {
		m_pCurrentState = Istate;
		m_pCurrentState->Reset();
	}

	static const float EYE_SPEED_RATE;		// カメラの位置への距離の差分に対する割合
	static const float TARGET_SPEED_RATE;	// 注視点への距離の差分に対する割合
	static const float MOUSE_SENSITIVITY;	// マウス感度
	static const float MOUSE_SMOOTH;		// マウスを徐々に戻す


public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlaySceneCamera();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	~PlaySceneCamera();

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize() ;

	/// <summary>
	/// カメラの更新
	/// </summary>
	/// <param name="rot">プレイヤーの角度</param>
	/// <param name="playerPosition">プレイヤーの位置</param>
	void Update(
		const int& playerHP,
		const DirectX::SimpleMath::Quaternion& rot,
		const DirectX::SimpleMath::Vector3& playerPosition
	);

private:
	// 生成されたビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// 視点
	DirectX::SimpleMath::Vector3 m_eye;

	// 注視点
	DirectX::SimpleMath::Vector3 m_target;

	// 注視点
	DirectX::SimpleMath::Vector3 m_up;

	// 注視点
	DirectX::SimpleMath::Vector3 m_dir;

	//通常のカメラのポインタ
	std::unique_ptr<StatePlaySceneCamera> m_NormalCamera;

	//デスのカメラのポインタ
	std::unique_ptr<StatePlaySceneCamera> m_DeathCamera;

	//現在の状態のポインタ
	StatePlaySceneCamera* m_pCurrentState;

};
