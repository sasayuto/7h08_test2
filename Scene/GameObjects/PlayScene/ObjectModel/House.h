#pragma once
#include"Objects.h"

/// <summary>
/// 家のクラスを定義する
/// </summary>
class House : public Objects
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	House();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~House()override;

	/// <summary>
/// 初期化する
/// </summary>
	void Initialize()override;


};
