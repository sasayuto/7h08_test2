//--------------------------------------------------------------------------------------
// File: Timer.h
//
// ゲージ
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Timer.h"

using namespace DirectX;

TimerTex::TimerTex():
    m_timerTex{}
{
}

TimerTex::~TimerTex()
{
}

void TimerTex::Initialize(const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& scale, const float& timer, const tito::ANCHOR& anchor)
{

    int Timer = static_cast<int>(timer);
    int index = 0;

    //最初だけは０でも書く
    int digit = Timer % 10; // 最下位の桁を取得
    //ゲージののリスポーンのインスタンスを生成する
    std::unique_ptr<tito::NumberManager> Number = std::make_unique<tito::NumberManager>();

    //必要な情報をセットする
    Number->Create(
        position - DirectX::SimpleMath::Vector2(index * 64* scale.x, 0)
        , scale
        , digit
        , anchor
    );

    index++;
    Timer /= 10; // 最下位の桁を削除

    m_timerTex.push_back(std::move(Number));

    while (Timer > 0) {
        int digit = Timer % 10; // 最下位の桁を取得
        //ゲージののリスポーンのインスタンスを生成する
        std::unique_ptr<tito::NumberManager> Number = std::make_unique<tito::NumberManager>();

        //必要な情報をセットする
        Number->Create(
            position - DirectX::SimpleMath::Vector2(index * 64 * scale.x, 0)
            , scale
            , digit
            , anchor
        );

        m_timerTex.push_back(std::move(Number));
        index++;
        Timer /= 10; // 最下位の桁を削除
    }
}


void TimerTex::Update(const float& timer)
{

    for (auto& Number : m_timerTex)
    {
        Number->SetNumber(0);
    }

    int index = 0;
    int Timer = static_cast<int>(timer);
    while (Timer > 0) {
        int digit = Timer % 10; // 最下位の桁を取得

        m_timerTex[index]->SetNumber(digit);

        index++;
        Timer /= 10; // 最下位の桁を削除
    }

}
void TimerTex::Render()
{   
    //ゲージとベースを描画する
    for (int i = 0; i < m_timerTex.size(); i++)
    {
        m_timerTex[i]->Render();
    }
}

void TimerTex::Finalize()
{
    m_timerTex.clear();
}

