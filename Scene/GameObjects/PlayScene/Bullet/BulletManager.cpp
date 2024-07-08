#include"pch.h"
#include"BulletManager.h"

//�����蔻��
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/StreetLight/StreetLight.h"
#include"Scene/GameObjects/PlayScene/Character/Turret/Turret.h"
#include"Scene/GameObjects/PlayScene/Character/CrabRobot/CrabRobot.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Bench/Bench.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/HouseMoveObjects/HouseMoveObjects.h"

//���̎��
#include"Bullet_01.h"
#include"Bullet_02.h"
#include"Bullet_Turret.h"

using namespace DirectX;

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
	
}

//�Q�[���̏��������s���֐�
void BulletManager::Intialize()
{
}

//�Q�[���̍X�V���s���֐�
void BulletManager::Update()
{
	//���̍X�V
	for (std::list<std::unique_ptr<Bullet>>::iterator itBullet = m_bulletList.begin(); itBullet != m_bulletList.end(); itBullet++)
	{
		//�`�拗���ݒ�
		if (Draw::GetInstance()->DespawnDistance(itBullet->get()->GetPosition(), 300.0f))
			itBullet->get()->SetisActive(false);

		//�g�p����ĂȂ������烊�X�g����r��
		if (!itBullet->get()->GetisActive())
		{
			itBullet = m_bulletList.erase(itBullet);
			if (itBullet == m_bulletList.end()) break;
			continue;

		}
		//���̍X�V
		itBullet->get()->Update();

		////���Ƌ��̓����蔻��i�d���j
		//CheckHitBullet(m_bulletList[i].get());
	}
}

void BulletManager::Render()
{
	for (std::list<std::unique_ptr<Bullet>>::iterator itBullet = m_bulletList.begin(); itBullet != m_bulletList.end(); itBullet++)
	{
		//���E�ɓ����Ă��邩
		if (Draw::GetInstance()->VisibilityRange(itBullet->get()->GetPosition()))
			continue;

		//���̕`��
		itBullet->get()->Render();

	}
}

void BulletManager::RenderShadowTex()
{
	for (std::list<std::unique_ptr<Bullet>>::iterator itBullet = m_bulletList.begin(); itBullet != m_bulletList.end(); itBullet++)
	{
		//���E�ɓ����Ă��邩
		if (Draw::GetInstance()->VisibilityRange(itBullet->get()->GetPosition()))
			continue;

		//���̕`��
		itBullet->get()->RenderShadowTex();

	}

}

void BulletManager::Finalize()
{
	//timer��n����m_effect�̍X�V�������s��
	for (std::list<std::unique_ptr<Bullet>>::iterator itBullet = m_bulletList.begin(); itBullet != m_bulletList.end(); itBullet++)
	{
		//���̌�n��
		itBullet->get()->Finalize();
	}
}

//���̔���
void BulletManager::Shot(const Bullet::BulletType& bulletType, const Bullet::BulletParent& shooterType, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate)
{
	//���𐶐�
	std::unique_ptr<Bullet> bullet;

	//�^�C�v�ɂ���Đ�����ς���
	switch (bulletType)
	{
	case Bullet::BulletType::Type1:
		bullet = std::make_unique<Bullet_01>();
		bullet->Initialize(shooterType, position, rotate);
		m_bulletList.push_back(std::move(bullet));
		break;

	case Bullet::BulletType::Type2:
		bullet = std::make_unique<Bullet_02>();
		bullet->Initialize(shooterType, position, rotate);
		m_bulletList.push_back(std::move(bullet));
		break;

	case Bullet::BulletType::Turret:
		bullet = std::make_unique<Bullet_Turret>();
		bullet->Initialize(shooterType, position, rotate);
		m_bulletList.push_back(std::move(bullet));
		break;

	}
}


