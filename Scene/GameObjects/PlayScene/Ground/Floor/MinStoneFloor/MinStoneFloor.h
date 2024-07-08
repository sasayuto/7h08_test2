#pragma once
#include"../Floor.h"
/// <summary>
/// 地面のクラスを定義する
/// </summary>
class MinStoneFloor :public Floor
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	MinStoneFloor();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MinStoneFloor();

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize()override;

	/// <summary>
/// 更新する
/// </summary>
	void Update()override;

	/// <summary>
	/// 描画する
	/// </summary>
	void Render()override;


};
