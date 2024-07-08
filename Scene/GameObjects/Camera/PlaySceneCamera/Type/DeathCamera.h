//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
#pragma once
#include"../StatePlaySceneCamera.h"
/// <summary>
/// プレイカメラクラスを定義する
/// </summary>
class DeathCamera :public StatePlaySceneCamera
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	DeathCamera();

	void Reset();
	/// <summary>
	/// カメラの更新
	/// </summary>
	/// <param name="rot">プレイヤーの角度</param>
	/// <param name="playerPosition">プレイヤーの位置</param>
	void Update(
		const int& playerHP,
		const DirectX::SimpleMath::Quaternion& rot,
		const DirectX::SimpleMath::Vector3& playerPosition
	)override;

	//視点の初期値
	static const DirectX::SimpleMath::Vector3 EYE_INITIAL_VALUE;	
private:
	// 注視点
	DirectX::SimpleMath::Vector3 m_target;

	float m_targetAnimationX;

	float m_yTmp;

	// 縦回転
	float m_xTmp;

	// ドラッグされた座標
	int m_x, m_y;

	// マウスの回転
	DirectX::SimpleMath::Matrix m_mauseRotate;

private:
	/// <summary>
	/// マウスの動き
	/// </summary>
	/// <param name="x">マウスの横回転</param>
	/// <param name="y">マウスの縦回転</param>
	void Motion(const int& x, const int& y);

};
