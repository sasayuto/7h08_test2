#pragma once
#include"../../Objects.h"

/// <summary>
/// 家のクラスを定義する
/// </summary>
class StoneStairs : public Objects
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StoneStairs();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StoneStairs()override;

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize()override;


};
