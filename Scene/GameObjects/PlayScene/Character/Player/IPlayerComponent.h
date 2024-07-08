#pragma once
#include <pch.h>
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"

class Respawn;
class Item;
class Enemy;
class Coin;
class Bullet;
class Objects;
struct IAirshipComponent;
struct IWindmillComponent;
class Floor;
struct IStreetLightComponent;
struct IBenchComponent;
class SandstormEffect;
struct ITurretComponent;
struct IMoveObjectsComponent;
struct IHouseMoveObjectsComponent;
/// <summary>
/// IPlayerComponent�C���^�t�F�[�X���`����
/// </summary>
interface  IPlayerComponent
{
	// �e�̃A�h���X�̃Z�b�^�[�A�Q�b�^�[
	virtual IPlayerComponent* GetParent() = 0;
	virtual void SetParent(IPlayerComponent* parent) = 0;

	//�q�̃p�[�c�̔z��̃Q�b�^�[
	virtual std::vector<std::unique_ptr<IPlayerComponent>>& GetParts() = 0;
	virtual void AddPart(std::unique_ptr<IPlayerComponent> part) = 0;

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	virtual DirectX::SimpleMath::Vector3 GetProgressVector() const = 0;
	virtual void SetProgressVector(const DirectX::SimpleMath::Vector3& progressVector) = 0;

	//���˃x�N�g���̃Q�b�^�[�Z�b�^�[
	virtual void SetMove(const DirectX::SimpleMath::Vector3& reflectionVector) = 0;
	virtual DirectX::SimpleMath::Vector3 GetMove()const = 0;


	//��]�̃Q�b�^�[�Z�b�^�[
	virtual DirectX::SimpleMath::Quaternion GetRotate() const = 0;
	virtual void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) = 0;

	//���˃x�N�g���̃Q�b�^�[�Z�b�^�[
	virtual void SetReflectionVector(const DirectX::SimpleMath::Vector3& reflectionVector) = 0;
	virtual DirectX::SimpleMath::Vector3 GetReflectionVector()const = 0;

	//�����_���ȉ�]�̃Q�b�^�[�Z�b�^�[
	virtual DirectX::SimpleMath::Quaternion GetRandomRotate() const = 0;
	virtual void SetRandomRotate(const DirectX::SimpleMath::Quaternion & killRotate) = 0;

	//�d�͂̃Q�b�^�[�A�Z�b�^�[
	virtual float GetGravity() const = 0;
	virtual void SetGravity(const float& gravity) = 0;

	//���f���̃Z�b�^�[�A�Q�b�^�[
	virtual DirectX::Model* GetPartModel() = 0;
	virtual void SetPartModel(DirectX::Model* supplyPointModel) = 0;

	//�����蔻��̃Q�b�^�[
	virtual Collider::OBB* GetCollider() = 0;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~IPlayerComponent() = default;

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="angle">���˃x�N�g��</param>
	virtual void Initialize(const DirectX::SimpleMath::Vector3& reflectionVector) = 0;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	virtual void Update(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render() = 0;

		/// <summary>
	/// �V���h�E�}�b�v�p�̉摜�����
	/// </summary>
	virtual void RenderShadowTex() = 0;


	/// <summary>
	/// ��������
	/// </summary>
	virtual void Explosion() = 0;

	/// <summary>
	/// ���x����������
	/// </summary>
	virtual void Speed() = 0;


	/// <summary>
	/// �I�u�W�F�N�g�̂Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�I�u�W�F�N�g�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionObjects(Objects* objects) = 0;

	/// <summary>
	///�A�C�e���Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�A�C�e���̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionItem(Item* item) = 0;

	/// <summary>
	/// �G�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�G�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionEnemy(Enemy* enemy) = 0;

	/// <summary>
	/// �R�C���Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�R�C���̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionCoin(Coin* coin) = 0;

	/// <summary>
	/// ���Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">���̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionBullet(Bullet* bullet) = 0;

	/// <summary>
	/// ���Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">���̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionFloor(Floor* floor) = 0;

	/// <summary>
	/// �����Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�����̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionSandstorm(SandstormEffect* sandstormEffect) = 0;

	/// <summary>
	/// �G�p�[�c�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�G�p�[�c�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool Collision(IPlayerComponent* iPlayerComponent) = 0;

	/// <summary>
	/// ��s�D�̃p�[�c�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">��s�D�̃p�[�c�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionAirshipParts(IAirshipComponent* iAirshipComponent) = 0;

	/// <summary>
	/// ���Ԃ̃p�[�c�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">���Ԃ̃p�[�c�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionWindmillParts(IWindmillComponent* HitAirshipPart) = 0;

	/// <summary>
	/// �X���̃p�[�c�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�X���̃p�[�c�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionStreetLightParts(IStreetLightComponent* iStreetLightComponent) = 0;

	/// <summary>
	/// �x���`�̃p�[�c�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�x���`�̃p�[�c�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionBenchParts(IBenchComponent* iBenchComponent) = 0;

	/// <summary>
	/// �j��I�u�W�F�N�g�̃p�[�c�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�x���`�̃p�[�c�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionIMoveObjectsParts(IMoveObjectsComponent* iMoveObjectsComponent) = 0;

	/// <summary>
	/// �j��I�u�W�F�N�g�̃p�[�c�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�x���`�̃p�[�c�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionIHouseMoveObjectsParts(IHouseMoveObjectsComponent* iHouseMoveObjectsComponent) = 0;

	/// <summary>
	/// �^���b�g�̃p�[�c�Ƃ̓����蔻��
	/// </summary>
	/// <param name="objects">�^���b�g�̃p�[�c�̃A�h���X</param>
	/// <returns>Hit��true</returns>
	virtual bool CollisionTurretPart(ITurretComponent* iTurretComponent) = 0;

	/// <summary>
	/// �㏈���������Ȃ�
	/// </summary>
	virtual void Finalize() = 0;
};
