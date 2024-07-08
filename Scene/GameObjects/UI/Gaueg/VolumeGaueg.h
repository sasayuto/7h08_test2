#pragma once

#include "ImaseLib/GaugeManager.h"
#include "ImaseLib/MoveUserInterface.h"
#include "Scene/GameObjects/PlayScene/Colliider/Collision.h"

/// <summary>
/// ゲージのクラスを定義する
/// </summary>
class VolumeGaueg
{

public:

	static const int TEXTURE_ANCHOR_RATIO_NUM;

	//ゲージの割合を取得
	float GetRatio() const { return m_ratio; }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="m_player">プレイヤーのポインタ</param>
	VolumeGaueg();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~VolumeGaueg();

	/// <summary>
	///  初期化
	/// </summary>
	/// <param name="position">位置</param>
	/// <param name="scale">大きさ（基本１）</param>
	/// <param name="anchor">画像のどの端から描画するか</param>
	/// <param name="positionAnchor">スクリーン座標のどの端から描画するか</param>
	void Initialize(
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const tito::ANCHOR& anchor,
		const tito::POSITION_ANCHOR& positionAnchor,
		const float& ratio
	);

	/// <summary>
	/// 更新する
	/// </summary>
	void Update();

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();
	void SetRatio(const float& ratio);

private:
	/// <summary>
	/// ゲージを作る
	/// </summary>
	/// <param name="path">ゲージの画像</param>
	/// <param name="basePath">背景の画像</param>
	/// <param name="position">描画位置</param>
	/// <param name="scale">大きさ</param>
	/// <param name="anchor">描画開始位置</param>
	void Add(
		const wchar_t* path,
		const wchar_t* basePath,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const tito::ANCHOR& anchor,
		const tito::POSITION_ANCHOR& positionAnchor
	);
	//ゲージとベースのポインタ
	std::unique_ptr<tito::GaugeManager>  m_baes, m_frame;

	std::unique_ptr<tito::MoveUserInterface>  m_bottom;

	//Buttonの初期位置
	DirectX::SimpleMath::Vector2 m_initialBottonPosition;

	//Buttonの位置
	DirectX::SimpleMath::Vector2 m_BottonPosition;

	//Buttonが押されたか
	bool m_BottonFlag;

	//ボタンを押したときのx座標
	float m_pressedMousePos_x;
	float m_bottonPosStorage_x;

	float m_ratio;
	std::unique_ptr<Collider::Box2D> m_collider;
};
