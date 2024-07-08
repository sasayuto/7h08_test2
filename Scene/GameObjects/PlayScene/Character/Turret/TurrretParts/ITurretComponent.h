#pragma once
#include <pch.h>
#include"Scene/GameObjects/PlayScene/Colliider/CollisionOLL.h"

class Bullet;
class Player;
class Enemy;
class Airship;
/// <summary>
/// ITurretComponent�C���^�t�F�[�X���`����
/// </summary>
interface ITurretComponent
{
	// �e�̃A�h���X�̃Z�b�^�[�A�Q�b�^�[
	virtual ITurretComponent* GetParent() = 0;

	//�q�̃p�[�c�̔z��̃Q�b�^�[
	virtual std::vector<std::unique_ptr<ITurretComponent>>& GetParts() = 0;
	virtual void AddPart(std::unique_ptr<ITurretComponent> part) = 0;

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;

	//��]�̃Q�b�^�[�Z�b�^�[
	virtual DirectX::SimpleMath::Quaternion GetRotate() const = 0;
	virtual void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) = 0;

	//�����̃Z�b�^�[�A�Q�b�^�[
	virtual bool GetSurvival() const = 0;
	virtual void SetSurvival(const bool& survival) = 0;

	//HP�̃Q�b�^�[�A�Z�b�^�[
	virtual int GetHp() const = 0;
	virtual void SetHp(const int& Hp) = 0;

	//���Ԃ̃Q�b�^�[�A�Z�b�^�[
	virtual float GetTimer() const = 0;
	virtual void SetTimer(const float& timer) = 0;

	//���S��]�̃Q�b�^�[�Z�b�^�[
	virtual DirectX::SimpleMath::Quaternion GetRandomRotate() const = 0;
	virtual void SetRandomRotate(const DirectX::SimpleMath::Quaternion& killRotate) = 0;

	//�d�͂̃Q�b�^�[�A�Z�b�^�[
	virtual float GetGravity() const = 0;
	virtual void SetGravity(const float& gravity) = 0;

	//���f���̃Z�b�^�[�A�Q�b�^�[
	virtual DirectX::Model* GetPartModel() = 0;
	virtual void SetPartModel(DirectX::Model* supplyPointModel) = 0;

	//�����蔻��̃Q�b�^�[
	virtual Collider::MultipleHitDetermination* GetCollider() = 0;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~ITurretComponent() = default;

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="position">�P�t���[������</param>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	virtual void Update(
		const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;

	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="position">�P�t���[������</param>
	virtual void Explosion(const float& elapsedTime) = 0;


	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// �����蔻��̏���������
	/// </summary>
	virtual bool CollisionPlayer(Player* player) = 0;
	virtual bool CollisionBullet(Bullet* bullet) = 0;

	/// <summary>
	/// �㏈���������Ȃ�
	/// </summary>
	virtual void Finalize() = 0;
};
