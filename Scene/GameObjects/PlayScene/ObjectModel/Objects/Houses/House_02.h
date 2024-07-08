#pragma once
#include"../../Objects.h"

/// <summary>
/// 家のクラスを定義する
/// </summary>
class House_02 : public Objects
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	House_02();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~House_02()override;

	/// <summary>
/// 初期化する
/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新する
	/// </summary>
	void Update()override;


};
