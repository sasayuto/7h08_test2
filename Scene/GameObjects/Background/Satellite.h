#pragma once

#include"Background.h"

/// <summary>
/// Satelliteの背景クラスを定義する
/// </summary>
class Satellite :public Background
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Satellite();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Satellite()override;
};

