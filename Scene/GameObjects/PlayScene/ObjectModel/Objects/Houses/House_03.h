#pragma once
#include"../../Objects.h"

/// <summary>
/// 家のクラスを定義する
/// </summary>
class House_03 : public Objects
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	House_03();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~House_03()override;

	/// <summary>
/// 初期化する
/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新する
	/// </summary>
	void Update()override;


};
