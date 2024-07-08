#include "pch.h"
#include "StageSelect.h"
using namespace DirectX;
#include"SelectTown.h"
#include"Tutorial.h"

//�f��
#include"Scene/GameObjects/Background/GrandCanyon.h"
#include"Scene/GameObjects/Background/CloudyBackGround.h"

void StageSelect::CreateDeviceDependentResources()
{
	//�����̂R�s�ǉ����邾��
		//�f���𐶐�
	//m_background[GRAND_CANYON] = std::make_unique<GrandCanyon>();
	//m_object[GRAND_CANYON] = std::make_unique<GrandCanyon>();
	//m_select[Planet::GRAND_CANYON] = std::make_unique<SelectGrandCanyon>();

	//m_background[CLOUDY] = std::make_unique<GrandCanyon>();
	//m_select[Planet::CLOUDY] = std::make_unique<SelectCloudyBackGround>();

	m_background[TOWN] = std::make_unique<CloudyBackGround>();
	m_select[Planet::TOWN] = std::make_unique<SelectTown>();

	m_background[TUTORIAL] = std::make_unique<CloudyBackGround>();
	m_select[Planet::TUTORIAL] = std::make_unique<Tutorial>();


}

StageSelect::StageSelect():
	m_selectNum(0),
	m_background{},
	m_flag{ false,false }

{
}

StageSelect::~StageSelect()
{
}

void StageSelect::Initialize(StageSelectScene* stageSelectScene)
{

	//�Q�[�W�ƃx�[�X��`�悷��
	for (int i = 0; i < 2; i++)
	{
		//�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
		m_HorizontalTriangle[i] = std::make_unique<tito::MoveUserInterface>();
		m_HorizontalTrianglecol[i] = std::make_unique<Collider::Box2D>();

	}
	//�K�v�ȏ����Z�b�g����
	m_HorizontalTriangle[0]->Create(
		L"Resources/Textures/HorizontalTrianglel.png"
		, DirectX::SimpleMath::Vector2(-1120, 0)
		, DirectX::SimpleMath::Vector2::One
		, tito::ANCHOR::MIDDLE_RIGHT
		, tito::POSITION_ANCHOR::MIDDLE_RIGHT
	);
	//�K�v�ȏ����Z�b�g����
	m_HorizontalTriangle[1]->Create(
		L"Resources/Textures/HorizontalTriangle.png"
		, DirectX::SimpleMath::Vector2(-90,0)
		, DirectX::SimpleMath::Vector2::One
		, tito::ANCHOR::MIDDLE_RIGHT
		, tito::POSITION_ANCHOR::MIDDLE_RIGHT
	);

	for (int i = 0; i < 2; i++)
	{
		//�����蔻��̏�����
		//�ʒu�A�T�C�Y���C�������l��n��
		m_HorizontalTrianglecol[i]->Initialize(
			m_HorizontalTriangle[i]->TexPositionCalculation(),
			m_HorizontalTriangle[i]->TexSizeCalculation()
		);
	}

	CreateDeviceDependentResources();
	//m_select[Planet::GRAND_CANYON]->Initialize(this, stageSelectScene);
	//m_select[Planet::CLOUDY]->Initialize(this, stageSelectScene);
	m_select[Planet::TOWN]->Initialize(this, stageSelectScene);
	m_select[Planet::TUTORIAL]->Initialize(this, stageSelectScene);

	for (int i = 0; i < COUNT; i++)
	{
		//�w�i��f���Ɖ��f����������
		m_background[i]->Initialize();

		//���Ԋu�ɕ��ׂ�
		m_background[i]->SetPosition(SimpleMath::Vector3(static_cast<float>(WIDTH) * i, 0.0f, 0.0f));

		//�w�i�f����傫������n
		m_background[i]->SetScale(SimpleMath::Vector3::One * static_cast<float>(SCALE));
	}

	m_pCurrentState = m_select[Planet::TUTORIAL].get();
	m_selectNum = static_cast<int>(Planet::TUTORIAL);
}

void StageSelect::Update(const bool& selectFlag, const bool& selectStartFlag, const bool& retuneSelectStartFlag)
{
	int selectNum = m_selectNum;
	//�I��
		//���肳�ꂽ�瑀��Ȃ�
	if (!selectStartFlag)
	{
		if (!retuneSelectStartFlag)
		{
			//�L�[����
			auto mouse = KeyboardSingleton::GetInstance()->GetMouseState();
			auto mouseTr = KeyboardTracker::GetInstance()->GetMouseTracker();

			m_HorizontalTriangle[0]->SetScale(DirectX::SimpleMath::Vector2(1.f, 1.f));

			if (m_HorizontalTrianglecol[0]->CheckHitPoint(mouse.x, mouse.y))
			{

				m_HorizontalTriangle[0]->SetScale(DirectX::SimpleMath::Vector2(1.2f, 1.2f));
				if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
					m_selectNum--;
				if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
					m_flag[0] = true;

			}
			if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
			{
				m_flag[0] = false;
				m_flag[1] = false;
			}

			if (m_flag[0])
				m_HorizontalTriangle[0]->SetBrightness(0.5f);
			else 
				m_HorizontalTriangle[0]->SetBrightness(1);

			m_HorizontalTriangle[1]->SetScale(DirectX::SimpleMath::Vector2(1.f, 1.f));
			if (m_HorizontalTrianglecol[1]->CheckHitPoint(mouse.x, mouse.y))
			{
				m_HorizontalTriangle[1]->SetScale(DirectX::SimpleMath::Vector2(1.2f, 1.2f));
				if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
					m_selectNum++;
				if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
					m_flag[1] = true;
			}
			if (m_flag[1])
				m_HorizontalTriangle[1]->SetBrightness(0.5f);
			else
				m_HorizontalTriangle[1]->SetBrightness(1);

			//�f���̊O�ɏo���璲��
			if (m_selectNum < 0) m_selectNum = Planet::COUNT - 1;
			if (m_selectNum >= Planet::COUNT) m_selectNum = 0;
		}
	}
	//�X�e�[�W���ς������ύX
	if (selectNum != m_selectNum) 
	{
		m_pCurrentState = m_select[m_selectNum].get();
	}

	//�X�e�[�W�̍X�V
	m_pCurrentState->Update(selectFlag, selectStartFlag);
}

void StageSelect::Render()
{
	m_pCurrentState->Render();

	//�Q�[�W�ƃx�[�X��`�悷��
	for (int i = 0; i < 2; i++)
	{
		m_HorizontalTriangle[i]->Render();
	}


}

void StageSelect::Finalize()
{
	m_pCurrentState->Finalize();
}

