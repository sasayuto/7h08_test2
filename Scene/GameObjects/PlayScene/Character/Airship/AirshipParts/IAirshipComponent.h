#pragma once
#include <pch.h>
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"

class Bullet;
class Objects;
class Player;
class Enemy;
/// <summary>
/// IPlayerComponent�C���^�t�F�[�X���`����
/// </summary>
interface  IAirshipComponent
{
	// �e�̃A�h���X�̃Z�b�^�[�A�Q�b�^�[
	virtual IAirshipComponent* GetParent() = 0;
	virtual void SetParent(IAirshipComponent* parent) = 0;

	virtual std::vector<std::unique_ptr<IAirshipComponent>>& GetParts() = 0;
	virtual void AddPart(std::unique_ptr<IAirshipComponent> part) = 0;

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;

	//��]�̃Q�b�^�[�Z�b�^�[
	virtual DirectX::SimpleMath::Quaternion GetRotate() const = 0;
	virtual void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) = 0;

	//���S��]�̃Q�b�^�[�Z�b�^�[
	virtual DirectX::SimpleMath::Quaternion GetKillRotate() const = 0;
	virtual void SetKillRotate(const DirectX::SimpleMath::Quaternion& killRotate) = 0;

	//���S��]�̃Q�b�^�[�Z�b�^�[
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
	virtual ~IAirshipComponent() = default;

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize() = 0;

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
	virtual void RenderShadowTex()=0;

	/// <summary>
	/// ��������
	/// </summary>
	virtual void Explosion() = 0;

	/// <summary>
	/// ���x����������
	/// </summary>
	virtual void Speed() = 0;

	/// <summary>
	/// �����蔻��̏���������
	/// </summary>
	/// <param name="respawnManager">���X�|�[���n�_�̃A�h���X</param>
	/// <param name="supplyPointManager">�A�C�e���̃A�h���X</param>
	/// <param name="enemyManager">�G�̃}�l�[�W���[�̃A�h���X</param>
	/// <param name="coinManager">�R�C���̃A�h���X</param>
	/// <param name="bulletManager">���̃A�h���X</param>
	/// <param name="objectsManager">�I�u�W�F�N�g�̃A�h���X</param>
	/// <param name="objectsManager">�؂̃A�h���X</param>
	virtual bool Collision(Objects* objects) = 0;
	virtual bool CollisionPlayer(Player* player) = 0;
	virtual bool CollisionEnemy(Enemy* enemy) = 0;
	virtual bool CollisionBullet(Bullet* bullet) = 0;

	/// <summary>
	/// �㏈���������Ȃ�
	/// </summary>
	virtual void Finalize() = 0;
};
