#pragma once
#include <pch.h>
#include"ICrabRobotComponent.h"

#include"Scene/GameObjects/PlayScene/Bullet/Bullet.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

/// <summary>
/// PlayerComponent�̃N���X���`����
/// </summary>
class CrabRobotComponent :public ICrabRobotComponent
{
public:
	// �e�̃Q�b�^�[�Z�b�^�[
	ICrabRobotComponent* GetParent()override { return m_pParent; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position)override { m_position = position; }

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRotate() const override { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate)override { m_rotate = rotate; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	bool GetSurvival() const override { return m_survival; }
	void SetSurvival(const bool& survival) override { m_survival = survival; }

	//���S��]�̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRandomRotate() const override { return m_randomRotate; }
	void SetRandomRotate(const DirectX::SimpleMath::Quaternion& killRotate)override { m_randomRotate = killRotate; }

	//�d�͂̃Q�b�^�[�A�Z�b�^�[
	float GetGravity() const override { return m_gravity; }
	void SetGravity(const float& gravity) override { m_gravity = gravity; }

	//�d�͂̃Q�b�^�[�A�Z�b�^�[
	int GetHp() const override { return m_Hp; }
	void SetHp(const int& Hp) override { m_Hp = Hp; }

	//�d�͂̃Q�b�^�[�A�Z�b�^�[
	float GetTimer() const override { return m_timer; }
	void SetTimer(const float& timer) override { m_timer = timer; }

	//���f���̃Z�b�^�[�A�Q�b�^�[
	DirectX::Model* GetPartModel()override { return m_pPartModel; }
	void SetPartModel(DirectX::Model* supplyPointModel)override { m_pPartModel = supplyPointModel; }

	//�����蔻��̃Q�b�^�[
	Collider::MultipleHitDetermination* GetCollider() override { return m_collider.get(); }

	//�q�̃p�[�c�̔z��̃Q�b�^�[
	std::vector<std::unique_ptr<ICrabRobotComponent>>& GetParts()override { return m_PlayerParts; }

	//�q�̃p�[�c�𐶐�
	void AddPart(std::unique_ptr<ICrabRobotComponent> part) override { m_PlayerParts.push_back(std::move(part)); }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	CrabRobotComponent(
		ICrabRobotComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) :
		m_pParent(parent),
		m_position(position),
		m_rotate(angle),
		m_collider(nullptr),
		m_pPartModel(nullptr),
		m_gravity(),
		m_randomRotate(),
		m_timer(),
		m_survival(true),
		m_Hp(0)
	{	//�����蔻��𐶐�
		m_collider = std::make_unique<Collider::MultipleHitDetermination>();
	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~CrabRobotComponent() override {}

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize()override {}

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">�P�t���[������</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	virtual void Update(
		const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) override {
		position; angle; elapsedTime;
	}

	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="elapsedTime">�P�t���[������</param>
	virtual void Explosion(const float& elapsedTime) override { elapsedTime; }


	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render() override {}

	/// <summary>
	/// �����蔻��̏���������
	/// </summary>
	/// <param name="respawnManager">���X�|�[���n�_�̃A�h���X</param>
	/// <param name="supplyPointManager">�A�C�e���̃A�h���X</param>
	/// <param name="enemyManager">�G�̃}�l�[�W���[�̃A�h���X</param>
	/// <param name="coinManager">�R�C���̃A�h���X</param>
	/// <param name="bulletManager">���̃A�h���X</param>
	/// <param name="objectsManager">�I�u�W�F�N�g�̃A�h���X</param>

	virtual bool CollisionBullet(Bullet* bullet)override {
		if (GetCollider()->CheckAllHit(bullet->GetCollider()))
		{
			SetHp(GetHp() - bullet->GetOffensivePower());
			return true;
		}
		for (auto& playerPart : GetParts())
		{
			// �p�[�c���X�V����
			if (playerPart->CollisionBullet(bullet))return true;
		}
		return false;
	}
	virtual bool CollisionPlayer(Player* player)override {
		
			//��܂��ȃv���C���[�ƕ��ԃp�[�c�̓����蔻��
			if (GetCollider()->CheckAllHit(player->GetCollider())) 
				//�v���C���[�̃p�[�c�Ǝ����̃p�[�c�̓����蔻��
				//for (auto& playerParts : player->GetParts())
					//if (playerParts->CollisionTurretPart(this))
					//{
						SetHp(GetHp() - player->GetOffensivePower());
						return true;
					//}
			//�p�[�c���������Ă���true
			for (auto& windmillPart : GetParts())
				if (windmillPart->CollisionPlayer(player))	return true;

			//�S�Ẵp�[�c���������ĂȂ�������false
			return false;
		
	}

	/// <summary>
	/// �㏈���������Ȃ�
	/// </summary>
	virtual void Finalize()override {}
private:


	//�v���y���̈ʒu
	DirectX::SimpleMath::Vector3 m_position;

	//�v���y���̕���
	DirectX::SimpleMath::Quaternion m_rotate;

	//����
	bool m_survival;

	//�g�o
	int m_Hp;

	//�v���y���̎��S���̃����_���ȕ����ɔ�΂���]
	DirectX::SimpleMath::Quaternion m_randomRotate;

	//�d��
	float m_gravity;

	//�v���y���̃��f��
	DirectX::Model* m_pPartModel;

	//�����蔻��̃|�C���^
	std::unique_ptr<Collider::MultipleHitDetermination> m_collider;

	//�o�ߎ���
	float m_timer;

	//�e�̃|�C���^
	ICrabRobotComponent* m_pParent;

	//�p�[�c�̔z��̃|�C���^
	std::vector<std::unique_ptr<ICrabRobotComponent>> m_PlayerParts;
};
