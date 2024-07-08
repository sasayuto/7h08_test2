#pragma once
#include"Floor.h"
/// <summary>
/// 地面のクラスを定義する
/// </summary>
class BlackFloor :public Floor
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BlackFloor();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BlackFloor();

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize()override;

};
