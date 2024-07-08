#pragma once
#include <pch.h>
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"

class Bullet;
class Player;
struct IPlayerComponent;
class Enemy;
class Airship;
/// <summary>
/// IPlayerComponent�C���^�t�F�[�X���`����
/// </summary>
interface IWindmillComponent
{
	// �e�̃A�h���X�̃Z�b�^�[�A�Q�b�^�[
	virtual IWindmillComponent* GetParent() = 0;
	virtual void SetParent(IWindmillComponent* parent) = 0;

	//
	virtual std::vector<std::unique_ptr<IWindmillComponent>>& GetParts() = 0;
	virtual void AddPart(std::unique_ptr<IWindmillComponent> part) = 0;

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;

	//��]�̃Q�b�^�[�Z�b�^�[
	virtual DirectX::SimpleMath::Quaternion GetRotate() const = 0;
	virtual void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) = 0;

	//���f���̃Z�b�^�[�A�Q�b�^�[
	virtual DirectX::Model* GetPartModel() = 0;
	virtual void SetPartModel(DirectX::Model* supplyPointModel) = 0;

	//�����蔻��̃Q�b�^�[
	virtual Collider::OBB* GetCollider() = 0;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~IWindmillComponent() = default;

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
	virtual void RenderShadowTex() = 0;

	/// <summary>
	/// �����蔻��̏���������
	/// </summary>
	virtual IWindmillComponent* Collision(Player* player) = 0;
	virtual bool CollisionPlayer(Player* player) = 0;
	virtual bool CollisionEnemy(Enemy* enemy) = 0;
	virtual IWindmillComponent* Collision(Airship* airship) = 0;
	virtual bool Collision(Bullet* bullet) = 0;

	/// <summary>
	/// �㏈���������Ȃ�
	/// </summary>
	virtual void Finalize() = 0;
};
