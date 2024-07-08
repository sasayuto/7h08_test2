#pragma once
#include"Floor/Floor.h"
/// <summary>
/// 地面のクラスを定義する
/// </summary>
class Ground:public Floor
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Ground();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Ground();

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize()override;
};
