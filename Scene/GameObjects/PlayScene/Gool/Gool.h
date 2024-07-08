#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
class Player;

class Gool
{
public:
	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//大きさのセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetScale() { return m_scale; }
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }

	//シーン変更フラグのゲッター
	bool GetSceneFlag() { return m_sceneFlag; }

private:
	//位置
	DirectX::SimpleMath::Vector3 m_position;

	//大きさ
	DirectX::SimpleMath::Vector3 m_scale;

	//モデルのポインタ
	DirectX::Model* m_goolModel;

	//シーン変更のフラグ
	bool m_sceneFlag;

public:		
	//プレイヤーとの当たり判定
	bool HitCheck_Sphere2Sphere(const DirectX::SimpleMath::Vector3& Center, const float& Radius);

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Gool();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Gool();

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize();

	/// <summary>
	/// 処理を実行する
	/// </summary>
	/// <param name="player">プレイヤーのポインタ</param>
	void Update(Player* player);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

};
