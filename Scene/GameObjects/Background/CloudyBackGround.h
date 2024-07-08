#pragma once

#include"Background.h"

/// <summary>
/// CloudyBackGroundの背景クラスを定義する
/// </summary>
class CloudyBackGround :public Background
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CloudyBackGround();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~CloudyBackGround()override;
};

