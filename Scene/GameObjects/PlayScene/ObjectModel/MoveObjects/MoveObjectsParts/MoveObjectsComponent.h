#pragma once
#include <pch.h>
#include"IMoveObjectsComponent.h"

#include"Scene/GameObjects/PlayScene/Bullet/Bullet.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/Effect/SandstormEffect.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

/// <summary>
/// PlayerComponent�̃N���X���`����
/// </summary>
class MoveObjectsComponent :public IMoveObjectsComponent
{
public:
	// �e�̃Q�b�^�[�Z�b�^�[
	IMoveObjectsComponent* GetParent()override { return m_pParent; }
	void SetParent(IMoveObjectsComponent* parent) override { m_pParent = parent; }

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
	std::vector<std::unique_ptr<IMoveObjectsComponent>>& GetParts()override { return m_PlayerParts; }

	//�q�̃p�[�c�𐶐�
	void AddPart(std::unique_ptr<IMoveObjectsComponent> part) override{ m_PlayerParts.push_back(std::move(part)); }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	MoveObjectsComponent(
		IMoveObjectsComponent* parent,
		const DirectX::SimpleMath::Vector3& MODEL_POS_ADJUSTMENT,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle,
		const float& FALL_SPEED_ACCELERATION,
		const float& EXPLOSIVE_ROTATE,
		const float& EXPLOSIVE_RANDOM_POWER,
		const float& EXPLOSIVE_POWER
	) :
		m_pParent(parent),
		m_position(position),
		m_rotate(angle),
		m_collider(nullptr),
		m_pPartModel(nullptr),
		m_gravity(),
		m_survival(true),
		m_randomRotate(DirectX::SimpleMath::Quaternion::Identity),
		m_timer(0),
		FALL_SPEED_ACCELERATION(FALL_SPEED_ACCELERATION),
		EXPLOSIVE_ROTATE(EXPLOSIVE_ROTATE),
		EXPLOSIVE_RANDOM_POWER(EXPLOSIVE_RANDOM_POWER),
		EXPLOSIVE_POWER(EXPLOSIVE_POWER),
		MODEL_POS_ADJUSTMENT(MODEL_POS_ADJUSTMENT)
	{	
		//�����蔻��𐶐�
		m_collider = std::make_unique<Collider::OBB>();
	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~MoveObjectsComponent() override {}

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize()override {
		//360�x�����_���ȕ������擾
		std::random_device seed;
		std::default_random_engine engine(seed());
		std::uniform_real_distribution<> dist(0, 6.28f);
		float explosionSpeedX = static_cast<float>(dist(engine));

		//�����_���ȉ�]���Z�b�g
		SetRandomRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, explosionSpeedX));

		//�����͂������_���ɂ���
		std::uniform_real_distribution<> power(5, 10);
		float explosionPower = static_cast<float>(power(engine)) / 60;

		//�����͂��d�͂ɕt����
		SetGravity(-explosionPower);

		//�����蔻��̏�����
		GetCollider()->Initialize(
			GetPosition(),
			GetRotate(),
			GetPartModel()->meshes[0]->boundingBox.Extents
		);
		// �p�[�c���X�V����
		for (auto& playerPart : GetParts())
		{
			playerPart->Initialize();
		}
	}

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	virtual void Update(const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) override 
	{
		//�e�̈ʒu�ƍ��킹��
		m_position =  position + DirectX::SimpleMath::Vector3::Transform(MODEL_POS_ADJUSTMENT, angle);
		//�e�̉�]�ƍ��킹��
		SetRotate(angle);
		//�����蔻��̍X�V
		GetCollider()->Update(
			GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
			GetRotate()
		);

		// �p�[�c���X�V����
		for (auto& playerPart : GetParts())
		{
			if (playerPart->GetSurvival())	playerPart->Update(elapsedTime, GetPosition(), GetRotate());
			else							playerPart->Explosion(elapsedTime);
		}
	}

	/// <summary>
	/// ��������
	/// </summary>
	virtual void Explosion(const float& elapsedTime) override{
		//�A�j���[�V�����𒴂�����X�V���Ȃ�
	if (GetTimer() >= Bench::ANIMATION_TIME)
		return;

	//���Ԃ��v��
	SetTimer(GetTimer() + elapsedTime);

	DirectX::SimpleMath::Vector3 position = GetPosition();

	//�����_���ȕ���
	position += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, 0, EXPLOSIVE_RANDOM_POWER), GetRandomRotate());

	////�j�󂳂������ɔ�΂�(���˃x�N�g��)
	//position += -GetReflectionVector() * EXPLOSIVE_POWER;

	//�d�͂�����
	SetGravity(GetGravity() + FALL_SPEED_ACCELERATION);

	//�L�����W�ɏd�͂�����
	position.y -= GetGravity();

	//�����̃N�I�[�^�j�I����]
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::Identity;
	q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(EXPLOSIVE_ROTATE));
	q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(EXPLOSIVE_ROTATE));

	SetRotate(q * GetRotate());
	SetPosition(position);

	//�����蔻��̍X�V
	GetCollider()->Update(
		GetPosition(),
		GetRotate()
	);
	// �p�[�c���X�V����
	for (auto& playerPart : GetParts())
	{
		playerPart->Explosion(elapsedTime);
	}
};

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render() override {
		//�A�j���[�V�����𒴂�����`�悵�Ȃ�
		if (GetTimer() >= Bench::ANIMATION_TIME)
			return;
		//���E�ɓ����Ă��邩
		if (Draw::GetInstance()->VisibilityRange(GetPosition(), m_pPartModel->meshes[0]->boundingSphere.Radius))
			return;
		//�X�P�[�����O�A�ʒu�����A��]��������
		DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
		world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
		world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

		// ��s�@�̕`��n
		Draw::GetInstance()->ShadowMapRender(GetPartModel(), world);
		//Draw::GetInstance()->TestCubeModel(m_collider->GetExtents(),m_collider->GetPosition(),m_rotate);

		// �p�[�c���X�V����
		for (auto& playerPart : GetParts())
		{
			playerPart->Render();
		}
	}

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
		//�A�j���[�V�����𒴂�����`�悵�Ȃ�
		if (GetTimer() >= Bench::ANIMATION_TIME)
			return;

		//�X�P�[�����O�A�ʒu�����A��]��������
		DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
		DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
		DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

		world = rotate * translation;
		// ��s�@�̕`��
		Draw::GetInstance()->ShadowMapTexCreate(GetPartModel(), world);
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
			for (auto& playerParts : player->GetParts())
			{
				//���Ԃ̎����̃p�[�c�ƃv���C���[�̃p�[�c�̓����蔻��
				if (playerParts->CollisionIMoveObjectsParts(this))
				{
					//���i�����v��
					//for (auto& windmillParts : GetParts())
					//	windmillParts->CollisionPlayerParts(player);
					SetSurvival(false);
					return true;
				}
				//���Ԃ̃p�[�c��
				for (auto& windmillParts : GetParts())
					if (windmillParts->CollisionPlayer(player)) return true;
			}
			//�S�Ẵp�[�c���������ĂȂ�������false
			return false;
		}
	}
	
	virtual IMoveObjectsComponent* Collision(Enemy* enemy)override {
		if (GetCollider()->CheckHitSphere(enemy->GetCollider()))return this;
		return nullptr;
	};
	virtual IMoveObjectsComponent* Collision(Airship* airship)override {
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
	IMoveObjectsComponent* m_pParent;

	//�p�[�c�̔z��̃|�C���^
	std::vector<std::unique_ptr<IMoveObjectsComponent>> m_PlayerParts;

	//�o�ߎ���
	float m_timer;

	const float FALL_SPEED_ACCELERATION;	//�����̉����x			(m/s)
	const float EXPLOSIVE_ROTATE;	//���f���̉�]�̑���	(��/s�j
	const float EXPLOSIVE_RANDOM_POWER;		//�����̉��̃p���[		(m/s)
	const float EXPLOSIVE_POWER;		//�����̉��̃p���[		(m/s)
	const DirectX::SimpleMath::Vector3 MODEL_POS_ADJUSTMENT;
};
