#pragma once
#include"../../../Objects.h"

/// <summary>
/// 家のクラスを定義する
/// </summary>
class BigBrickWall : public Objects
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BigBrickWall();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BigBrickWall()override;

	/// <summary>
/// 初期化する
/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新する
	/// </summary>
	void Update()override;

	/// <summary>
	/// 更新する
	/// </summary>
	void Render()override;

	/// <summary>
	/// シャドウマップ用の画像を作る
	/// </summary>
	void RenderShadowTex()override;

};
