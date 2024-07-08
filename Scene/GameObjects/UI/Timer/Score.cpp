//--------------------------------------------------------------------------------------
// File: Timer.h
//
// ゲージ
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Score.h"

using namespace DirectX;

ScoreTex::ScoreTex():
    m_ScoreTex{}
{
}

ScoreTex::~ScoreTex()
{
}

void ScoreTex::Initialize(const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& scale, const int& timer, const tito::ANCHOR& anchor)
{


    int Timer = timer;
    int index = 0;

    //最初だけは０でも書く
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
    index++;
    Timer /= 10; // 最下位の桁を削除

    
    m_ScoreTex.push_back(std::move(Number));
    //最初だけは０でも書く
    digit = Timer % 10; // 最下位の桁を取得
    //ゲージののリスポーンのインスタンスを生成する
    Number = std::make_unique<tito::NumberManager>();

    //必要な情報をセットする
    Number->Create(
        position - DirectX::SimpleMath::Vector2(index * 64 * scale.x, 0)
        , scale
        , digit
        , anchor
    );
    index++;
    Timer /= 10; // 最下位の桁を削除

    
    m_ScoreTex.push_back(std::move(Number));
    //最初だけは０でも書く
    digit = Timer % 10; // 最下位の桁を取得
    //ゲージののリスポーンのインスタンスを生成する
    Number = std::make_unique<tito::NumberManager>();

    //必要な情報をセットする
    Number->Create(
        position - DirectX::SimpleMath::Vector2(index * 64 * scale.x, 0)
        , scale
        , digit
        , anchor
    );
    index++;
    Timer /= 10; // 最下位の桁を削除

    
    m_ScoreTex.push_back(std::move(Number));
    //最初だけは０でも書く
    digit = Timer % 10; // 最下位の桁を取得
    //ゲージののリスポーンのインスタンスを生成する
    Number = std::make_unique<tito::NumberManager>();

    //必要な情報をセットする
    Number->Create(
        position - DirectX::SimpleMath::Vector2(index * 64 * scale.x, 0)
        , scale
        , digit
        , anchor
    );
    index++;
    Timer /= 10; // 最下位の桁を削除

    
    m_ScoreTex.push_back(std::move(Number));
    //最初だけは０でも書く
    digit = Timer % 10; // 最下位の桁を取得
    //ゲージののリスポーンのインスタンスを生成する
    Number = std::make_unique<tito::NumberManager>();

    //必要な情報をセットする
    Number->Create(
        position - DirectX::SimpleMath::Vector2(index * 64 * scale.x, 0)
        , scale
        , digit
        , anchor
    );
    index++;
    Timer /= 10; // 最下位の桁を削除

    
    m_ScoreTex.push_back(std::move(Number));
    //最初だけは０でも書く
    digit = Timer % 10; // 最下位の桁を取得
    //ゲージののリスポーンのインスタンスを生成する
    Number = std::make_unique<tito::NumberManager>();

    //必要な情報をセットする
    Number->Create(
        position - DirectX::SimpleMath::Vector2(index * 64 * scale.x, 0)
        , scale
        , digit
        , anchor
    );
    index++;
    Timer /= 10; // 最下位の桁を削除

    
    m_ScoreTex.push_back(std::move(Number));
    //最初だけは０でも書く
    digit = Timer % 10; // 最下位の桁を取得
    //ゲージののリスポーンのインスタンスを生成する
    Number = std::make_unique<tito::NumberManager>();

    //必要な情報をセットする
    Number->Create(
        position - DirectX::SimpleMath::Vector2(index * 64 * scale.x, 0)
        , scale
        , digit
        , anchor
    );
    index++;
    Timer /= 10; // 最下位の桁を削除

    
    m_ScoreTex.push_back(std::move(Number));

}


void ScoreTex::Update(const int& timer)
{

    for (auto& Number : m_ScoreTex)
    {
        Number->SetNumber(0);
    }

    int index = 0;
    int Timer = timer;
    while (Timer > 0) {
        int digit = Timer % 10; // 最下位の桁を取得

        m_ScoreTex[index]->SetNumber(digit);

        index++;
        Timer /= 10; // 最下位の桁を削除
    }

}
void ScoreTex::Render()
{   
    //ゲージとベースを描画する
    for (int i = 0; i < m_ScoreTex.size(); i++)
    {
        m_ScoreTex[i]->Render();
    }
}

