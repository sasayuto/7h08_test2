#pragma once
#include <pch.h>
#include"IHouseMoveObjectsComponent.h"

#include"Scene/GameObjects/PlayScene/Bullet/Bullet.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/Effect/SandstormEffect.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

/// <summary>
/// PlayerComponent�̃N���X���`����
/// </summary>
class HouseMoveObjectsComponent :public IHouseMoveObjectsComponent
{
public:
	// �e�̃Q�b�^�[�Z�b�^�[
	IHouseMoveObjectsComponent* GetParent()override { return m_pParent; }
	void SetParent(IHouseMoveObjectsComponent* parent) override { m_pParent = parent; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position)override { m_position = position; }

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRotate() const override { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate)override { m_rotate = rotate; }

	//��]�̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetInitialRotate() const override { return m_initialRotate; }
	void SetInitialRotate(const DirectX::SimpleMath::Quaternion& rotate)override { m_initialRotate = rotate; }

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
	Collider::MultipleHitDetermination* GetCollider() override { return m_collider.get(); }

	//�q�̃p�[�c�̃Q�b�^�[
	std::vector<std::unique_ptr<IHouseMoveObjectsComponent>>& GetParts()override { return m_PlayerParts; }

	//�q�̃p�[�c�𐶐�
	void AddPart(std::unique_ptr<IHouseMoveObjectsComponent> part) override{ m_PlayerParts.push_back(std::move(part)); }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	HouseMoveObjectsComponent(
		IHouseMoveObjectsComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle,
		const float& FALL_SPEED_ACCELERATION,
		const float& EXPLOSIVE_ROTATE,
		const float& EXPLOSIVE_RANDOM_POWER,
		const float& EXPLOSIVE_POWER,
		PartListObj& partsModel
	) :
		m_pParent(parent),
		m_position(position),
		m_rotate(DirectX::SimpleMath::Quaternion::Identity),
		m_initialRotate(angle),
		m_collider(nullptr),
		m_pPartModel(partsModel.model),
		m_gravity(),
		m_survival(true),
		m_randomRotate(DirectX::SimpleMath::Quaternion::Identity),
		m_timer(0),
		FALL_SPEED_ACCELERATION(FALL_SPEED_ACCELERATION),
		EXPLOSIVE_ROTATE(EXPLOSIVE_ROTATE),
		EXPLOSIVE_RANDOM_POWER(EXPLOSIVE_RANDOM_POWER),
		EXPLOSIVE_POWER(EXPLOSIVE_POWER),
		MODEL_POS_ADJUSTMENT(partsModel.model->meshes[0]->boundingBox.Center)
	{	
		for (auto& parts : partsModel.childrenParts)
		{
			std::unique_ptr<IHouseMoveObjectsComponent> part = std::make_unique<HouseMoveObjectsComponent>(
				nullptr,
				m_position,
				m_rotate * m_initialRotate,
				FALL_SPEED_ACCELERATION,
				EXPLOSIVE_ROTATE,
				EXPLOSIVE_RANDOM_POWER,
				EXPLOSIVE_POWER,
				parts
			);
			AddPart(std::move(part));
		}
		m_roughCollider = std::move(partsModel.colSphere);
		//�����蔻��𐶐�
		m_collider = std::move(partsModel.col);
		//m_collider = std::make_unique<Collider::OBB>();

		m_normalMap = std::move(partsModel.normalMap);

	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~HouseMoveObjectsComponent() override {}

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
		//GetCollider()->Initialize(
		//	GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		//	GetRotate(),
		//	GetPartModel()->meshes[0]->boundingBox.Extents
		//); 
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
		angle;
		position;
		////�e�̈ʒu�ƍ��킹��
		//m_position =  position + DirectX::SimpleMath::Vector3::Transform(MODEL_POS_ADJUSTMENT, angle);
		////�e�̉�]�ƍ��킹��
		//SetRotate(angle);
		////�����蔻��̍X�V
		//GetCollider()->Update(
		//	GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		//	GetRotate()
		//);
		//GetCollider()->AllUpdate(GetPosition()+ MODEL_POS_ADJUSTMENT, GetRotate());

		//m_roughCollider->SetPosition(GetPosition() + DirectX::SimpleMath::Vector3::Transform(MODEL_POS_ADJUSTMENT, m_initialRotate));
		//GetCollider()->AllUpdate(GetPosition() + DirectX::SimpleMath::Vector3::Transform(MODEL_POS_ADJUSTMENT, m_initialRotate), GetRotate() * m_initialRotate);

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
	virtual void Explosion(const float& elapsedTime) override
	{
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
		//GetCollider()->Update(
		//	GetPosition() +DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center),
		//	GetRotate()
		//);
		m_roughCollider->SetPosition(GetPosition() + DirectX::SimpleMath::Vector3::Transform(MODEL_POS_ADJUSTMENT, m_initialRotate));
		GetCollider()->AllUpdate(GetPosition() + DirectX::SimpleMath::Vector3::Transform(MODEL_POS_ADJUSTMENT,m_initialRotate), GetRotate() * m_initialRotate);
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
		world *= DirectX::SimpleMath::Matrix::CreateTranslation(-MODEL_POS_ADJUSTMENT);
		world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate()* m_initialRotate);
		world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition() + DirectX::SimpleMath::Vector3::Transform(MODEL_POS_ADJUSTMENT,  m_initialRotate));

		// ��s�@�̕`��
		if (m_normalMap)
		{
			Draw::GetInstance()->ShadowMapRender(GetPartModel(), world, m_normalMap, []() {
				// �J�����O�͍�����
				SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext()->RSSetState(
					SingletonDeviceResources::GetInstance()->GetCommonStates()->CullNone()
				);
				});
		}
		else
		{
			Draw::GetInstance()->ShadowMapRender(GetPartModel(), world, []() {
				// �J�����O�͍�����
				SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext()->RSSetState(
					SingletonDeviceResources::GetInstance()->GetCommonStates()->CullNone()
				);
				});
		}
		//Draw::GetInstance()->TestSphereModel(m_roughCollider->GetRadius(), m_roughCollider->GetPosition());
		//GetCollider()->Render(GetRotate());

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
		world *= DirectX::SimpleMath::Matrix::CreateTranslation(-MODEL_POS_ADJUSTMENT);
		world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate() * m_initialRotate);
		world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition() + DirectX::SimpleMath::Vector3::Transform(MODEL_POS_ADJUSTMENT,  m_initialRotate));
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
			if (!m_roughCollider->CheckHitSphere(player->GetCollider()))
			{
				for (auto& streetLightParts : GetParts())
					if (streetLightParts->CollisionPlayer(player))
						return true;

				return false;

			}


			if (!GetCollider()->CheckHitOneOrMore(player->GetCollider())) {

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
				if (playerParts->CollisionIHouseMoveObjectsParts(this))
				{
					//�v���C���[�̂ق��œ����蔻��Ƃ肽���Ȃ�
					////���i�����v��
					for (auto& windmillParts : GetParts())
						windmillParts->CollisionPlayer(player);

					return true;
				}
				//���Ԃ̃p�[�c��
				for (auto& windmillParts : GetParts())
					if (windmillParts->CollisionPlayer(player)) 
						return true;
			}
			//�S�Ẵp�[�c���������ĂȂ�������false
			return false;
		}
	}
	
	virtual IHouseMoveObjectsComponent* Collision(Enemy* enemy)override {
		if (GetCollider()->CheckHitOneOrMore(enemy->GetCollider()))return this;
		return nullptr;
	};
	virtual IHouseMoveObjectsComponent* Collision(Airship* airship)override {
		if (GetCollider()->CheckHitOneOrMore(airship->GetCollider()))return this;
		return nullptr;

	};
	virtual bool Collision(Bullet* bullet)override {
		if (!m_roughCollider->CheckHitSphere(bullet->GetCollider()))
		{
			for (auto& streetLightParts : GetParts())
				if (streetLightParts->Collision(bullet))
					return true;

			return false;

		}

		if (GetCollider()->CheckHitOneOrMore(bullet->GetCollider()))
		{
			SetSurvival(false);
			SetGravity(-0.1f);
			return true;
		}
		for (auto& streetLightParts : GetParts())
			if (streetLightParts->Collision(bullet))
				return true;
		return false;
	}
	virtual bool CollisionSandstorm(SandstormEffect* sandstormEffect)
	{
		//if (!m_roughCollider->CheckHitSphereBox(sandstormEffect->GetCollider()));
			//for (auto& streetLightParts : GetParts())
			//{
			//	if (streetLightParts->Collision(sandstormEffect))
			//		return true;

			//	return false;
			//}

		if (GetCollider()->CheckHitOneOrMore(sandstormEffect->GetCollider()))
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

	//�v���y���̕���
	DirectX::SimpleMath::Quaternion m_initialRotate;

	//����
	bool m_survival;

	//�v���y���̎��S���̃����_���ȕ����ɔ�΂���]
	DirectX::SimpleMath::Quaternion m_randomRotate;

	//�d��
	float m_gravity;

	//�v���y���̃��f��
	DirectX::Model* m_pPartModel;

	//�����蔻��̃|�C���^
	std::unique_ptr<Collider::MultipleHitDetermination> m_collider;
	//��܂��ȓ����蔻��̃|�C���^
	std::unique_ptr<Collider::Sphere> m_roughCollider;

	//�e�̃|�C���^
	IHouseMoveObjectsComponent* m_pParent;

	//�p�[�c�̔z��̃|�C���^
	std::vector<std::unique_ptr<IHouseMoveObjectsComponent>> m_PlayerParts;

	//normal�}�b�v�̃e�N�X�`��
	ID3D11ShaderResourceView* m_normalMap;

	//�o�ߎ���
	float m_timer;

	const float FALL_SPEED_ACCELERATION;	//�����̉����x			(m/s)
	const float EXPLOSIVE_ROTATE;	//���f���̉�]�̑���	(��/s�j
	const float EXPLOSIVE_RANDOM_POWER;		//�����̉��̃p���[		(m/s)
	const float EXPLOSIVE_POWER;		//�����̉��̃p���[		(m/s)
	const DirectX::SimpleMath::Vector3 MODEL_POS_ADJUSTMENT;
};
