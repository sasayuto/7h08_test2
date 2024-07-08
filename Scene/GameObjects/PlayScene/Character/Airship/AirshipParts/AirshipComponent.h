#pragma once
#include <pch.h>
#include"IAirshipComponent.h"

/// <summary>
/// PlayerComponent�̃N���X���`����
/// </summary>
class AirshipComponent :public IAirshipComponent
{
public:
	// �e�̃Q�b�^�[�Z�b�^�[
	IAirshipComponent* GetParent()override { return m_pParent; }
	void SetParent(IAirshipComponent* parent) override { m_pParent = parent; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position)override { m_position = position; }

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRotate() const override { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate)override { m_rotate = rotate; }

	//���S��]�̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetKillRotate() const override { return m_killrotate; }
	void SetKillRotate(const DirectX::SimpleMath::Quaternion& killRotate)override { m_killrotate = killRotate; }

	//���S��]�̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRandomRotate() const override { return m_randomRotate; }
	void SetRandomRotate(const DirectX::SimpleMath::Quaternion& killRotate)override { m_randomRotate = killRotate; }

	//�d�͂̃Q�b�^�[�A�Z�b�^�[
	float GetGravity() const override{ return m_gravity; }
	void SetGravity(const float& gravity) override{ m_gravity = gravity; }

	//���f���̃Z�b�^�[�A�Q�b�^�[
	DirectX::Model* GetPartModel()override { return m_pPartModel; }
	void SetPartModel(DirectX::Model* supplyPointModel)override { m_pPartModel = supplyPointModel; }

	//�����蔻��̃Q�b�^�[
	Collider::OBB* GetCollider() override { return m_collider.get(); }

	//�q�̃p�[�c�̃Q�b�^�[
	std::vector<std::unique_ptr<IAirshipComponent>>& GetParts()override { return m_PlayerParts; }

	//�q�̃p�[�c�𐶐�
	void AddPart(std::unique_ptr<IAirshipComponent> part) override{ m_PlayerParts.push_back(std::move(part)); }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	AirshipComponent(
		IAirshipComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) :
		m_pParent(parent),
		m_position(position),
		m_rotate(angle),
		m_collider(nullptr),
		m_pPartModel(nullptr),
		m_killrotate(DirectX::SimpleMath::Quaternion::Identity),
		m_gravity(0),
		m_randomRotate(DirectX::SimpleMath::Quaternion::Identity)
	{	//�����蔻��𐶐�
		m_collider = std::make_unique<Collider::OBB>();
	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~AirshipComponent() override {}

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize()override {}

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	virtual void Update(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) override {
		position; angle;
	}

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render() override {}

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
		Draw::GetInstance()->ShadowMapTexCreateNoPicture(GetPartModel(), world);

		//Draw::GetInstance()->TestCubeModel(
		//	GetPartModel()->meshes[0]->boundingBox.Extents, 
		//	GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		//	GetRotate()
		//);

			// �p�[�c���X�V����
		for (auto& Part : GetParts())
		{
			Part->RenderShadowTex();
		}
	};

	/// <summary>
	/// ��������
	/// </summary>
	virtual void Explosion() override {}

	/// <summary>
	/// ���x����������
	/// </summary>
	virtual void Speed() override {}

	/// <summary>
	/// �����蔻��̏���������
	/// </summary>
	/// <param name="respawnManager">���X�|�[���n�_�̃A�h���X</param>
	/// <param name="supplyPointManager">�A�C�e���̃A�h���X</param>
	/// <param name="enemyManager">�G�̃}�l�[�W���[�̃A�h���X</param>
	/// <param name="coinManager">�R�C���̃A�h���X</param>
	/// <param name="bulletManager">���̃A�h���X</param>
	/// <param name="objectsManager">�I�u�W�F�N�g�̃A�h���X</param>
	virtual bool Collision(Objects* objects) override {
		if (objects->GetCollider()->CheckHitOneOrMore(GetCollider()))return true;
		for (auto& playerPart : GetParts())
		{
			// �p�[�c���X�V����
			if (playerPart->Collision(objects))return true;
		}
		return false;
	}

	virtual bool CollisionBullet(Bullet* bullet)override {
		if (GetCollider()->CheckHitSphere(bullet->GetCollider()))
			return true;
		for (auto& playerPart : GetParts())
		{
			// �p�[�c���X�V����
			if (playerPart->CollisionBullet(bullet))
				return true;
		}
		return false;
	}

	virtual bool CollisionPlayer(Player* player)override {
		//��܂��ȃv���C���[�ƕ��ԃp�[�c�̓����蔻��
		//�������ĂȂ�������p�[�c�̔���
		if (!GetCollider()->CheckHitSphere(player->GetCollider())) {

			//�p�[�c���������Ă���true
			for (auto& airshipPart : GetParts())
				if (airshipPart->CollisionPlayer(player))
					return true;
			//�S�Ẵp�[�c���������ĂȂ�������false
			return false;
		}
		//�v���C���[�̃p�[�c�ƓG�̃p�[�c�̓����蔻��
		for (auto& playerParts : player->GetParts())
		{
			//���Ԃ̎����̃p�[�c�ƃv���C���[�̃p�[�c�̓����蔻��
			if (playerParts->CollisionAirshipParts(this))
				//���i�����v��
				//for (auto& windmillParts : GetParts())
				//	windmillParts->CollisionPlayerParts(player);
				return true;

			//���Ԃ̃p�[�c��
			for (auto& airshipPart : GetParts())
				if (airshipPart->CollisionPlayer(player)) return true;
		}
		//�S�Ẵp�[�c���������ĂȂ�������false
		return false;
	}

	virtual bool CollisionEnemy(Enemy* enemy)override
	{
		//��܂��ȃv���C���[�ƕ��ԃp�[�c�̓����蔻��
		//�������ĂȂ�������p�[�c�̔���
		if (!GetCollider()->CheckHitSphere(enemy->GetCollider())) {

			//�p�[�c���������Ă���true
			for (auto& windmillPart : GetParts())
				if (windmillPart->CollisionEnemy(enemy))
					return true;
			//�S�Ẵp�[�c���������ĂȂ�������false
			return false;
		}
		//�v���C���[�̃p�[�c�ƓG�̃p�[�c�̓����蔻��
		for (auto& enemyParts : enemy->GetParts())
		{
			//���Ԃ̎����̃p�[�c�ƃv���C���[�̃p�[�c�̓����蔻��
			if (enemyParts->CollisionAirshipParts(this))
				//���i�����v��
				//for (auto& windmillParts : GetParts())
				//	windmillParts->CollisionPlayerParts(player);
				return true;

			//���Ԃ̃p�[�c��
			for (auto& windmillParts : GetParts())
				if (windmillParts->CollisionEnemy(enemy)) return true;
		}
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

	//�v���y���̃��f��
	DirectX::Model* m_pPartModel;

	//�����蔻��̃|�C���^
	std::unique_ptr<Collider::OBB> m_collider;

	//�e�̃|�C���^
	IAirshipComponent* m_pParent;

	//�v���y���̎��S���̉�]
	DirectX::SimpleMath::Quaternion m_killrotate;

	//�v���y���̎��S���̃����_���ȕ����ɔ�΂���]
	DirectX::SimpleMath::Quaternion m_randomRotate;

	//�p�[�c�̔z��̃|�C���^
	std::vector<std::unique_ptr<IAirshipComponent>> m_PlayerParts;

	//�d��
	float m_gravity;

};
