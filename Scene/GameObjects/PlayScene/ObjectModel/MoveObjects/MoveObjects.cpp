#include "pch.h"
#include"MoveObjects.h"
#include <math.h>
#include<random>
using namespace DirectX;
#include"MoveObjectsManager.h"

#include"../Bench/BenchParts/BenchPartFactory.h"
const float MoveObjects::ANIMATION_TIME(10.0f);//�������[�V�����̎���

MoveObjects::MoveObjects():
	m_position(SimpleMath::Vector3::Zero),
	m_rotate(SimpleMath::Quaternion::Identity),
	m_survival(false),
	m_timer(0),
	m_killCountFlag(false),
	m_allSurvivalFlag(true),
	m_pPartModel(nullptr),
	m_world()
{
}

MoveObjects::~MoveObjects()
{

}

void MoveObjects::Initialize(BulletManager* bulletManager, MoveObjectsManager* benchManager)
{
	m_pBulletManager = bulletManager;

	m_pBenchManager = benchManager;
	//�����蔻��𐶐�
	m_roughCollider = std::make_unique<Collider::Sphere>();
	m_timer = 0;
	//��܂��ȓ����蔻��Ɉʒu�Ɣ��a���Z�b�g
	GetRoughCollider()->SetPosition(GetPosition()+DirectX::SimpleMath::Vector3(0,3,0));


	//�X�P�[�����O�A�ʒu�����A��]��������
	m_world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

	//�Ίp���̔���
	GetRoughCollider()->SetRadius(12);
	for (auto& parts : m_parts)
	{
		parts->Initialize();
	}
	m_survival = true;
}

void MoveObjects::Update(const float& elapsedTime)
{	
	//�p�[�c�������Ă��邩
	bool PartsSurvival = false;
	for (auto& parts : m_parts)
	{
		if (parts->GetSurvival())
		{
			parts->Update(elapsedTime,m_position, m_rotate);
			PartsSurvival = true;
		}
		else
			parts->Explosion(elapsedTime);
	}
	//�p�[�c�����ׂĎ��񂾂�A�j���[�V�����̎��Ԃ�}��
	if (!PartsSurvival)
	{
		m_timer += elapsedTime;
		//�L���J�E���g���ĂȂ������炷��
		if (!m_killCountFlag)
		{
			m_pBenchManager->SetBenchKillCount(m_pBenchManager->GetBenchKillCount() + 1);
			//�J�E���g������true�ɂ���
			m_killCountFlag = true;
		}

		//�A�j���[�V�������I�������Ȃ���
		if (m_timer >= ANIMATION_TIME)
			m_survival = false;
	}
	if (m_pBulletManager)
		m_pBulletManager->CheckHitDestructionObjects(this);

	//��ł����Ă��邩
	for (auto& parts : m_parts)
	{
		if (!parts->SurvivalCheck())
		{
			m_allSurvivalFlag = false;
			break;
		}
	}
}

void MoveObjects::Render()
{
	if (m_allSurvivalFlag)
	{
		//���E�ɓ����Ă��邩
		if (Draw::GetInstance()->VisibilityRange(GetPosition(), GetModel()->meshes[0]->boundingSphere.Radius))
			return;

		// ��s�@�̕`��
		Draw::GetInstance()->ShadowMapRender(m_pPartModel, m_world);
	}
	else
		for (auto& parts : m_parts)
			parts->Render();

		//Draw::GetInstance()->TestSphereModel(GetRoughCollider()->GetRadius(), GetRoughCollider()->GetPosition());
}

void MoveObjects::RenderShadowTex()
{
	if (m_allSurvivalFlag)
	{
		// ��s�@�̕`��
		Draw::GetInstance()->ShadowMapTexCreate(m_pPartModel, m_world);
	}
	else
		for (auto& parts : m_parts)
			parts->RenderShadowTex();
}

void MoveObjects::SetpositionRandam(const float& min, const float& max)
{
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> distance(min, max);

	float x = static_cast<float>(distance(engine));
	float z = static_cast<float>(distance(engine));

	m_position = SimpleMath::Vector3(x, 0, z);
	m_rotate = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, x);
}
