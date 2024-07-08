#include "pch.h"
#include"CoinGet.h"
#include<random>
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"

#include"../TutorialUI.h"
using namespace DirectX;

const float DRAWING_TIME(1);

CoinGet::CoinGet(TutorialUI* tutorialUI):
	IStateTutorialUI(),
	m_pTutorialUI(tutorialUI),
	m_wasdPushFlag(false)
{
}

void CoinGet::Initialize()
{
	//�����̐ݒ�
	GetTextLetter()->Initialize(
		L"Resources/Textures/CoinGetLtter.png",
		DirectX::SimpleMath::Vector2(0, 30),
		DirectX::SimpleMath::Vector2::One,
		tito::ANCHOR::BOTTOM_CENTER,
		tito::POSITION_ANCHOR::BOTTOM_CENTER
	);
}

void CoinGet::Update(const float& elapsedTime)
{
	//�R�C���Q�b�g�~�b�V������true�ɂ���
	m_pTutorialUI->SetCoinDrawFlag(true);

	//�R�C�����Ƃ�����true
	if (m_pTutorialUI->GetCoinGetFlag())
		m_wasdPushFlag = true;

	//�R�C�����Ƃ��ĂȂ�������||�`�掞�Ԉȓ���������
	if (m_wasdPushFlag == false ||
		GetTimer() <= DRAWING_TIME)
	{
		//�����̍X�V
		GetTextLetter()->Update(elapsedTime);

		//�R�C�����Ƃ��ĂȂ������玞�Ԃ͐i�߂Ȃ�
		if (GetTimer() <= DRAWING_TIME)
			SetTimer(GetTimer() + elapsedTime);
		//�I��
		return;
	}

	//�R�C���Q�b�g�~�b�V������true�ɂ���
	m_pTutorialUI->SetCoinMissionAccomplishedFlag(true);

	//�R�C�����Ƃ����玞�Ԃ�i�߂�
	SetTimer(GetTimer() + elapsedTime);

	//�����̏I������
	GetTextLetter()->ReduceTransparency(elapsedTime);

	//�����̏I���������I�������
	if (GetTimer() >= DRAWING_TIME + TutorialUI::FADE_TIME)
	{
		//���̃V�[���Ƀi�C�X������Ƃ��͎��ɍs�����ߕ��������ɃZ�b�g����
		m_pTutorialUI->SetNiceUis(TUTORIAl_UIS::BENCH_STREET_LIGHT_GET);

		//�i�C�X�̎��ɂȂɂ����t���͂��ނƂ��ɂ����ɃZ�b�g����
		m_pTutorialUI->SetPraiseUis(TUTORIAl_UIS::SCORE_UP_LETTER);

		//���ɍs���V�[�����Z����
		m_pTutorialUI->SetCurrentState(m_pTutorialUI->GetTutorialUI()[TUTORIAl_UIS::NICE_LETTER].get());
	}
}

void CoinGet::Render()
{
	GetTextLetter()->Render();
}

void CoinGet::Finalize()
{
}

void CoinGet::Reset()
{
	SetTimer(0);
	m_wasdPushFlag = false;
}