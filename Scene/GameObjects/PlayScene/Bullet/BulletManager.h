#pragma once
#include"Bullet.h"
#include<list>
class Player;
class Enemy;
class StreetLight;
class MoveObjects;
class Airship;
class Turret;
class CrabRobot;
class HouseMoveObjects;
/// <summary>
/// ���̊Ǘ��҃N���X���`����
/// </summary>
class BulletManager
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BulletManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BulletManager();

	/// <summary>
	/// ����������
	/// </summary>
	void Intialize();

	/// <summary>
	/// ���������s����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

	/// <summary>
	/// �`�悷��
	/// </summary>
	void RenderShadowTex();

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize();

	/// <summary>
	/// ���̔���
	/// </summary>
	/// <param name="bulletType">���̎g�p��</param>
	/// <param name="shooterType">���̎��</param>
	/// <param name="position">�g�p���̈ʒu</param>
	/// <param name="rotate">�g�p���̊p�x</param>
	void Shot(
		const Bullet::BulletType& bulletType, 
		const Bullet::BulletParent& shooterType,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate
	);
	/// <summary>
	/// �v���C���[�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="character">�L�����N�^�[�̃A�h���X</param>
	template<typename Object>
	void CheckHitDamegeObjects(Object* object, Bullet::BulletParent MyParent);

	/// <summary>
	/// ��s�D�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="character">�G�̃A�h���X</param>
	template<typename Object>
	void CheckHitDestructionObjects(Object* object);

private:
	//���̔z��̃|�C���^
	std::list<std::unique_ptr<Bullet>> m_bulletList;
};

template<typename Object>
inline void BulletManager::CheckHitDamegeObjects(Object* object, Bullet::BulletParent MyParent)
{
	for (std::list<std::unique_ptr<Bullet>>::iterator itBullet = m_bulletList.begin(); itBullet != m_bulletList.end(); itBullet++)
	{
		for (size_t i = 1; i <= 10; i++)
		{
			bool HitFlag = false;
			itBullet->get()->GetCollider()->SetPosition(itBullet->get()->GetPosition() - itBullet->get()->GetMove() * (static_cast<float>(i) * 0.1f));

			//�����̋��ł���
			if (itBullet->get()->GetParentType() == MyParent)
				continue;

			//�����蔻��
			//�v���C���[�̑�܂��ȓ����蔻��
			if (!itBullet->get()->GetCollider()->CheckHitSphere(object->GetCollider()))
				continue;

			//�v���C���[�̃p�[�c�Ƃ̓����蔻��
			for (auto& playerParts : object->GetParts())
			{
				if (!playerParts->CollisionBullet(itBullet->get()))
					continue;
				else  HitFlag = true;
				//���𖢎g�p�ɂ���
				itBullet->get()->SetisActive(false);

				//�������Ă�����_���[�W����
				object->Damage(itBullet->get()->GetOffensivePower());
				break;
			}
			if (HitFlag)
				break;
		}
	}

}

template<typename Object>
inline void BulletManager::CheckHitDestructionObjects(Object* object)
{
	int CheckNum = 4;
	for (std::list<std::unique_ptr<Bullet>>::iterator itBullet = m_bulletList.begin(); itBullet != m_bulletList.end(); itBullet++)
	{
		for (size_t i = 1; i <= CheckNum; i++)
		{
			bool HitFlag = false;
			itBullet->get()->GetCollider()->SetPosition(itBullet->get()->GetPosition() - itBullet->get()->GetMove() * (static_cast<float>(i) / static_cast<float>(CheckNum)));

			//���̂Ƃ���v���C���[�Ƃ̔��肾�����
			if (itBullet->get()->GetParentType() != Bullet::BulletParent::PlayerBullet)
				continue;

			//�x���`�̑�܂��ȓ����蔻��
			if (!object->GetRoughCollider()->CheckHitSphere(itBullet->get()->GetCollider()))
				continue;

			//�x���`�p�[�c�Ƃ̓����蔻��
			for (auto& streetLightParts : object->GetParts())
			{
				if (!streetLightParts->Collision(itBullet->get()))
					continue;
				else  HitFlag = true;

				//�p�[�c���΂炯��̂ő�܂��Ȕ����傫������
				object->GetRoughCollider()->SetRadius(
					object->GetRoughCollider()->GetRadius() * 5.0f
				);

				//���𖢎g�p�ɂ���
				itBullet->get()->SetisActive(false);
			}
			if (HitFlag)
				break;

		}
	}

}
