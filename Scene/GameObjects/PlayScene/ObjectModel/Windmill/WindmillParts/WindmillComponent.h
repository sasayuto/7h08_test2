#pragma once
#include <pch.h>
#include"IWindmillComponent.h"

#include"Scene/GameObjects/PlayScene/Bullet/Bullet.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"

/// <summary>
/// PlayerComponent�̃N���X���`����
/// </summary>
class WindmillComponent :public IWindmillComponent
{
public:
	// �e�̃Q�b�^�[�Z�b�^�[
	IWindmillComponent* GetParent()override { return m_pParent; }
	void SetParent(IWindmillComponent* parent) override { m_pParent = parent; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position)override { m_position = position; }

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRotate() const override { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate)override { m_rotate = rotate; }

	//���f���̃Z�b�^�[�A�Q�b�^�[
	DirectX::Model* GetPartModel()override { return m_pPartModel; }
	void SetPartModel(DirectX::Model* supplyPointModel)override { m_pPartModel = supplyPointModel; }

	//�����蔻��̃Q�b�^�[
	Collider::OBB* GetCollider() override { return m_collider.get(); }

	//�q�̃p�[�c�̃Q�b�^�[
	std::vector<std::unique_ptr<IWindmillComponent>>& GetParts()override { return m_PlayerParts; }

	//�q�̃p�[�c�𐶐�
	void AddPart(std::unique_ptr<IWindmillComponent> part) override { m_PlayerParts.push_back(std::move(part)); }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	WindmillComponent(
		IWindmillComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) :
		m_pParent(parent),
		m_position(position),
		m_rotate(angle),
		m_collider(nullptr),
		m_pPartModel(nullptr)
	{	//�����蔻��𐶐�
		m_collider = std::make_unique<Collider::OBB>();
	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~WindmillComponent() override {}

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
	virtual IWindmillComponent* Collision(Player* player)override {
		if (GetCollider()->CheckHitSphere(player->GetCollider()))return this;
		for (auto& windmillPart : GetParts())
		{
			// �p�[�c���X�V����
			IWindmillComponent* HitPrats = windmillPart->Collision(player);
			if (HitPrats)
				return HitPrats;
		}
		return nullptr;
	}

	virtual IWindmillComponent* Collision(Airship* airship)override {
		if (GetCollider()->CheckHitSphere(airship->GetCollider()))return this;
		for (auto& windmillPart : GetParts())
		{
			// �p�[�c���X�V����
			IWindmillComponent* HitPrats = windmillPart->Collision(airship);
			if (HitPrats)
				return HitPrats;
		}
		return nullptr;

	};
	virtual bool Collision(Bullet* bullet)override {
		if (GetCollider()->CheckHitSphere(bullet->GetCollider()))return true;
		for (auto& playerPart : GetParts())
		{
			// �p�[�c���X�V����
			if (playerPart->Collision(bullet))return true;
		}
		return false;
	}
	virtual bool CollisionPlayer(Player* player)override
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
			if (playerParts->CollisionWindmillParts(this))
				//���i�����v��
				//for (auto& windmillParts : GetParts())
				//	windmillParts->CollisionPlayerParts(player);
				return true;

			//���Ԃ̃p�[�c��
			for (auto& windmillParts : GetParts())
				if (windmillParts->CollisionPlayer(player)) return true;
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
		for (auto& playerParts : enemy->GetParts())
		{
			//���Ԃ̎����̃p�[�c�ƃv���C���[�̃p�[�c�̓����蔻��
			if (playerParts->CollisionWindmillParts(this))
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
	IWindmillComponent* m_pParent;

	//�p�[�c�̔z��̃|�C���^
	std::vector<std::unique_ptr<IWindmillComponent>> m_PlayerParts;
};
