//--------------------------------------------------------------------------------------
// File: Timer.h
//
// �Q�[�W
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

    //�ŏ������͂O�ł�����
    int digit = Timer % 10; // �ŉ��ʂ̌����擾
    //�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
    std::unique_ptr<tito::NumberManager> Number = std::make_unique<tito::NumberManager>();

    //�K�v�ȏ����Z�b�g����
    Number->Create(
        position - DirectX::SimpleMath::Vector2(index * 64* scale.x, 0)
        , scale
        , digit
        , anchor
    );

    index++;
    Timer /= 10; // �ŉ��ʂ̌����폜

    m_timerTex.push_back(std::move(Number));

    while (Timer > 0) {
        int digit = Timer % 10; // �ŉ��ʂ̌����擾
        //�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
        std::unique_ptr<tito::NumberManager> Number = std::make_unique<tito::NumberManager>();

        //�K�v�ȏ����Z�b�g����
        Number->Create(
            position - DirectX::SimpleMath::Vector2(index * 64 * scale.x, 0)
            , scale
            , digit
            , anchor
        );

        m_timerTex.push_back(std::move(Number));
        index++;
        Timer /= 10; // �ŉ��ʂ̌����폜
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
        int digit = Timer % 10; // �ŉ��ʂ̌����擾

        m_timerTex[index]->SetNumber(digit);

        index++;
        Timer /= 10; // �ŉ��ʂ̌����폜
    }

}
void TimerTex::Render()
{   
    //�Q�[�W�ƃx�[�X��`�悷��
    for (int i = 0; i < m_timerTex.size(); i++)
    {
        m_timerTex[i]->Render();
    }
}

void TimerTex::Finalize()
{
    m_timerTex.clear();
}

