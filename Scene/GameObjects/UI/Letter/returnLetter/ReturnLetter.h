#pragma once

#include "ImaseLib/MoveUserInterface.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
/// <summary>
/// タイトル名のクラスを定義する
/// </summary>
class ReturnLetter
{
public:

	bool GetMouseFlag() const { return m_mouseFlag; }

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="m_player">プレイヤーのポインタ</param>
	ReturnLetter();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ReturnLetter();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新する
	/// </summary>
	void Update(const float& nowTime);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

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
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const tito::ANCHOR& anchor,
		const tito::POSITION_ANCHOR& positionAnchor
	);

	Collider::Box2D* GetCollider() { return m_collider.get(); };
private:
	//ゲージとベースのポインタ
	std::unique_ptr<tito::MoveUserInterface> m_returnLetter;

	//当たり判定
	std::unique_ptr<Collider::Box2D> m_collider;

	//マウスとあたっているか
	bool m_mouseFlag;
};
