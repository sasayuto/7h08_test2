#pragma once
#include <pch.h>
#include"IPlayerComponent.h"

#include"Scene/GameObjects/PlayScene/Ground/Floor/Floor.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/AirshipParts/IAirshipComponent.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Windmill/WindmillParts/IWindmillComponent.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/StreetLight/StreetLightParts/IStreetLightComponent.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Bench/BenchParts/IBenchComponent.h"
#include"Scene/GameObjects/PlayScene/Character/Turret/TurrretParts/ITurretComponent.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/HouseMoveObjects/IHouseMoveObjectsComponent.h"
#include"Scene/GameObjects/PlayScene/Effect/SandstormEffect.h"
/// <summary>
/// PlayerComponent�̃N���X���`����
/// </summary>
class  PlayerComponent :public IPlayerComponent
{
public:
	// �e�̃Q�b�^�[�Z�b�^�[
	IPlayerComponent* GetParent()override { return m_pParent; }
	void SetParent(IPlayerComponent* parent) override { m_pParent = parent; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position)override { m_position = position; }

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRotate() const override { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate)override { m_rotate = rotate; }

	//���˃x�N�g���̃Q�b�^�[�Z�b�^�[
	void SetReflectionVector(const DirectX::SimpleMath::Vector3& reflectionVector)override { m_reflectionVector = reflectionVector; }
	DirectX::SimpleMath::Vector3 GetReflectionVector()const override { return m_reflectionVector; }

	//���˃x�N�g���̃Q�b�^�[�Z�b�^�[
	void SetMove(const DirectX::SimpleMath::Vector3& move)override { m_move = move; }
	DirectX::SimpleMath::Vector3 GetMove()const override { return m_move; }

	//���S��]�̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRandomRotate() const override { return m_randomRotate; }
	void SetRandomRotate(const DirectX::SimpleMath::Quaternion& killRotate)override { m_randomRotate = killRotate; }

	//�d�͂̃Q�b�^�[�A�Z�b�^�[
	float GetGravity() const override{ return m_gravity; }
	void SetGravity(const float& gravity) override{ m_gravity = gravity; }

	//���f���̃Z�b�^�[�A�Q�b�^�[
	DirectX::Model* GetPartModel()override { return m_pPartModel; }
	void SetPartModel(DirectX::Model* supplyPointModel)override { m_pPartModel = supplyPointModel; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	virtual DirectX::SimpleMath::Vector3 GetProgressVector() const override { return m_progressVector; };
	virtual void SetProgressVector(const DirectX::SimpleMath::Vector3& progressVector) override { m_progressVector = progressVector; };

	//�����蔻��̃Q�b�^�[
	Collider::OBB* GetCollider() override { return m_collider.get(); }

	//�q�̃p�[�c�̃Q�b�^�[
	std::vector<std::unique_ptr<IPlayerComponent>>& GetParts()override { return m_PlayerParts; }

	//�q�̃p�[�c�𐶐�
	void AddPart(std::unique_ptr<IPlayerComponent> part) override{ m_PlayerParts.push_back(std::move(part)); }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	PlayerComponent(
		IPlayerComponent* parent,
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
		m_randomRotate(DirectX::SimpleMath::Quaternion::Identity),
		m_reflectionVector(),
		m_progressVector(DirectX::SimpleMath::Vector3::Zero),
		m_move()
	{	//�����蔻��𐶐�
		m_collider = std::make_unique<Collider::OBB>();
	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~PlayerComponent() override {}

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="angle">���˃x�N�g��</param>
	virtual void Initialize(const DirectX::SimpleMath::Vector3& reflectionVector)override { reflectionVector; }

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
	/// ��������
	/// </summary>
	virtual void Explosion() override {}

	/// <summary>
	/// ���x����������
	/// </summary>
	virtual void Speed() override {}

	/// <summary>
	/// �I�u�W�F�N�g�̂Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�I�u�W�F�N�g�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionObjects(Objects* objects) override {
		//�������Ă����甽�˃x�N�g����Ԃ�
		DirectX::SimpleMath::Vector3 reflectionVector = objects->GetCollider()->CheckHitreflectionVector(GetCollider(), GetMove());
		if (reflectionVector != DirectX::SimpleMath::Vector3::Zero)
		{
			//�����Γ��������p�[�c�̌�̃p�[�c�̔�����s���Ă���邪
			//���񂾂Ƃ��Ƀp�[�c���΂炯���˃x�N�g���ɂƂю����͓�����Ȃ��̂Ŋ���
			// ���̃v���C���[�̓����蔻������l
			for (auto& playerPart : GetParts())
				playerPart->CollisionObjects(objects);

			//�܂��������蔽�˃x�N�g�����Ƃ�Ȃ��̂Ŕ��Ε����ɔ�΂�
			reflectionVector = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ, GetRotate());
			SetReflectionVector(-reflectionVector * 2);
			SetGravity(-0.1f);
			return true;
		}

		for (auto& playerPart : GetParts())
		{
			// �p�[�c���X�V����
			if (playerPart->CollisionObjects(objects))
				return true;
		}
		return false;
	}

	/// <summary>
	///�A�C�e���Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�A�C�e���̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionItem(Item* item)override {
		if (GetCollider()->CheckHitSphere(item->GetCollider()))return true;
		for (auto& playerPart : GetParts())
		{
			// �p�[�c���X�V����
			if (playerPart->CollisionItem(item)) return true;
		}
		return false;
	}

	/// <summary>
	/// �G�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�G�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionEnemy(Enemy* enemy) override {
		if (GetCollider()->CheckHitSphere(enemy->GetCollider()))return true;
		for (auto& playerPart : GetParts())
		{
			// �p�[�c���X�V����
			if (playerPart->CollisionEnemy(enemy)) return true;
		}
		return false;
	}

	/// <summary>
	/// �����Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�����̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionSandstorm(SandstormEffect* sandstormEffect)
	{
		if (GetCollider()->CheckHitOBBBox(sandstormEffect->GetCollider()))
		{
			SetGravity(-0.1f);
			//�펞�G��Ă��邱�Ƃ�����̂�1�̃p�[�c���������Ă����̃p�[�c�̓����蔻����Ƃ�
			for (auto& playerPart : GetParts())
				// �p�[�c���X�V����
				playerPart->CollisionSandstorm(sandstormEffect);
			return true;
		}
		for (auto& playerPart : GetParts())
			// �p�[�c���X�V����
			if (playerPart->CollisionSandstorm(sandstormEffect)) return true;
		return false;
	}



	/// <summary>
	/// �R�C���Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�R�C���̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionCoin(Coin* coin)override {
		if (GetCollider()->CheckHitSphere(coin->GetCollider()))return true;
		for (auto& playerPart : GetParts())
		{
			// �p�[�c���X�V����
			if (playerPart->CollisionCoin(coin)) return true;
		}
		return false;
	}

	/// <summary>
	/// ���Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">���̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionBullet(Bullet* bullet)override {
		if (GetCollider()->CheckHitSphere(bullet->GetCollider()))
		{
			SetGravity(-0.1f);
			return true;
		}for (auto& playerPart : GetParts())
		{
			// �p�[�c���X�V����
			if (playerPart->CollisionBullet(bullet)) return true;
		}
		return false;
	}

	/// <summary>
	/// �G�p�[�c�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�G�p�[�c�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool Collision(IPlayerComponent* iPlayerComponent)override
	{
		if (GetCollider()->CheckHitOBB(iPlayerComponent->GetCollider()))return true;
		for (auto& playerPart : GetParts())
		{
			// �p�[�c���X�V����
			if (playerPart->Collision(iPlayerComponent)) return true;
		}
		return false;

	}

	/// <summary>
	/// ��s�D�̃p�[�c�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">��s�D�̃p�[�c�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionAirshipParts(IAirshipComponent* iAirshipComponent)override
	{
		//�������Ă����甽�˃x�N�g����Ԃ�
		DirectX::SimpleMath::Vector3 reflectionVector = iAirshipComponent->GetCollider()->CheckHitreflectionVector(GetCollider());
		if (reflectionVector != DirectX::SimpleMath::Vector3::Zero)
		{
			////���񂾂Ƃ��Ƀp�[�c���΂炯�邪���˃x�N�g���ɂƂю����͓�����Ȃ��̂Ŋ���
			//for (auto& playerPart : GetParts())
			//	// �p�[�c���X�V����
			//	playerPart->Collision(iWindmillComponent);

			//�܂��������蔽�˃x�N�g�����Ƃ�Ȃ��̂Ŕ��Ε����ɔ�΂�
			reflectionVector = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ, GetRotate());
			SetReflectionVector(-reflectionVector * 2);
			SetGravity(-0.1f);
			return true;
		}
		for (auto& playerPart : GetParts())
		{
			// �p�[�c���X�V����
			if (playerPart->CollisionAirshipParts(iAirshipComponent)) return true;
		}
		return false;
	}

	/// <summary>
	/// ���Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">���̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionFloor(Floor* floor)
	{
		if (GetCollider()->CheckHitOBB(floor->GetCollider()))
		{
			SetGravity(-0.1f);

			return true;
		}
		for (auto& playerPart : GetParts())
		{
			// �p�[�c���X�V����
			if (playerPart->CollisionFloor(floor)) return true;
		}
		return false;
	}

	/// <summary>
	/// ���Ԃ̃p�[�c�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">���Ԃ̃p�[�c�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionWindmillParts(IWindmillComponent* iWindmillComponent)
	{
		//�������Ă����甽�˃x�N�g����Ԃ�
		DirectX::SimpleMath::Vector3 reflectionVector = iWindmillComponent->GetCollider()->CheckHitreflectionVector(GetCollider());
		if (reflectionVector != DirectX::SimpleMath::Vector3::Zero)
		{
			//�܂��������蔽�˃x�N�g�����Ƃ�Ȃ��̂Ŕ��Ε����ɔ�΂�
			reflectionVector = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ, GetRotate());
			SetReflectionVector(-reflectionVector * 2);
			SetGravity(-0.1f);
			return true;
		}
		for (auto& playerPart : GetParts())
		{
			// �p�[�c���X�V����
			if (playerPart->CollisionWindmillParts(iWindmillComponent)) return true;
		}
		return false;

	}

	/// <summary>
	/// �X���̃p�[�c�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�X���̃p�[�c�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionStreetLightParts(IStreetLightComponent* iStreetLightComponent)
	{
		if (iStreetLightComponent->GetCollider()->CheckHitOBB(GetCollider()))
			return true;

		for (auto& playerPart : GetParts())
			// �p�[�c���X�V����
			if (playerPart->CollisionStreetLightParts(iStreetLightComponent))
				return true;

		return false;
	}

	virtual bool CollisionIHouseMoveObjectsParts(IHouseMoveObjectsComponent* iHouseMoveObjectsComponent)
	{
		//�������Ă����甽�˃x�N�g����Ԃ�
		DirectX::SimpleMath::Vector3 reflectionVector = iHouseMoveObjectsComponent->GetCollider()->CheckHitreflectionVector(GetCollider(),m_move);
		if (reflectionVector != DirectX::SimpleMath::Vector3::Zero)
		{
			for (auto& playerPart : GetParts())
				// �p�[�c���X�V����
				playerPart->CollisionIHouseMoveObjectsParts(iHouseMoveObjectsComponent);

			//�܂��������蔽�˃x�N�g�����Ƃ�Ȃ��̂Ŕ��Ε����ɔ�΂�
			reflectionVector = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ, GetRotate());
			SetReflectionVector(-reflectionVector * 2);
			SetGravity(-0.1f);
			return true;
		}
		for (auto& playerPart : GetParts())
			// �p�[�c���X�V����
			if (playerPart->CollisionIHouseMoveObjectsParts(iHouseMoveObjectsComponent))
				return true;

		return false;
	}

	/// <summary>
	/// �x���`�̃p�[�c�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�x���`�̃p�[�c�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionBenchParts(IBenchComponent* iBenchComponent)
	{
		if (iBenchComponent->GetCollider()->CheckHitOBB(GetCollider()))
			return true;

		for (auto& playerPart : GetParts())
			// �p�[�c���X�V����
			if (playerPart->CollisionBenchParts(iBenchComponent))
				return true;

		return false;
	}
	/// <summary>
	/// �j��I�u�W�F�N�g�̃p�[�c�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�x���`�̃p�[�c�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionIMoveObjectsParts(IMoveObjectsComponent* iMoveObjectsComponent)
	{
		if (iMoveObjectsComponent->GetCollider()->CheckHitOBB(GetCollider()))
			return true;

		for (auto& playerPart : GetParts())
			// �p�[�c���X�V����
			if (playerPart->CollisionIMoveObjectsParts(iMoveObjectsComponent))
				return true;

		return false;

	}

	/// <summary>
	/// �^���b�g�̃p�[�c�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�^���b�g�̃p�[�c�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionTurretPart(ITurretComponent* iTurretComponent)
	{
		if (iTurretComponent->GetCollider()->CheckAllHit(GetCollider()))
		{
			SetGravity(-0.1f);
			for (auto& playerPart : GetParts())
				// �p�[�c���X�V����
				playerPart->CollisionTurretPart(iTurretComponent);

			return true;
		}

		for (auto& playerPart : GetParts())
			// �p�[�c���X�V����
			if (playerPart->CollisionTurretPart(iTurretComponent))
				return true;

		return false;
	}

	/// <summary>
	/// �㏈���������Ȃ�
	/// </summary>
	virtual void Finalize()override {}
private:
	//�v���y���̈ʒu
	DirectX::SimpleMath::Vector3 m_position;
	
	//�v���y���̈ʒu
	DirectX::SimpleMath::Vector3 m_progressVector;

	//�v���y���̕���
	DirectX::SimpleMath::Quaternion m_rotate;

	//�v���y���̃��f��
	DirectX::Model* m_pPartModel;

	//�����蔻��̃|�C���^
	std::unique_ptr<Collider::OBB> m_collider;

	//�e�̃|�C���^
	IPlayerComponent* m_pParent;

	//�v���y���̎��S���̉�]
	DirectX::SimpleMath::Quaternion m_killrotate;

	//�v���y���̎��S���̃����_���ȕ����ɔ�΂���]
	DirectX::SimpleMath::Quaternion m_randomRotate;

	//�d��
	float m_gravity;

	//�p�[�c�̔z��̃|�C���^
	std::vector<std::unique_ptr<IPlayerComponent>> m_PlayerParts;

	//���˃x�N�g��
	DirectX::SimpleMath::Vector3 m_reflectionVector;

	//���˃x�N�g��
	DirectX::SimpleMath::Vector3 m_move;
};
