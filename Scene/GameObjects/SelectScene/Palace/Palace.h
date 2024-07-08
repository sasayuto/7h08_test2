#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"Scene/GameObjects/Models/Resources.h"

/// <summary>
/// アイテムの基底クラスを定義する
/// </summary>
class Palace
{
public:
	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

private:
	//位置
	DirectX::SimpleMath::Vector3 m_position;

	//位置
	DirectX::SimpleMath::Quaternion m_rotate;

	//モデルのポインタ
	DirectX::Model* m_pModel;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Palace();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Palace();

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">1フレーム時間</param>
	void Update(const float& elapsedTime);


	/// <summary>
	/// シャドウマップ用の画像を作る
	/// </summary>
	virtual void RenderShadowTex();

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();
};
