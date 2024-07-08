
#pragma once

#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"

/// <summary>
/// 背景の基底クラスを定義する
/// </summary>
class Background
{
public:
    //モデルのセッター、ゲッター
    DirectX::Model* GetBackGroundModel() { return m_backgroundModel; }
    void SetBackGroundModel(DirectX::Model* backgroundModel) { m_backgroundModel = backgroundModel; }

    //大きさのセッター、ゲッター
    void SetScale( const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
    DirectX::SimpleMath::Vector3 GetScale() const { return m_scale; }

    //位置のセッター、ゲッター
    void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
    DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }

    //回転のセッター
    void SetRotateX(const float& rotateX) { m_rotateY = rotateX; }

    static const float ROTATE_SPEED;

public:
    /// <summary>
    /// 回転の動き
    /// </summary>
    virtual void SelectMotion();

    /// <summary>
    /// 選択画面の描画設定
    /// </summary>
    virtual void RotateRender();

public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    Background();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Background();

    /// <summary>
    /// 初期化する
    /// </summary>
    virtual void Initialize();

    /// <summary>
    /// 描画する
    /// </summary>
    virtual void Render();

    /// <summary>
    /// 後始末
    /// </summary>
    virtual void Finalize();

private:
    //大きさ
    DirectX::SimpleMath::Vector3 m_scale;

    //位置
    DirectX::SimpleMath::Vector3 m_position;

    //モデル
    DirectX::Model* m_backgroundModel;

    //回転
    float m_rotateY;
};

