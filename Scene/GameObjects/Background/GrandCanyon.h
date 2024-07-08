#pragma once

#include"Background.h"

/// <summary>
/// GrandCanyonの背景クラスを定義する
/// </summary>
class GrandCanyon :public Background
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GrandCanyon();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GrandCanyon()override;
};
