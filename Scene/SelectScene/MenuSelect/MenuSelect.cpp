#include "pch.h"
#include "MenuSelect.h"
using namespace DirectX;

#include"StateManuScene/StageSelectScen.h"
#include"StateManuScene/TitleSelectScene.h"
#include"StateManuScene/OptionSelectScene.h"

MenuSelect::MenuSelect():
	m_selectNum(0)
{
}

MenuSelect::~MenuSelect()
{
}

void MenuSelect::Initialize(TitleScene* titleScene)
{
	CreateDeviceDependentResources();
	for (int i = 0; i < Menu::MENU_COUNT; i++)
	{
		m_object[i]->Initialize(
			DirectX::SimpleMath::Vector2(0, static_cast<float>(-i * WIDTH))
			, DirectX::SimpleMath::Vector2(1, 1)
			, tito::ANCHOR::MIDDLE_CENTER
			, tito::POSITION_ANCHOR::MIDDLE_CENTER
		);
	}

	m_underBar->Initialize(
		DirectX::SimpleMath::Vector2(0, 0)
		, DirectX::SimpleMath::Vector2(1, 1)
		, tito::ANCHOR::MIDDLE_CENTER
		, tito::POSITION_ANCHOR::MIDDLE_CENTER
	);

	m_select[Menu::STAGE_SELECT]->Initialize(this, titleScene);
	m_select[Menu::TITLE]->Initialize(this, titleScene);
	m_select[Menu::OPTION]->Initialize(this, titleScene);

	m_pCurrentState = m_select[Menu::STAGE_SELECT].get();
	m_selectNum = static_cast<int>(Menu::STAGE_SELECT);

}

void MenuSelect::Update(const bool& selectFlag, const bool& selectStartFlag)
{
	//���肳�ꂽ�瑀��Ȃ�
	if (!selectStartFlag)
	{
		//�I��
		if (KeyboardTracker::GetInstance()->Up()) m_selectNum--;
		if (KeyboardTracker::GetInstance()->Down())m_selectNum++;

		//�f���̊O�ɏo���璲��
		if (m_selectNum < 0) m_selectNum++;
		if (m_selectNum >= Menu::MENU_COUNT) m_selectNum--;
	}

		m_underBar->Update(m_selectNum);

		//�X�V�O�̃X�e�[�W�ԍ�
		m_pCurrentState = m_select[m_selectNum].get();

		//�X�e�[�W�̍X�V
		m_pCurrentState->Update(selectFlag);
	
}

void MenuSelect::Render()
{
	for (int i = 0; i < Menu::MENU_COUNT; i++)
	{
		m_object[i]->Render();
	}
	m_underBar->Render();

	m_pCurrentState->Render();
}

void MenuSelect::Finalize()
{
	m_pCurrentState->Finalize();
}

void MenuSelect::CreateDeviceDependentResources()
{	
	//�f���𐶐�
	m_object[Menu::STAGE_SELECT] = std::make_unique<StageSelectLetter>();
	m_object[Menu::TITLE] = std::make_unique<StageSelectLetter>();
	m_object[Menu::OPTION] = std::make_unique<StageSelectLetter>();

	m_object[Menu::STAGE_SELECT]->SetPath(L"Resources/Textures/StageSelectLetter.png");
	m_object[Menu::TITLE]->SetPath(L"Resources/Textures/TaitoruheLetter.png");
	m_object[Menu::OPTION]->SetPath(L"Resources/Textures/OperationExplanationLetter.png");

	m_select[Menu::STAGE_SELECT] = std::make_unique<StageSelectScen>();
	m_select[Menu::TITLE] = std::make_unique<TitleSelectScene>();
	m_select[Menu::OPTION] = std::make_unique<OptionSelectScene>();


	
	m_underBar = std::make_unique<UnderBar>();
}

