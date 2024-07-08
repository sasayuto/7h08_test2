//--------------------------------------------------------------------------------------
// File: Timer.h
//
// �Q�[�W
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

    //�ŏ������͂O�ł�����
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
    index++;
    Timer /= 10; // �ŉ��ʂ̌����폜

    
    m_ScoreTex.push_back(std::move(Number));
    //�ŏ������͂O�ł�����
    digit = Timer % 10; // �ŉ��ʂ̌����擾
    //�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
    Number = std::make_unique<tito::NumberManager>();

    //�K�v�ȏ����Z�b�g����
    Number->Create(
        position - DirectX::SimpleMath::Vector2(index * 64 * scale.x, 0)
        , scale
        , digit
        , anchor
    );
    index++;
    Timer /= 10; // �ŉ��ʂ̌����폜

    
    m_ScoreTex.push_back(std::move(Number));
    //�ŏ������͂O�ł�����
    digit = Timer % 10; // �ŉ��ʂ̌����擾
    //�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
    Number = std::make_unique<tito::NumberManager>();

    //�K�v�ȏ����Z�b�g����
    Number->Create(
        position - DirectX::SimpleMath::Vector2(index * 64 * scale.x, 0)
        , scale
        , digit
        , anchor
    );
    index++;
    Timer /= 10; // �ŉ��ʂ̌����폜

    
    m_ScoreTex.push_back(std::move(Number));
    //�ŏ������͂O�ł�����
    digit = Timer % 10; // �ŉ��ʂ̌����擾
    //�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
    Number = std::make_unique<tito::NumberManager>();

    //�K�v�ȏ����Z�b�g����
    Number->Create(
        position - DirectX::SimpleMath::Vector2(index * 64 * scale.x, 0)
        , scale
        , digit
        , anchor
    );
    index++;
    Timer /= 10; // �ŉ��ʂ̌����폜

    
    m_ScoreTex.push_back(std::move(Number));
    //�ŏ������͂O�ł�����
    digit = Timer % 10; // �ŉ��ʂ̌����擾
    //�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
    Number = std::make_unique<tito::NumberManager>();

    //�K�v�ȏ����Z�b�g����
    Number->Create(
        position - DirectX::SimpleMath::Vector2(index * 64 * scale.x, 0)
        , scale
        , digit
        , anchor
    );
    index++;
    Timer /= 10; // �ŉ��ʂ̌����폜

    
    m_ScoreTex.push_back(std::move(Number));
    //�ŏ������͂O�ł�����
    digit = Timer % 10; // �ŉ��ʂ̌����擾
    //�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
    Number = std::make_unique<tito::NumberManager>();

    //�K�v�ȏ����Z�b�g����
    Number->Create(
        position - DirectX::SimpleMath::Vector2(index * 64 * scale.x, 0)
        , scale
        , digit
        , anchor
    );
    index++;
    Timer /= 10; // �ŉ��ʂ̌����폜

    
    m_ScoreTex.push_back(std::move(Number));
    //�ŏ������͂O�ł�����
    digit = Timer % 10; // �ŉ��ʂ̌����擾
    //�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
    Number = std::make_unique<tito::NumberManager>();

    //�K�v�ȏ����Z�b�g����
    Number->Create(
        position - DirectX::SimpleMath::Vector2(index * 64 * scale.x, 0)
        , scale
        , digit
        , anchor
    );
    index++;
    Timer /= 10; // �ŉ��ʂ̌����폜

    
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
        int digit = Timer % 10; // �ŉ��ʂ̌����擾

        m_ScoreTex[index]->SetNumber(digit);

        index++;
        Timer /= 10; // �ŉ��ʂ̌����폜
    }

}
void ScoreTex::Render()
{   
    //�Q�[�W�ƃx�[�X��`�悷��
    for (int i = 0; i < m_ScoreTex.size(); i++)
    {
        m_ScoreTex[i]->Render();
    }
}

