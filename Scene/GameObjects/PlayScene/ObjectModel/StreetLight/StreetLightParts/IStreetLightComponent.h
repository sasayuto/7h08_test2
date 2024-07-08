#pragma once
#include <pch.h>
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"

class Bullet;
class Player;
class Enemy;
class Airship;
class SandstormEffect;
/// <summary>
/// IPlayerComponent�C���^�t�F�[�X���`����
/// </summary>
interface IStreetLightComponent
{
	// �e�̃A�h���X�̃Z�b�^�[�A�Q�b�^�[
	virtual IStreetLightComponent* GetParent() = 0;
	virtual void SetParent(IStreetLightComponent* parent) = 0;

	//
	virtual std::vector<std::unique_ptr<IStreetLightComponent>>& GetParts() = 0;
	virtual void AddPart(std::unique_ptr<IStreetLightComponent> part) = 0;

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;

	//�d�͂̃Q�b�^�[�A�Z�b�^�[
	virtual float GetTimer() const = 0;
	virtual void SetTimer(const float& timer) = 0;

	//��]�̃Q�b�^�[�Z�b�^�[
	virtual DirectX::SimpleMath::Quaternion GetRotate() const = 0;
	virtual void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) = 0;

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	virtual bool GetSurvival() const = 0;
	virtual void SetSurvival(const bool& survival) = 0;

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
	virtual Collider::OBB* GetCollider() = 0;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~IStreetLightComponent() = default;

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="position">�e�̈ʒu</param>
	/// <param name="angle">�e�̊p�x</param>
	virtual void Update(const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& angle
	) = 0;	
	
	/// <summary>
	/// ��������
	/// </summary>
	virtual void Explosion(const float& elapsedTime) = 0;

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// �V���h�E�}�b�v�p�̉摜�����
	/// </summary>
	virtual void RenderShadowTex() = 0;

	/// <summary>
	/// �����蔻��̏���������
	/// </summary>
	virtual bool CollisionPlayer(Player* player) = 0;
	virtual bool CollisionSandstorm(SandstormEffect* sandstormEffect) = 0;
	virtual IStreetLightComponent* Collision(Enemy* enemy) = 0;
	virtual IStreetLightComponent* Collision(Airship* airship) = 0;
	virtual bool Collision(Bullet* bullet) = 0;

	/// <summary>
	/// �㏈���������Ȃ�
	/// </summary>
	virtual void Finalize() = 0;

	virtual bool SurvivalCheck() = 0;


};
