#pragma once
#include"Floor.h"
/// <summary>
/// 地面のクラスを定義する
/// </summary>
class StoneFloor :public Floor
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	StoneFloor();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StoneFloor();

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize()override;

};
