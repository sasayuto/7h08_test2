////--------------------------------------------------------------------------------------
////--------------------------------------------------------------------------------------
//#pragma once
//
///// <summary>
///// プレイカメラクラスを定義する
///// </summary>
//class PlayCamera
//{
//public:
//	// カメラのビュー行列の取得関数
//	DirectX::SimpleMath::Matrix GetCameraMatrix() const { return m_view; };
//
//	//カメラの位置の取得関数
//	DirectX::SimpleMath::Vector3 GetEyePosition() const { return m_eye;}
//
//	//カメラの注視点の取得関数
//	DirectX::SimpleMath::Vector3 GetTargetPosition() const { return m_target; }
//
//	//カメラの位置の取得関数
//	DirectX::SimpleMath::Vector3 GetUpPosition() const { return m_up; }
//
//public:
//	/// <summary>
//	/// コンストラクタ
//	/// </summary>
//	PlayCamera();
//
//	/// <summary>
//	/// カメラの更新
//	/// </summary>
//	/// <param name="rot">プレイヤーの角度</param>
//	/// <param name="playerPosition">プレイヤーの位置</param>
//	void Update(
//		const DirectX::SimpleMath::Quaternion& rot, 
//		const DirectX::SimpleMath::Vector3& playerPosition,
//		const DirectX::SimpleMath::Vector3& eye= DirectX::SimpleMath::Vector3(0,0,7)
//	);
//
//private:
//	// 生成されたビュー行列
//	DirectX::SimpleMath::Matrix m_view;
//
//	// 視点
//	DirectX::SimpleMath::Vector3 m_eye;
//
//	// 注視点
//	DirectX::SimpleMath::Vector3 m_target;
//
//	// 注視点
//	DirectX::SimpleMath::Vector3 m_up;
//
//	float m_targetAnimationX;
//
//
//////マウスの処理////
//private:
//
//	// 横回転
//	float m_yTmp;
//
//	// 縦回転
//	float m_xTmp;
//
//	// ドラッグされた座標
//	int m_x, m_y;
//
//	// マウスの回転
//	DirectX::SimpleMath::Matrix m_mauseRotate;
//
//private:
//	/// <summary>
//	/// マウスの動き
//	/// </summary>
//	/// <param name="x">マウスの横回転</param>
//	/// <param name="y">マウスの縦回転</param>
//	void Motion(const int& x, const int& y);
//
//	/// <summary>
//	/// マウスの処理
//	/// </summary>
//	void Mouse();
//
//};
