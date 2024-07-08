#include "pch.h"
#include"PlayerKillMotion.h"
#include<random>

using namespace DirectX;

const float KillMotion::FALL_SPEED_ACCELERATION	(0.03f / 60);	//�����̉����x			(m/s)
const float KillMotion::EXPLOSIVE_POWER_XZ		(1.0f / 60);	//�����̉��̃p���[		(m/s)
const float KillMotion::EXPLOSIVE_A				(2.0f / 60);	//�����̉��̃p���[		(m/s)
const float KillMotion::EXPLOSIVE_ROTATE		(120 / 60);		//���f���̉�]�̑���	(��/s�j
const float KillMotion::NEXT_MOTION_TIME		(3);			//���̏�Ԃ܂ł̎���	(s)

KillMotion::KillMotion(Player* parent):
	m_pPlayer(parent),
	m_nextMotionTime()
{
}

KillMotion::~KillMotion()
{
}

void KillMotion::Initialize()
{
	//������
	m_nextMotionTime = 0.0f;
	//m_pPlayer->SetRotate(SimpleMath::Quaternion::Identity);

	//�v���C���[�𐶑����Ȃ���
	m_pPlayer->SetSurvival(false);

	m_pPlayer->PartsInitialize();

	//�v���C���[�̏�Ԃɂ���Ĕ��a���ς��̂ŃZ�b�g
	m_pPlayer->GetCollider()->SetRadius(20);

}

void KillMotion::Update(const float& elapsedTime)
{
	//�o�ߎ��Ԃ̌v�Z
	m_nextMotionTime += elapsedTime;

	m_pPlayer->PartsExplosion();

	//���Ń{�f�B�[�̈ʒu�ɂ��Ƃ��i�J�����������Ȃ����߁j
	m_pPlayer->SetPosition(m_pPlayer->GetParts()[0]->GetPosition());

	//���Ԍo�߂Ŏ��̃��[�V������
	if (m_nextMotionTime >= NEXT_MOTION_TIME)
	{
		//�L���̏�Ԃ���߂�Ƃ��̓��Z�b�g���ĂԁI
		m_pPlayer->Reset();
		m_pPlayer->SetIState(m_pPlayer->GetMotion());
	}

	if (m_pPlayer->GetFuel() >= 0)
	{
		//���̉��̃G�t�F�N�g�̍X�V
		m_pPlayer->GetPlayerEffect()->Update(elapsedTime,
			m_pPlayer->GetPosition(),
			m_pPlayer->GetParts()[0]->GetRotate(),
			m_pPlayer->GetHP()
		);
	}

}

void KillMotion::Render()
{
	m_pPlayer->PartsRender();
	m_pPlayer->GetPlayerEffect()->Render();
	m_pPlayer->GetBloodEffect()->Render();
}

void KillMotion::Finalize()
{
}

void KillMotion::Motion(const float& elapsedTime)
{
	elapsedTime;
}

