#pragma once

#include"Background.h"

/// <summary>
/// Satelliteの背景クラスを定義する
/// </summary>
class CityNight :public Background
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CityNight();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~CityNight()override;
};

