#pragma once
#include <pch.h>
#include"IBenchComponent.h"

#include"Scene/GameObjects/PlayScene/Bullet/Bullet.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/Effect/SandstormEffect.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

/// <summary>
/// PlayerComponent�̃N���X���`����
/// </summary>
class BenchComponent :public IBenchComponent
{
public:
	// �e�̃Q�b�^�[�Z�b�^�[
	IBenchComponent* GetParent()override { return m_pParent; }
	void SetParent(IBenchComponent* parent) override { m_pParent = parent; }

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
	float GetTimer() const override { return m_timer; }
	void SetTimer(const float& timer) override { m_timer = timer; }

	//���f���̃Z�b�^�[�A�Q�b�^�[
	DirectX::Model* GetPartModel()override { return m_pPartModel; }
	void SetPartModel(DirectX::Model* supplyPointModel)override { m_pPartModel = supplyPointModel; }

	//�����蔻��̃Q�b�^�[
	Collider::OBB* GetCollider() override { return m_collider.get(); }

	//�q�̃p�[�c�̃Q�b�^�[
	std::vector<std::unique_ptr<IBenchComponent>>& GetParts()override { return m_PlayerParts; }

	//�q�̃p�[�c�𐶐�
	void AddPart(std::unique_ptr<IBenchComponent> part) override{ m_PlayerParts.push_back(std::move(part)); }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	BenchComponent(
		IBenchComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) :
		m_pParent(parent),
		m_position(position),
		m_rotate(angle),
		m_collider(nullptr),
		m_pPartModel(nullptr),
		m_gravity(),
		m_survival(true),
		m_randomRotate(DirectX::SimpleMath::Quaternion::Identity),
		m_timer(0)
	{	//�����蔻��𐶐�
		m_collider = std::make_unique<Collider::OBB>();
	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~BenchComponent() override {}

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize()override {}

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	virtual void Update(const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) override {
		position; angle;
	}

	/// <summary>
	/// ��������
	/// </summary>
	virtual void Explosion(const float& elapsedTime) override{};

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render() override {}

	virtual bool SurvivalCheck() {
		if (!m_survival)
			return false;

		for (auto& parts : m_PlayerParts)
			if (!parts->SurvivalCheck())
				return false;

		return true;

	};

	/// <summary>
	/// �V���h�E�}�b�v�p�̉摜�����
	/// </summary>
	virtual void RenderShadowTex() override {
		//�X�P�[�����O�A�ʒu�����A��]��������
		DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
		DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
		DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

		world = rotate * translation;
		// ��s�@�̕`��
		Draw::GetInstance()->ShadowMapTexCreate(GetPartModel(), world);

		//Draw::GetInstance()->TestCubeModel(
		//	GetPartModel()->meshes[0]->boundingBox.Extents, 
		//	GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		//	GetRotate()
		//);

			// �p�[�c���X�V����
		for (auto& playerPart : GetParts())
		{
			playerPart->RenderShadowTex();
		}
	};

	/// <summary>
	/// �����蔻��̏���������
	/// </summary>
	/// <param name="respawnManager">���X�|�[���n�_�̃A�h���X</param>
	/// <param name="supplyPointManager">�A�C�e���̃A�h���X</param>
	/// <param name="enemyManager">�G�̃}�l�[�W���[�̃A�h���X</param>
	/// <param name="coinManager">�R�C���̃A�h���X</param>
	/// <param name="bulletManager">���̃A�h���X</param>
	/// <param name="objectsManager">�I�u�W�F�N�g�̃A�h���X</param>
	virtual bool CollisionPlayer(Player* player)override {
		{
			//��܂��ȃv���C���[�ƕ��ԃp�[�c�̓����蔻��
			//�������ĂȂ�������p�[�c�̔���
			if (!GetCollider()->CheckHitSphere(player->GetCollider())) {

				//�p�[�c���������Ă���true
				for (auto& windmillPart : GetParts())
					if (windmillPart->CollisionPlayer(player))
						return true;

				//�S�Ẵp�[�c���������ĂȂ�������false
				return false;
			}

			//�v���C���[�̃p�[�c�ƓG�̃p�[�c�̓����蔻��
			for (auto& playerParts : player->GetPlayerParts())
			{
				//���Ԃ̎����̃p�[�c�ƃv���C���[�̃p�[�c�̓����蔻��
				if (playerParts->CollisionBenchParts(this))
					//���i�����v��
					//for (auto& windmillParts : GetParts())
					//	windmillParts->CollisionPlayerParts(player);
					SetSurvival(false);
					return true;

				//���Ԃ̃p�[�c��
				for (auto& windmillParts : GetParts())
					if (windmillParts->CollisionPlayer(player)) return true;
			}
			//�S�Ẵp�[�c���������ĂȂ�������false
			return false;
		}
	}
	
	virtual IBenchComponent* Collision(Enemy* enemy)override {
		if (GetCollider()->CheckHitSphere(enemy->GetCollider()))return this;
		return nullptr;
	};
	virtual IBenchComponent* Collision(Airship* airship)override {
		if (GetCollider()->CheckHitSphere(airship->GetCollider()))return this;
		return nullptr;

	};
	virtual bool Collision(Bullet* bullet)override {
		if (GetCollider()->CheckHitSphere(bullet->GetCollider()))
		{
			SetSurvival(false);
			SetGravity(-0.1f);
			return true;
		}
		for (auto& streetLightParts : GetParts())
		{
			if (streetLightParts->Collision(bullet))
				return true;
		}
		return false;
	}
	virtual bool CollisionSandstorm(SandstormEffect* sandstormEffect)
	{
		if (GetCollider()->CheckHitOBBBox(sandstormEffect->GetCollider()))
		{
			SetSurvival(false);
			SetGravity(-0.1f);
			for (auto& streetLightParts : GetParts())
				streetLightParts->CollisionSandstorm(sandstormEffect);

			return true;
		}
		for (auto& streetLightParts : GetParts())
		{
			if (streetLightParts->CollisionSandstorm(sandstormEffect))
				return true;
		}
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

	//�v���y���̎��S���̃����_���ȕ����ɔ�΂���]
	DirectX::SimpleMath::Quaternion m_randomRotate;

	//�d��
	float m_gravity;

	//�v���y���̃��f��
	DirectX::Model* m_pPartModel;

	//�����蔻��̃|�C���^
	std::unique_ptr<Collider::OBB> m_collider;

	//�e�̃|�C���^
	IBenchComponent* m_pParent;

	//�p�[�c�̔z��̃|�C���^
	std::vector<std::unique_ptr<IBenchComponent>> m_PlayerParts;

	//�o�ߎ���
	float m_timer;

};
