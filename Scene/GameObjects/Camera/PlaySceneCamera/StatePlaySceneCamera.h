//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
#pragma once
class PlaySceneCamera;
/// <summary>
/// プレイカメラクラスを定義する
/// </summary>
class StatePlaySceneCamera
{
public:

	//親を取得
	PlaySceneCamera* GetParent() { return m_pParent; };

	/// <summary>
	/// コンストラクタ
	/// </summary>
	StatePlaySceneCamera(){}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~StatePlaySceneCamera(){}

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize(PlaySceneCamera* parent) { m_pParent = parent; };

	/// <summary>
	/// リセットする
	/// </summary>
	virtual void Reset() {}

	/// <summary>
	/// カメラの更新
	/// </summary>
	/// <param name="rot">プレイヤーの角度</param>
	/// <param name="playerPosition">プレイヤーの位置</param>
	virtual void Update(
		const int& playerHP, 
		const DirectX::SimpleMath::Quaternion& rotate,
		const DirectX::SimpleMath::Vector3& position
	) {
		playerHP, rotate, position;
	};
private:
	//親のポインタ
	PlaySceneCamera* m_pParent;
};
